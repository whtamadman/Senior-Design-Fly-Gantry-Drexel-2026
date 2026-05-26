#include "pch.h"

#include <windows.h>
#include <pylon/PylonIncludes.h>
#ifdef PYLON_WIN_BUILD
#include <pylon/PylonGUI.h>
#endif
#include <pylon/usb/BaslerUsbInstantCamera.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio/videoio.hpp>

#include <yolo_v2_class.hpp>

#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <filesystem>
#include <string>
#include <sstream>
#include <vector>
#include <deque>
#include <cmath>
#include <algorithm>
#include <thread>
#include <concurrent_queue.h>
#include <mutex>
#include <condition_variable>
#include <atomic>

#include "HardwareTriggerConfiguration.h"
#include "WindowManager.h"
#include "gantry.h"
#include "filter.h"
#include "flyViewStruc.h"
#include "MatlabSaveData.h"

#include <common/image/image.hpp>
#include <common/parameters.hpp>
#include <common/returncode.hpp>
#include <dlp_platforms/lightcrafter_4500/lcr4500.hpp>

using namespace std;
using namespace cv;
using namespace Pylon;
using namespace GenApi;
using namespace Basler_UsbCameraParams;
using ZaberGantry::Gantry;

namespace {

constexpr double kFrequencyHz = 480.0;
constexpr double kObjectSpaceResolutionUmPerPixel = 4.8 / 0.5; // 9.6 um/pixel
constexpr double kManualSpeedMmPerSec = 5;
constexpr int kYoloInputWidth = 296;
constexpr int kYoloInputHeight = 300;
constexpr int kFlyMissHoldFrames = 5;
constexpr int kCenterAverageWindow = 5;
constexpr float kAutoMaxErrorPx = 40.0f;

// Projector DMD constants
constexpr unsigned int kDmdColumns = 912;
constexpr unsigned int kDmdRows = 1140;
constexpr unsigned int kSpotWidthPixels = 3;
constexpr unsigned int kSpotHeightPixels = 4;

// Keep false when TI GUI already owns USB HID and projector is already in video mode.
// Set true only if you need exclusive USB control and TI GUI is not running.
constexpr bool kUseUsbProjectorControl = false;

// 3x3 homography matrix for camera -> projector transformation
struct HomographyMatrix {
    double data[3][3];
    bool loaded = false;
};

unsigned int ClampUnsigned(unsigned int value, unsigned int maxValue) {
    return std::min(value, maxValue);
}

// Load camera_to_projector_matrix.csv (3x3 CSV file)
bool LoadHomographyMatrix(const std::string &filepath, HomographyMatrix &H) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Could not open " << filepath << std::endl;
        return false;
    }

    std::string line;
    for (int row = 0; row < 3 && std::getline(file, line); ++row) {
        std::istringstream lineStream(line);
        std::string cell;
        for (int col = 0; col < 3 && std::getline(lineStream, cell, ','); ++col) {
            try {
                H.data[row][col] = std::stod(cell);
            } catch (...) {
                std::cerr << "Parse error at row " << row << ", col " << col << std::endl;
                return false;
            }
        }
    }

    H.loaded = true;
    std::cout << "Loaded homography matrix from " << filepath << std::endl;
    return true;
}

// Try to find and load calibration matrix from common locations
bool TryLoadHomographyMatrix(HomographyMatrix &H) {
    const std::vector<std::string> paths = {
        "camera_to_projector_matrix.csv",
        "../camera_to_projector_matrix.csv",
        "../../camera_to_projector_matrix.csv",
        "../../../experiments/projector/camera_to_projector_matrix.csv",
    };

    for (const auto &path : paths) {
        std::ifstream test(path);
        if (test.good()) {
            test.close();
            std::cout << "Searching for matrix file..." << std::endl;
            return LoadHomographyMatrix(path, H);
        }
    }

    std::cerr << "Could not find camera_to_projector_matrix.csv in any standard location." << std::endl;
    return false;
}

// Initialize homography matrix with hard-coded calibration values
void InitializeHomographyMatrixHardcoded(HomographyMatrix &H) {
    H.data[0][0] = 0.11702;
    H.data[0][1] = 0.034507;
    H.data[0][2] = 133.88;
    
    H.data[1][0] = -0.022916;
    H.data[1][1] = 0.25797;
    H.data[1][2] = 441.7;
    
    H.data[2][0] = -3.2228e-05;
    H.data[2][1] = 9.6704e-05;
    H.data[2][2] = 1.0;
    
    H.loaded = true;
    std::cout << "Initialized homography matrix with hard-coded calibration values." << std::endl;
}

// Apply homography: [px_tilde, py_tilde, w_tilde] = H * [cx, cy, 1]^T
// Then normalize: px = px_tilde / w_tilde, py = py_tilde / w_tilde
bool ApplyHomography(const HomographyMatrix &H, double cx, double cy,
                     unsigned int &out_px, unsigned int &out_py) {
    if (!H.loaded) {
        std::cerr << "Homography matrix not loaded." << std::endl;
        return false;
    }

    double px_tilde = H.data[0][0] * cx + H.data[0][1] * cy + H.data[0][2];
    double py_tilde = H.data[1][0] * cx + H.data[1][1] * cy + H.data[1][2];
    double w_tilde = H.data[2][0] * cx + H.data[2][1] * cy + H.data[2][2];

    if (std::fabs(w_tilde) < 1e-6) {
        std::cerr << "Homography scale factor near zero." << std::endl;
        return false;
    }

    double px = px_tilde / w_tilde;
    double py = py_tilde / w_tilde;

    out_px = ClampUnsigned(static_cast<unsigned int>(std::round(px)), kDmdColumns - 1U);
    out_py = ClampUnsigned(static_cast<unsigned int>(std::round(py)), kDmdRows - 1U);

    return true;
}

// Build a frame for projector output with a white spot at (targetX, targetY)
Mat BuildProjectorFrame(unsigned int targetX, unsigned int targetY, bool blank) {
    Mat frame(static_cast<int>(kDmdRows), static_cast<int>(kDmdColumns), CV_8UC3, cv::Scalar(0, 0, 0));

    if (blank) {
        return frame;
    }

    const int halfW = static_cast<int>(kSpotWidthPixels / 2U);
    const int halfH = static_cast<int>(kSpotHeightPixels / 2U);
    const int startX = std::max(0, static_cast<int>(targetX) - halfW);
    const int startY = std::max(0, static_cast<int>(targetY) - halfH);
    const int width = std::min(static_cast<int>(kSpotWidthPixels), static_cast<int>(kDmdColumns) - startX);
    const int height = std::min(static_cast<int>(kSpotHeightPixels), static_cast<int>(kDmdRows) - startY);

    cv::rectangle(
        frame,
        cv::Rect(startX, startY, std::max(1, width), std::max(1, height)),
        cv::Scalar(255, 255, 255),
        cv::FILLED);

    return frame;
}

dlp::ReturnCode BuildFrame(unsigned int targetX, unsigned int targetY, bool blankOutput, dlp::Image *outputImage)
{
    dlp::ReturnCode ret;
    if (!outputImage) {
        return ret.AddError("NULL_POINTER_ARGUMENT_DATA");
    }

    cv::Mat frame(static_cast<int>(kDmdRows), static_cast<int>(kDmdColumns), CV_8UC3, cv::Scalar(0, 0, 0));

    if (blankOutput) {
        return outputImage->Create(frame);
    }

    const int halfW = static_cast<int>(kSpotWidthPixels / 2U);
    const int halfH = static_cast<int>(kSpotHeightPixels / 2U);
    const int startX = std::max(0, static_cast<int>(targetX) - halfW);
    const int startY = std::max(0, static_cast<int>(targetY) - halfH);
    const int width = std::min(static_cast<int>(kSpotWidthPixels), static_cast<int>(kDmdColumns) - startX);
    const int height = std::min(static_cast<int>(kSpotHeightPixels), static_cast<int>(kDmdRows) - startY);

    cv::rectangle(
        frame,
        cv::Rect(startX, startY, std::max(1, width), std::max(1, height)),
        cv::Scalar(255, 255, 255),
        cv::FILLED);

    return outputImage->Create(frame);
}

dlp::ReturnCode ConfigureProjectorForVideoMode(dlp::LCr4500 &projector)
{
    dlp::Parameters videoParams;
    videoParams.Set(dlp::LCr4500::Parameters::OperatingMode(dlp::LCr4500::OperatingMode::VIDEO));
    videoParams.Set(dlp::LCr4500::Parameters::VideoInputSource(dlp::LCr4500::Video::InputSource::FPD_LINK));
    videoParams.Set(dlp::LCr4500::Parameters::VideoParallelPortWidth(dlp::LCr4500::Video::ParallelPortWidth::BITS_30));
    videoParams.Set(dlp::LCr4500::Parameters::InvertData(dlp::LCr4500::InvertData::NORMAL));
    videoParams.Set(dlp::LCr4500::Parameters::LED_SequenceAutomatic(true));
    videoParams.Set(dlp::LCr4500::Parameters::LED_EnableRed(true));
    videoParams.Set(dlp::LCr4500::Parameters::LED_EnableGreen(true));
    videoParams.Set(dlp::LCr4500::Parameters::LED_EnableBlue(true));
    return projector.Setup(videoParams);
}

void configureBottomCameraFreeRun(CBaslerUsbInstantCamera& camera)
{
    // Override hardware trigger config so USB camera streams continuously.
    GenApi::INodeMap& nodeMap = camera.GetNodeMap();
    GenApi::CEnumerationPtr triggerSelector(nodeMap.GetNode("TriggerSelector"));
    GenApi::CEnumerationPtr triggerMode(nodeMap.GetNode("TriggerMode"));
    if (triggerSelector && triggerMode)
    {
        if (IsAvailable(triggerSelector->GetEntryByName("FrameStart")))
        {
            triggerSelector->FromString("FrameStart");
            triggerMode->FromString("Off");
        }
        if (IsAvailable(triggerSelector->GetEntryByName("AcquisitionStart")))
        {
            triggerSelector->FromString("AcquisitionStart");
            triggerMode->FromString("Off");
        }
    }

    GenApi::CEnumerationPtr acquisitionMode(nodeMap.GetNode("AcquisitionMode"));
    if (acquisitionMode && IsAvailable(acquisitionMode->GetEntryByName("Continuous")))
    {
        acquisitionMode->FromString("Continuous");
    }
}

void configureCameraFrameRate(CBaslerUsbInstantCamera& camera, double targetHz, const char* cameraLabel)
{
    GenApi::INodeMap& nodeMap = camera.GetNodeMap();

    GenApi::CBooleanPtr frameRateEnable(nodeMap.GetNode("AcquisitionFrameRateEnable"));
    if (frameRateEnable && IsWritable(frameRateEnable))
    {
        frameRateEnable->SetValue(true);
    }

    GenApi::CFloatPtr frameRate(nodeMap.GetNode("AcquisitionFrameRate"));
    if (!frameRate || !IsWritable(frameRate))
    {
        std::cout << "Warning: " << cameraLabel << " camera does not expose writable AcquisitionFrameRate." << std::endl;
        return;
    }

    const double minHz = frameRate->GetMin();
    const double maxHz = frameRate->GetMax();
    const double appliedHz = std::max(minHz, std::min(targetHz, maxHz));
    frameRate->SetValue(appliedHz);

    std::cout << cameraLabel << " camera acquisition frame rate set to " << appliedHz << " Hz";
    if (appliedHz < targetHz)
    {
        std::cout << " (requested " << targetHz << " Hz; camera max is " << maxHz << " Hz)";
    }
    std::cout << std::endl;
}

string buildTimestampForFilename()
{
    time_t now = time(nullptr);
    tm localTm{};
    localtime_s(&localTm, &now);

    char buffer[32] = {};
    strftime(buffer, sizeof(buffer), "%Y%m%d%H%M", &localTm);
    return string(buffer);
}

string buildDateForFolder()
{
    time_t now = time(nullptr);
    tm localTm{};
    localtime_s(&localTm, &now);

    char buffer[16] = {};
    strftime(buffer, sizeof(buffer), "%Y%m%d", &localTm);
    return string(buffer);
}

string buildClockTime()
{
    time_t now = time(nullptr);
    tm localTm{};
    localtime_s(&localTm, &now);

    char buffer[16] = {};
    strftime(buffer, sizeof(buffer), "%H:%M:%S", &localTm);
    return string(buffer);
}

unsigned long clampToUnsignedLong(double value)
{
    if (value < 0.0)
    {
        return 0;
    }
    if (value > static_cast<double>(numeric_limits<unsigned long>::max()))
    {
        return numeric_limits<unsigned long>::max();
    }
    return static_cast<unsigned long>(value);
}

struct StopButtonUiState
{
    enum class ButtonId
    {
        None,
        Stop,
        Exit,
    };

    std::mutex mutex;
    cv::Rect stopButtonRect;
    cv::Rect exitButtonRect;
    ButtonId pressedButton = ButtonId::None;
    bool stopClicked = false;
    bool exitClicked = false;
};

string formatDurationHMS(std::chrono::steady_clock::duration duration)
{
    const auto totalSeconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
    const long long hours = totalSeconds / 3600;
    const long long minutes = (totalSeconds % 3600) / 60;
    const long long seconds = totalSeconds % 60;

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hours
        << ":" << std::setw(2) << minutes
        << ":" << std::setw(2) << seconds;
    return oss.str();
}

void OnCameraFeedsMouse(int event, int x, int y, int /*flags*/, void* userdata)
{
    auto* uiState = static_cast<StopButtonUiState*>(userdata);
    if (!uiState)
    {
        return;
    }

    std::lock_guard<std::mutex> lock(uiState->mutex);
    const cv::Point p(x, y);

    if (event == cv::EVENT_LBUTTONDOWN)
    {
        if (uiState->stopButtonRect.contains(p))
        {
            uiState->pressedButton = StopButtonUiState::ButtonId::Stop;
        }
        else if (uiState->exitButtonRect.contains(p))
        {
            uiState->pressedButton = StopButtonUiState::ButtonId::Exit;
        }
        else
        {
            uiState->pressedButton = StopButtonUiState::ButtonId::None;
        }
    }
    else if (event == cv::EVENT_LBUTTONUP)
    {
        const bool releasedOnStop = uiState->stopButtonRect.contains(p);
        const bool releasedOnExit = uiState->exitButtonRect.contains(p);

        if (uiState->pressedButton == StopButtonUiState::ButtonId::Stop && releasedOnStop)
        {
            uiState->stopClicked = true;
        }
        else if (uiState->pressedButton == StopButtonUiState::ButtonId::Exit && releasedOnExit)
        {
            uiState->exitClicked = true;
        }
        uiState->pressedButton = StopButtonUiState::ButtonId::None;
    }
}

bool ConsumeStopButtonClick(StopButtonUiState& uiState)
{
    std::lock_guard<std::mutex> lock(uiState.mutex);
    if (!uiState.stopClicked)
    {
        return false;
    }
    uiState.stopClicked = false;
    return true;
}

bool ConsumeExitButtonClick(StopButtonUiState& uiState)
{
    std::lock_guard<std::mutex> lock(uiState.mutex);
    if (!uiState.exitClicked)
    {
        return false;
    }
    uiState.exitClicked = false;
    return true;
}

// Shared data structure for thread-safe frame passing and state
struct SharedContext
{
    Mat bottomFrame;
    Mat sideFrame;
    Point2f manualVelocity;
    bool saveEnabled = false;
    bool stopRequested = false;
    unsigned long frameCounter = 0;
    
    // Projector target pixel from camera click
    unsigned int projectorTargetX = kDmdColumns / 2U;
    unsigned int projectorTargetY = kDmdRows / 2U;
    bool projectorTargetUpdated = false;
    bool projectorBlank = false;
    bool projectorEnabled = true;
    
    std::mutex frameMutex;
    // YOLO detection results (protected by yoloMutex)
    bool flyDetected = false;
    bool headDetected = false;
    Point bodyCoM;
    Point headCoM;
    Rect bodyBox;
    Rect headBox;
    Point2f estDist;          // Kalman-filtered pixel error from frame center
    Point2f estVel;           // Kalman-filtered pixel velocity (px/update)
    TrackerLocal filter;      // V2-style tracker for smoothing + velocity estimate
    bool autoTrackEnabled = false;
    bool autoJustEnabled = false;
    bool flyDetectedFresh = false;
    std::mutex yoloMutex;

    std::mutex velocityMutex;
    std::mutex saveMutex;
    std::mutex projectorMutex;
    
    std::condition_variable frameCV;
    std::condition_variable stopCV;
    std::condition_variable projectorCV;
};

} // namespace

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    if (!SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS))
    {
        cout << "Could not set priority class" << endl;
    }

    LPCSTR rootPath = "C:\\";
    DWORD sectorsPerCluster = 0;
    DWORD bytesPerSector = 0;
    DWORD numberOfFreeClusters = 0;
    DWORD totalNumberOfClusters = 0;
    GetDiskFreeSpaceA(rootPath, &sectorsPerCluster, &bytesPerSector, &numberOfFreeClusters, &totalNumberOfClusters);
    const double totalFreeGB = static_cast<double>(numberOfFreeClusters) *
        static_cast<double>(sectorsPerCluster) *
        static_cast<double>(bytesPerSector) /
        (1024.0 * 1024.0 * 1024.0);
    if (totalFreeGB < 50.0)
    {
        cout << "Warning: only " << totalFreeGB << " GB free on C: drive." << endl;
    }

    cout << "---------------------------------\n";
    cout << "-Robotic System for Fly Tracking-\n";
    cout << "-Bottom camera + manual + Zaber-\n";
    cout << "-gantrycodeV3 (4 worker threads)-\n";
    cout << "---------------------------------\n";

    WindowManager wnd;
    const char* userProfile = getenv("USERPROFILE");
    const string dataRoot = string(userProfile ? userProfile : ".") + "\\Documents\\Data";
    const string timestamp = buildTimestampForFilename();
    const string runDate = buildDateForFolder();
    const string runFolder = dataRoot + "\\" + runDate + "\\" + timestamp;
    std::filesystem::create_directories(runFolder);
    const string dataName = runFolder + "\\" + timestamp;
    const string textFileName = dataName + ".txt";
    const string bottomVideoFileName = dataName + ".avi";
    const string sideVideoFileName = dataName + "_side.avi";
    const string yoloVideoFileName = dataName + "_yolo.avi";
    cout << "Saving run data to: " << runFolder << endl;

    const string matFileName = dataName + ".mat";
    const string metaFileName = dataName + "_meta.csv";
    std::unique_ptr<MatlabSaveData> matSaveData;

    ofstream textOut;
    VideoWriter writer;
    VideoWriter sideWriter;
    VideoWriter yoloWriter;
    const int codec = VideoWriter::fourcc('M', 'J', 'P', 'G');

    std::unique_ptr<Gantry> motors;
    bool pylonInitialized = false;
    bool fatalError = false;
    string lastStep = "startup";

    dlp::LCr4500 projector;
    bool projectorControlAvailable = false;

    SharedContext sharedCtx;
    StopButtonUiState stopButtonUi;
    sharedCtx.filter.Init(Point2f(0.0f, 0.0f));
    concurrency::concurrent_queue<Mat> yoloFrameQueue;
    concurrency::concurrent_queue<Mat> displayBottomFrameQueue;
    wnd.newCVWindow("camera feeds");
    cv::setMouseCallback("camera feeds", OnCameraFeedsMouse, &stopButtonUi);

    try
    {
        lastStep = "PylonInitialize";
        PylonInitialize();
        pylonInitialized = true;

        lastStep = "MatlabSaveData initialization";
        matSaveData = std::make_unique<MatlabSaveData>(matFileName.c_str(), kFrequencyHz);
        // Create an initial .mat immediately so the file exists even during an active run.
        matSaveData->saveMatFile();
        cout << "Initialized MAT file at: " << matFileName << endl;
        lastStep = "open text output file";
        textOut.open(textFileName, ofstream::out);
        textOut << "# run_folder\t" << runFolder << "\n";
        textOut << "# txt_file\t" << textFileName << "\n";
        textOut << "# bottom_video_file\t" << bottomVideoFileName << "\n";
        textOut << "# side_video_file\t" << sideVideoFileName << "\n";
        textOut << "# yolo_video_file\t" << yoloVideoFileName << "\n";
        textOut << "# mat_file\t" << matFileName << "\n";
        textOut << "# meta_csv_file\t" << metaFileName << "\n";
        textOut << "dataNum\tcamTime\tframeCoMX\tframeCoMY\tgrabSucceeded\timageDamaged\tdecoderdt\t"
               "encoderX\tencoderY\tabsCoMX\tabsCoMY\tbottomCamSeesFly\tmanualOrAuto\tonPROJ\t"
               "centerX\tcenterY\tbottomCamInCharge\tclockTime\tprojStateInt\tstimulusVoltage\n";
        textOut.flush();

        {
            ofstream initialMetaOut(metaFileName, ofstream::out);
            if (initialMetaOut.is_open())
            {
                initialMetaOut << "# NOTE: Optostim output fields are not populated in this system version (optostim removed).\n";
                initialMetaOut
                    << "Arena center coordinate X," << "Arena Center coordinate Y," << "Arena Radius," << "Object space resolution,"
                    << "Ending Optogenetic Stimulation Center X," << "Ending Optogenetic Stimulation Center Y," << "Optogenetic Stimulation Radius,"
                    << "Stimulus Type," << "Optogenetic Stimulus Slope," << "Optogenetic Stimulus Width," << "Stimulus Voltage," << "Yolo,"
                    << "Optogenetic Inner Circle Radius\n";

                initialMetaOut
                    << 0 << "," << 0 << "," << 0 << "," << kObjectSpaceResolutionUmPerPixel << ","
                    << 0 << "," << 0 << "," << 0 << ","
                    << 0 << "," << 0 << "," << 0 << ","
                    << 0 << "," << "Yes" << "," << 0;
                initialMetaOut.close();
                cout << "Initialized meta CSV at: " << metaFileName << endl;
            }
            else
            {
                cerr << "Warning: could not initialize meta CSV: " << metaFileName << endl;
            }
        }

        lastStep = "load homography matrix for projector";
        HomographyMatrix H;
        InitializeHomographyMatrixHardcoded(H);
        
        // Initialize projector to center of camera (800x600 -> 400, 300)
        unsigned int centerProjX = 0, centerProjY = 0;
        if (ApplyHomography(H, 400.0, 300.0, centerProjX, centerProjY)) {
            {
                std::lock_guard<std::mutex> lock(sharedCtx.projectorMutex);
                sharedCtx.projectorTargetX = centerProjX;
                sharedCtx.projectorTargetY = centerProjY;
            }
            cout << "Projector aimed at camera center (400, 300) -> DMD (" << centerProjX << ", " << centerProjY << ")" << endl;
        } else {
            cout << "Warning: Homography transform failed at startup." << endl;
        }

        lastStep = "configure DLP projector";
        dlp::ReturnCode ret;
        
        if (kUseUsbProjectorControl) {
            ret = projector.Connect("0");
            if (ret.hasErrors()) {
                cout << "Warning: Could not connect to DLP projector via USB: " << ret.ToString() << endl;
                cout << "Continuing in video-only mode; keep TI GUI configured to Video Mode + FPD_LINK." << endl;
            } else {
                projectorControlAvailable = true;
                ret = projector.StopPatternSequence();
                if (ret.hasErrors()) {
                    cout << "Pattern stop returned: " << ret.ToString() << " (continuing)." << endl;
                }
                ret = ConfigureProjectorForVideoMode(projector);
                if (ret.hasErrors()) {
                    cout << "Warning: projector video-mode setup failed: " << ret.ToString() << endl;
                } else {
                    cout << "Projector configured for video mode (FPD_LINK)." << endl;
                }
            }
        } else {
            cout << "USB projector control disabled. Make sure TI GUI is already running and projector" << endl;
            cout << "is configured to Video Mode + FPD_LINK (parallel) input." << endl;
            cout << "Video frames will be sent via FPD_LINK parallel interface." << endl;
        }

        lastStep = "connect Zaber gantry";
        cout << "Connecting to Zaber gantry on COM4..." << endl;
        motors = std::make_unique<Gantry>("COM4");
        lastStep = "configure Zaber gantry";
        motors->configure();

        lastStep = "detect camera devices";
        CTlFactory& tlFactory = CTlFactory::GetInstance();
        DeviceInfoList_t devices;
        if (tlFactory.EnumerateDevices(devices) == 0)
        {
            throw RUNTIME_EXCEPTION("No camera devices found.");
        }

        // Device 0 is treated as bottom camera, device 1 (if present) as side camera.
        CBaslerUsbInstantCamera bottomCamera(tlFactory.CreateDevice(devices[0]));
        std::unique_ptr<CBaslerUsbInstantCamera> sideCamera;
        if (devices.size() > 1)
        {
            sideCamera = std::make_unique<CBaslerUsbInstantCamera>(tlFactory.CreateDevice(devices[1]));
        }

        cout << "Bottom camera: " << bottomCamera.GetDeviceInfo().GetModelName()
             << " (SN " << bottomCamera.GetDeviceInfo().GetSerialNumber() << ")" << endl;
        if (sideCamera)
        {
            cout << "Side camera: " << sideCamera->GetDeviceInfo().GetModelName()
                 << " (SN " << sideCamera->GetDeviceInfo().GetSerialNumber() << ")" << endl;
        }
        else
        {
            cout << "Side camera: not detected" << endl;
        }

        lastStep = "register bottom camera configuration";
        bottomCamera.RegisterConfiguration(new CHardwareTriggerConfiguration, RegistrationMode_ReplaceAll, Cleanup_Delete);
        lastStep = "open bottom camera";
        bottomCamera.Open();

        lastStep = "force bottom camera free-run trigger mode";
        configureBottomCameraFreeRun(bottomCamera);

        lastStep = "configure bottom camera settings";
        bottomCamera.ExposureTime.SetValue(1000.0);
        bottomCamera.SensorReadoutMode.SetValue(SensorReadoutMode_Fast);
        bottomCamera.Width.SetValue(592);
        bottomCamera.Height.SetValue(600);
        bottomCamera.OffsetX.SetValue(112);
        bottomCamera.OffsetY.SetValue(16);
        bottomCamera.ReverseX.SetValue(true);
        configureCameraFrameRate(bottomCamera, kFrequencyHz, "Bottom");

        bottomCamera.ChunkModeActive.SetValue(true);
        bottomCamera.ChunkSelector.SetValue(ChunkSelector_Timestamp);
        bottomCamera.ChunkEnable.SetValue(true);
        bottomCamera.ChunkSelector.SetValue(ChunkSelector_PayloadCRC16);
        bottomCamera.ChunkEnable.SetValue(true);

        if (sideCamera)
        {
            lastStep = "register side camera configuration";
            sideCamera->RegisterConfiguration(new CHardwareTriggerConfiguration, RegistrationMode_ReplaceAll, Cleanup_Delete);
            lastStep = "open side camera";
            sideCamera->Open();
            lastStep = "force side camera free-run trigger mode";
            configureBottomCameraFreeRun(*sideCamera);

            // Keep side camera setup minimal for robust startup across device variants.
            sideCamera->ExposureTime.SetValue(1000.0);
            sideCamera->SensorReadoutMode.SetValue(SensorReadoutMode_Fast);
            configureCameraFrameRate(*sideCamera, kFrequencyHz, "Side");
        }

        lastStep = "start grabbing";
        // Low-latency path: keep queues shallow and always process the newest frame.
        bottomCamera.MaxNumBuffer = 8;
        bottomCamera.OutputQueueSize = 1;
        bottomCamera.MaxNumQueuedBuffer = 2;
        bottomCamera.StartGrabbing(GrabStrategy_LatestImageOnly, GrabLoop_ProvidedByUser);
        if (sideCamera)
        {
            sideCamera->MaxNumBuffer = 8;
            sideCamera->OutputQueueSize = 1;
            sideCamera->MaxNumQueuedBuffer = 2;
            sideCamera->StartGrabbing(GrabStrategy_LatestImageOnly, GrabLoop_ProvidedByUser);
        }

        CImageFormatConverter formatConverter;
        formatConverter.OutputPixelFormat = PixelType_Mono8;

        // Lambda: Bottom camera acquisition thread
        auto threadBottomCamera = [&]()
        {
            try
            {
                CImageFormatConverter localConverter;
                localConverter.OutputPixelFormat = PixelType_Mono8;
                CPylonImage pylonImage;
                while (!sharedCtx.stopRequested && bottomCamera.IsGrabbing())
                {
                    CGrabResultPtr grabResult;
                    bottomCamera.RetrieveResult(20, grabResult, TimeoutHandling_Return);
                    if (!grabResult || !grabResult->GrabSucceeded())
                    {
                        std::this_thread::sleep_for(std::chrono::milliseconds(1));
                        continue;
                    }

                    localConverter.Convert(pylonImage, grabResult);
                    Mat grayFrame(
                        grabResult->GetHeight(),
                        grabResult->GetWidth(),
                        CV_8UC1,
                        static_cast<uint8_t*>(pylonImage.GetBuffer()));
                    Mat frameClone = grayFrame.clone();

                    {
                        std::lock_guard<std::mutex> lock(sharedCtx.frameMutex);
                        sharedCtx.bottomFrame = frameClone;
                        sharedCtx.frameCounter++;
                    }
                    yoloFrameQueue.push(frameClone);
                    if (sharedCtx.frameCounter % 32 == 0)
                    {
                        displayBottomFrameQueue.push(frameClone);
                    }
                    sharedCtx.frameCV.notify_one();
                }
            }
            catch (const exception& e)
            {
                cerr << "Bottom camera thread error: " << e.what() << endl;
            }
        };

        // Lambda: Side camera acquisition thread
        auto threadSideCamera = [&]()
        {
            if (!sideCamera)
                return;
            try
            {
                CImageFormatConverter localConverter;
                localConverter.OutputPixelFormat = PixelType_Mono8;
                CPylonImage pylonImage;
                while (!sharedCtx.stopRequested && sideCamera->IsGrabbing())
                {
                    CGrabResultPtr grabResult;
                    sideCamera->RetrieveResult(1, grabResult, TimeoutHandling_Return);
                    if (!grabResult || !grabResult->GrabSucceeded())
                    {
                        std::this_thread::sleep_for(std::chrono::milliseconds(1));
                        continue;
                    }

                    localConverter.Convert(pylonImage, grabResult);
                    Mat grayFrame(
                        grabResult->GetHeight(),
                        grabResult->GetWidth(),
                        CV_8UC1,
                        static_cast<uint8_t*>(pylonImage.GetBuffer()));

                    {
                        std::lock_guard<std::mutex> lock(sharedCtx.frameMutex);
                        sharedCtx.sideFrame = grayFrame.clone();
                    }
                }
            }
            catch (const exception& e)
            {
                cerr << "Side camera thread error: " << e.what() << endl;
            }
        };

        // Lambda: Manual input thread
        auto threadManualInput = [&]()
        {
            try
            {
                int saveKeyLatch = 0;
                int autoKeyLatch = 0;
                int spaceKeyLatch = 0;
                bool autoArmPending = false;
                Point2f lastPrintedManualVelocity(0.0f, 0.0f);
                while (!sharedCtx.stopRequested)
                {
                    // 'M' key arms AUTO (prints center error); Space confirms enable.
                    // If already AUTO, 'M' returns to manual immediately.
                    if (wnd.keyPressed(0x4D))
                    {
                        if (!autoKeyLatch)
                        {
                            if (sharedCtx.autoTrackEnabled)
                            {
                                sharedCtx.autoTrackEnabled = false;
                                autoArmPending = false;
                                cout << "currently manual" << endl;
                            }
                            else
                            {
                                Point2f estDist(0.0f, 0.0f);
                                bool flyFound = false;
                                {
                                    std::lock_guard<std::mutex> lock(sharedCtx.yoloMutex);
                                    estDist = sharedCtx.estDist;
                                    flyFound = sharedCtx.flyDetected;
                                }

                                cout << "AUTO arm requested. Fly center offset (px): X="
                                      << estDist.x << " Y=" << estDist.y;
                                if (!flyFound)
                                {
                                    cout << " (fly not currently detected)";
                                }
                                cout << endl;

                                autoArmPending = true;
                                cout << "Press SPACE to enable AUTO." << endl;
                            }
                        }
                        autoKeyLatch = 1;
                    }
                    else
                    {
                        autoKeyLatch = 0;
                    }

                    if (wnd.keyPressed(VK_SPACE))
                    {
                        if (!spaceKeyLatch)
                        {
                            if (!sharedCtx.autoTrackEnabled && autoArmPending)
                            {
                                sharedCtx.autoTrackEnabled = true;
                                sharedCtx.autoJustEnabled = true;
                                autoArmPending = false;
                                cout << "currently automatic" << endl;
                            }
                        }
                        spaceKeyLatch = 1;
                    }
                    else
                    {
                        spaceKeyLatch = 0;
                    }

                    if (sharedCtx.autoTrackEnabled)
                    {
                        // Automatic mode: use filtered error + filtered velocity (V2-style)
                        Point2f estDist, estVel;
                        bool flyFound;
                        bool flyFoundFresh;
                        bool autoJustEnabled;
                        {
                            std::lock_guard<std::mutex> lock(sharedCtx.yoloMutex);
                            estDist  = sharedCtx.estDist;
                            estVel   = sharedCtx.estVel;
                            flyFound = sharedCtx.flyDetected;
                            flyFoundFresh = sharedCtx.flyDetectedFresh;
                            autoJustEnabled = sharedCtx.autoJustEnabled;
                            sharedCtx.autoJustEnabled = false;
                        }

                        if (motors)
                        {
                            // Deadband: only correct if fly is more than N pixels from center
                            constexpr float kCenterDeadbandPx = 60.0f; // larger deadband to reduce center hunting
                            float distMag = std::sqrt(estDist.x * estDist.x + estDist.y * estDist.y);

                            // Clamp correction so a bad/stale estimate cannot command a huge move.
                            Point2f clampedDist(
                                std::max(-kAutoMaxErrorPx, std::min(kAutoMaxErrorPx, estDist.x)),
                                std::max(-kAutoMaxErrorPx, std::min(kAutoMaxErrorPx, estDist.y)));

                            const bool allowThisCycle = !(autoJustEnabled && !flyFoundFresh);
                            if (flyFound && distMag > kCenterDeadbandPx && allowThisCycle)
                            {
                                // Negate: camera pixel axes may be opposite gantry axes.
                                // Feed filtered velocity too, so Gantry::SetVelocity can use kf term.
                                cout << "AUTO move command (px): distX=" << clampedDist.x
                                     << " distY=" << clampedDist.y
                                     << " velX=" << estVel.x
                                     << " velY=" << estVel.y << endl;
                                motors->SetVelocity(clampedDist, -estVel, true);
                            }
                            else
                            {
                                motors->SetVelocity(Point2f(0.0f, 0.0f), Point2f(0.0f, 0.0f), true);
                            }
                        }
                    }
                    else
                    {
                        // Manual mode: arrow / IJKL keys drive at fixed mm/s
                        Point2f velocity(0.0f, 0.0f);
                        if (wnd.keyPressed(VK_UP) || wnd.keyPressed(0x4A))
                        {
                            velocity.x -= kManualSpeedMmPerSec;
                        }
                        if (wnd.keyPressed(VK_DOWN) || wnd.keyPressed(0x4C))
                        {
                            velocity.x += kManualSpeedMmPerSec;
                        }
                        if (wnd.keyPressed(VK_RIGHT) || wnd.keyPressed(0x49))
                        {
                            velocity.y += kManualSpeedMmPerSec;
                        }
                        if (wnd.keyPressed(VK_LEFT) || wnd.keyPressed(0x4B))
                        {
                            velocity.y -= kManualSpeedMmPerSec;
                        }

                        {
                            std::lock_guard<std::mutex> lock(sharedCtx.velocityMutex);
                            sharedCtx.manualVelocity = velocity;
                        }

                        if (motors)
                        {
                            if (velocity.x != 0.0f || velocity.y != 0.0f)
                            {
                                if (velocity != lastPrintedManualVelocity)
                                {
                                    // cout << "Manual move command (mm/s): X=" << velocity.x
                                    //      << " Y=" << velocity.y << endl;
                                    lastPrintedManualVelocity = velocity;
                                }
                            }
                            else
                            {
                                lastPrintedManualVelocity = Point2f(0.0f, 0.0f);
                            }
                            motors->SetVelocity(Point2f(0.0f, 0.0f), velocity, false);
                        }
                    }

                    if (wnd.keyPressed(0x53))  // 'S' key
                    {
                        if (!saveKeyLatch)
                        {
                            {
                                std::lock_guard<std::mutex> lock(sharedCtx.saveMutex);
                                sharedCtx.saveEnabled = !sharedCtx.saveEnabled;
                                cout << (sharedCtx.saveEnabled ? "started saving" : "stopped saving") << endl;
                            }
                        }
                        saveKeyLatch = 1;
                    }
                    else
                    {
                        saveKeyLatch = 0;
                    }

                    static int projectorKeyLatch = 0;
                    if (wnd.keyPressed(0x50))  // 'P' key for projector
                    {
                        if (!projectorKeyLatch)
                        {
                            {
                                std::lock_guard<std::mutex> lock(sharedCtx.projectorMutex);
                                sharedCtx.projectorEnabled = !sharedCtx.projectorEnabled;
                                cout << (sharedCtx.projectorEnabled ? "projector ON" : "projector OFF") << endl;
                            }
                        }
                        projectorKeyLatch = 1;
                    }
                    else
                    {
                        projectorKeyLatch = 0;
                    }

                    std::this_thread::sleep_for(std::chrono::milliseconds(16));  // ~60 Hz
                }
            }
            catch (const exception& e)
            {
                cerr << "Manual input thread error: " << e.what() << endl;
            }
        };

        // Lambda: Data saving thread
        auto threadDataSave = [&]()
        {
            try
            {
                auto prevEncoderSample = chrono::steady_clock::now();
                bool wasSaving = false;
                unsigned long savedDataCounter = 0;
                while (!sharedCtx.stopRequested)
                {
                    bool shouldSave;
                    {
                        std::lock_guard<std::mutex> lock(sharedCtx.saveMutex);
                        shouldSave = sharedCtx.saveEnabled;
                    }

                    if (!shouldSave)
                    {
                        if (wasSaving && matSaveData)
                        {
                            matSaveData->saveMatFile();
                            cout << "Autosaved MAT after save OFF. Samples collected: " << savedDataCounter << endl;
                        }
                        wasSaving = false;
                        std::this_thread::sleep_for(std::chrono::milliseconds(10));
                        continue;
                    }

                    if (!wasSaving)
                    {
                        // Start a fresh timing interval exactly when saving transitions OFF -> ON.
                        prevEncoderSample = chrono::steady_clock::now();
                        wasSaving = true;
                    }

                    Mat frameToSave;
                    Mat sideFrameToSave;
                    bool sideFrameAvailable = false;
                    unsigned long frameNum;
                    {
                        std::lock_guard<std::mutex> lock(sharedCtx.frameMutex);
                        if (sharedCtx.bottomFrame.empty())
                        {
                            std::this_thread::sleep_for(std::chrono::milliseconds(10));
                            continue;
                        }
                        frameToSave = sharedCtx.bottomFrame.clone();
                        if (sideCamera && !sharedCtx.sideFrame.empty())
                        {
                            sideFrameToSave = sharedCtx.sideFrame.clone();
                            sideFrameAvailable = true;
                        }
                        frameNum = ++savedDataCounter;
                    }

                    auto now = chrono::steady_clock::now();
                    auto dtNs64 = chrono::duration_cast<chrono::nanoseconds>(now - prevEncoderSample).count();
                    prevEncoderSample = now;
                    if (dtNs64 <= 0)
                    {
                        dtNs64 = static_cast<long long>((1.0 / kFrequencyHz) * 1e9);
                    }
                    const unsigned long dtNs = static_cast<unsigned long>(dtNs64);

                    if (!writer.isOpened())
                    {
                        writer.open(bottomVideoFileName, codec, kFrequencyHz, frameToSave.size(), false);
                    }
                    if (sideFrameAvailable && !sideWriter.isOpened())
                    {
                        sideWriter.open(sideVideoFileName, codec, kFrequencyHz, sideFrameToSave.size(), false);
                    }

                    const Point2f stagePosMm = motors->GetPosition();
                    unsigned long encoderXum = clampToUnsignedLong(stagePosMm.x * 1000.0);
                    unsigned long encoderYum = clampToUnsignedLong(stagePosMm.y * 1000.0);

                    int frameOffsetXpx = 0;
                    int frameOffsetYpx = 0;
                    bool flyDetected = false;
                    bool headDetected = false;
                    bool autoTrackEnabled = false;
                    unsigned long stimPointX = 0;
                    unsigned long stimPointY = 0;
                    bool projectorBlank = false;
                    bool projectorEnabled = true;
                    Point yoloBodyCoM;
                    Point yoloHeadCoM;
                    Rect yoloBodyBox;
                    Rect yoloHeadBox;
                    {
                        std::lock_guard<std::mutex> lock(sharedCtx.yoloMutex);
                        flyDetected = sharedCtx.flyDetected;
                        headDetected = sharedCtx.headDetected;
                        autoTrackEnabled = sharedCtx.autoTrackEnabled;
                        yoloBodyCoM = sharedCtx.bodyCoM;
                        yoloHeadCoM = sharedCtx.headCoM;
                        yoloBodyBox = sharedCtx.bodyBox;
                        yoloHeadBox = sharedCtx.headBox;
                        if (flyDetected)
                        {
                            frameOffsetXpx = yoloBodyCoM.x - frameToSave.cols / 2;
                            frameOffsetYpx = yoloBodyCoM.y - frameToSave.rows / 2;
                        }
                    }
                    {
                        std::lock_guard<std::mutex> lock(sharedCtx.projectorMutex);
                        stimPointX = sharedCtx.projectorTargetX;
                        stimPointY = sharedCtx.projectorTargetY;
                        projectorBlank = sharedCtx.projectorBlank;
                        projectorEnabled = sharedCtx.projectorEnabled;
                    }

                    const double absXum = static_cast<double>(encoderXum) +
                        static_cast<double>(frameOffsetXpx) * kObjectSpaceResolutionUmPerPixel;
                    const double absYum = static_cast<double>(encoderYum) +
                        static_cast<double>(frameOffsetYpx) * kObjectSpaceResolutionUmPerPixel;

                    flyViewStruc fvStruc{};
                    fvStruc.img = frameToSave.clone();
                    fvStruc.camTime = static_cast<unsigned long long>(chrono::duration_cast<chrono::nanoseconds>(chrono::steady_clock::now().time_since_epoch()).count());
                    fvStruc.grabSucceeded = 1;
                    fvStruc.imageDamaged = 0;
                    fvStruc.dataNum = frameNum;
                    fvStruc.encoderX = encoderXum;
                    fvStruc.encoderY = encoderYum;
                    fvStruc.decoderdt = dtNs;
                    fvStruc.frameCoMX = frameOffsetXpx;
                    fvStruc.frameCoMY = frameOffsetYpx;
                    fvStruc.absCoMX = clampToUnsignedLong(absXum);
                    fvStruc.absCoMY = clampToUnsignedLong(absYum);
                    fvStruc.stimPointX = stimPointX;
                    fvStruc.stimPointY = stimPointY;
                    fvStruc.bottomCamSeesFly = flyDetected ? 1 : 0;
                    fvStruc.onPROJ = projectorEnabled && !projectorBlank;
                    fvStruc.center[0] = static_cast<long long>(stimPointX);
                    fvStruc.center[1] = static_cast<long long>(stimPointY);
                    fvStruc.stimulusVoltage = 0.0f;
                    fvStruc.bottomCamInCharge = flyDetected;
                    fvStruc.clockTime = buildClockTime();
                    fvStruc.manualOrAuto = autoTrackEnabled;

                    if (writer.isOpened())
                    {
                        writer.write(fvStruc.img);
                    }

                    Mat yoloAnnotatedFrame;
                    cvtColor(frameToSave, yoloAnnotatedFrame, COLOR_GRAY2BGR);
                    line(yoloAnnotatedFrame,
                         Point(frameToSave.cols / 2 - 15, frameToSave.rows / 2),
                         Point(frameToSave.cols / 2 + 15, frameToSave.rows / 2),
                         Scalar(0, 255, 255),
                         1);
                    line(yoloAnnotatedFrame,
                         Point(frameToSave.cols / 2, frameToSave.rows / 2 - 15),
                         Point(frameToSave.cols / 2, frameToSave.rows / 2 + 15),
                         Scalar(0, 255, 255),
                         1);

                    if (flyDetected)
                    {
                        rectangle(yoloAnnotatedFrame, yoloBodyBox, Scalar(0, 255, 0), 2);
                        circle(yoloAnnotatedFrame, yoloBodyCoM, 5, Scalar(0, 255, 0), cv::FILLED);
                        putText(yoloAnnotatedFrame,
                                "BODY",
                                Point(yoloBodyBox.x, yoloBodyBox.y - 5),
                                FONT_HERSHEY_SIMPLEX,
                                0.45,
                                Scalar(0, 255, 0),
                                1);
                    }
                    if (headDetected)
                    {
                        rectangle(yoloAnnotatedFrame, yoloHeadBox, Scalar(255, 255, 0), 2);
                        circle(yoloAnnotatedFrame, yoloHeadCoM, 4, Scalar(255, 255, 0), cv::FILLED);
                        putText(yoloAnnotatedFrame,
                                "HEAD",
                                Point(yoloHeadBox.x, yoloHeadBox.y - 5),
                                FONT_HERSHEY_SIMPLEX,
                                0.45,
                                Scalar(255, 255, 0),
                                1);
                    }

                    putText(yoloAnnotatedFrame,
                            flyDetected ? "FLY DETECTED" : "FLY NOT DETECTED",
                            Point(20, 30),
                            FONT_HERSHEY_SIMPLEX,
                            0.7,
                            flyDetected ? Scalar(0, 255, 0) : Scalar(0, 0, 255),
                            2);

                    if (!yoloWriter.isOpened())
                    {
                        yoloWriter.open(yoloVideoFileName, codec, kFrequencyHz, yoloAnnotatedFrame.size(), true);
                    }
                    if (yoloWriter.isOpened())
                    {
                        yoloWriter.write(yoloAnnotatedFrame);
                    }

                    if (sideFrameAvailable && sideWriter.isOpened())
                    {
                        sideWriter.write(sideFrameToSave);
                    }

                    textOut << fvStruc.dataNum << "\t" << fvStruc.camTime << "\t" << fvStruc.frameCoMX << "\t" << fvStruc.frameCoMY << "\t"
                            << fvStruc.grabSucceeded << "\t" << fvStruc.imageDamaged << "\t" << fvStruc.decoderdt << "\t"
                            << fvStruc.encoderX << "\t" << fvStruc.encoderY << "\t" << fvStruc.absCoMX << "\t" << fvStruc.absCoMY << "\t"
                            << fvStruc.bottomCamSeesFly << "\t" << fvStruc.manualOrAuto << "\t" << fvStruc.onPROJ << "\t"
                            << fvStruc.center[0] << "\t" << fvStruc.center[1] << "\t" << fvStruc.bottomCamInCharge << "\t"
                            << fvStruc.clockTime << "\t" << static_cast<int>(fvStruc.onPROJ) << "\t" << fvStruc.stimulusVoltage << "\n";
                    textOut.flush();

                    matSaveData->addFrameData(fvStruc);

                    if (matSaveData && (savedDataCounter % 500UL == 0UL))
                    {
                        matSaveData->saveMatFile();
                        cout << "Autosaved MAT checkpoint at sample " << savedDataCounter << endl;
                    }

                    std::this_thread::sleep_for(std::chrono::milliseconds(2));
                }
            }
            catch (const exception& e)
            {
                cerr << "Data save thread error: " << e.what() << endl;
            }
        };

        // Lambda: Projector display thread
        auto threadProjectorDisplay = [&](const HomographyMatrix &H)
        {
            try
            {
                dlp::Image dlpFrame;
                cv::Mat displayMat;
                const std::string projectorWindowName = "Projector Output (DMD 912x1140)";

                // Find the secondary (projector) monitor using Windows API
                struct MonitorInfo { RECT rect; bool foundSecondary; };
                MonitorInfo monInfo = { {0,0,0,0}, false };
                EnumDisplayMonitors(nullptr, nullptr, [](HMONITOR hMon, HDC, LPRECT, LPARAM lParam) -> BOOL {
                    MONITORINFO mi = {};
                    mi.cbSize = sizeof(mi);
                    if (GetMonitorInfo(hMon, &mi) && !(mi.dwFlags & MONITORINFOF_PRIMARY)) {
                        MonitorInfo* pInfo = reinterpret_cast<MonitorInfo*>(lParam);
                        pInfo->rect = mi.rcMonitor;
                        pInfo->foundSecondary = true;
                        return FALSE; // stop after first secondary monitor found
                    }
                    return TRUE;
                }, reinterpret_cast<LPARAM>(&monInfo));

                cv::namedWindow(projectorWindowName, cv::WINDOW_NORMAL);

                if (monInfo.foundSecondary) {
                    int monX = monInfo.rect.left;
                    int monY = monInfo.rect.top;
                    int monW = monInfo.rect.right - monInfo.rect.left;
                    int monH = monInfo.rect.bottom - monInfo.rect.top;
                    cout << "Projector window -> secondary monitor at (" << monX << "," << monY
                         << ") " << monW << "x" << monH << endl;
                    cv::moveWindow(projectorWindowName, monX, monY);
                    cv::resizeWindow(projectorWindowName, monW, monH);
                    cv::setWindowProperty(projectorWindowName, cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
                } else {
                    cout << "Warning: No secondary monitor found; projector window on primary display." << endl;
                    cv::resizeWindow(projectorWindowName, 912, 1140);
                }

                while (!sharedCtx.stopRequested)
                {
                    unsigned int targetX = 0;
                    unsigned int targetY = 0;
                    bool blank = false;
                    bool enabled = false;

                    {
                        std::lock_guard<std::mutex> lock(sharedCtx.projectorMutex);
                        targetX = sharedCtx.projectorTargetX;
                        targetY = sharedCtx.projectorTargetY;
                        blank = sharedCtx.projectorBlank;
                        enabled = sharedCtx.projectorEnabled;
                    }

                    // Build frame using DLP SDK (show blank if projector is disabled)
                    dlp::ReturnCode ret = BuildFrame(targetX, targetY, blank || !enabled, &dlpFrame);
                    if (!ret.hasErrors()) {
                        // Convert dlp::Image to OpenCV Mat for preview window
                        ret = dlpFrame.GetOpenCVData(&displayMat);
                        if (!ret.hasErrors()) {
                            cv::imshow(projectorWindowName, displayMat);
                            cv::waitKey(1);
                        }
                    }

                    if (cv::getWindowProperty(projectorWindowName, cv::WND_PROP_VISIBLE) < 1)
                    {
                        break;
                    }

                    std::this_thread::sleep_for(std::chrono::milliseconds(16));  // ~60 Hz
                }

                cv::destroyWindow(projectorWindowName);
            }
            catch (const exception& e)
            {
                cerr << "Projector display thread error: " << e.what() << endl;
            }
        };

        // Lambda: Console command input thread — "cam cx cy" to aim projector at camera coords
        auto threadConsoleInput = [&]()
        {
            try
            {
                cout << "\n--- Projector Console ---" << endl;
                cout << "  cam <cx> <cy>  : aim at camera pixel (0-800, 0-600)" << endl;
                cout << "  blank          : blank projector output" << endl;
                cout << "  unblank        : restore projector output" << endl;
                cout << "  quit           : stop program" << endl;
                cout << "-------------------------" << endl;

                std::string line;
                while (!sharedCtx.stopRequested)
                {
                    cout << "proj> ";
                    if (!std::getline(std::cin, line))
                        break;

                    if (line.empty()) continue;

                    std::istringstream iss(line);
                    std::string token;
                    iss >> token;

                    if (token == "quit" || token == "q" || token == "exit")
                    {
                        sharedCtx.stopRequested = true;
                        sharedCtx.frameCV.notify_all();
                        break;
                    }
                    else if (token == "blank")
                    {
                        std::lock_guard<std::mutex> lock(sharedCtx.projectorMutex);
                        sharedCtx.projectorBlank = true;
                        cout << "Projector blanked." << endl;
                    }
                    else if (token == "unblank")
                    {
                        std::lock_guard<std::mutex> lock(sharedCtx.projectorMutex);
                        sharedCtx.projectorBlank = false;
                        cout << "Projector unblanked." << endl;
                    }
                    else if (token == "cam")
                    {
                        double cx = 0.0, cy = 0.0;
                        if (!(iss >> cx >> cy))
                        {
                            cout << "Usage: cam <cx> <cy>" << endl;
                        }
                        else
                        {
                            unsigned int px = 0, py = 0;
                            if (ApplyHomography(H, cx, cy, px, py))
                            {
                                std::lock_guard<std::mutex> lock(sharedCtx.projectorMutex);
                                sharedCtx.projectorTargetX = px;
                                sharedCtx.projectorTargetY = py;
                                sharedCtx.projectorBlank = false;
                                sharedCtx.projectorEnabled = true;
                                cout << "Camera (" << cx << ", " << cy << ") -> DMD (" << px << ", " << py << ")" << endl;
                            }
                            else
                            {
                                cout << "Homography transform failed (matrix not loaded?)." << endl;
                            }
                        }
                    }
                    else
                    {
                        cout << "Unknown command. Type 'cam cx cy', 'blank', 'unblank', or 'quit'." << endl;
                    }
                }
            }
            catch (const exception& e)
            {
                cerr << "Console input thread error: " << e.what() << endl;
            }
        };

        // Launch all threads
        std::thread thBottomCam(threadBottomCamera);
        std::thread thYolo([&]()
        {
            try
            {
                const string yolo_cfg     = "C:\\Users\\SeniorDesign\\Downloads\\darknet-master\\darknet-master\\flyHeadYolov4.cfg";
                const string yolo_weights = "C:\\Users\\SeniorDesign\\Downloads\\darknet-master\\darknet-master\\flyHead_final.weights";
                const float  yThresh      = 0.9F;

                Detector detector(yolo_cfg, yolo_weights);
                std::vector<bbox_t> detect_vec;
                int consecutiveBodyMisses = 0;
                bool hasLastKnownBody = false;
                Point2f lastKnownDist(0.0f, 0.0f);
                std::deque<Point2f> recentBodyOffsets;
                int bodyDetectionCount = 0;

                cout << "YOLO detector loaded." << endl;

                while (!sharedCtx.stopRequested)
                {
                    Mat frame;
                    if (!yoloFrameQueue.try_pop(frame))
                    {
                        std::this_thread::sleep_for(std::chrono::milliseconds(1));
                        continue;
                    }

                    // Always process the most recent frame to keep control responsive.
                    // Draining avoids queue buildup and keeps YOLO from lagging behind live motion.
                    Mat latestFrame;
                    while (yoloFrameQueue.try_pop(latestFrame))
                    {
                        frame = latestFrame;
                    }

                    // Downsample the camera frame before inference to reduce YOLO cost.
                    Mat yoloFrame;
                    resize(frame, yoloFrame, Size(kYoloInputWidth, kYoloInputHeight), 0.0, 0.0, INTER_AREA);

                    detect_vec = detector.detect(yoloFrame, yThresh);

                    const float scaleX = static_cast<float>(frame.cols) / static_cast<float>(kYoloInputWidth);
                    const float scaleY = static_cast<float>(frame.rows) / static_cast<float>(kYoloInputHeight);

                    bool bodyFound = false;
                    bool headFound = false;
                    Point newBodyCoM, newHeadCoM;
                    Rect  newBodyBox, newHeadBox;

                    for (const auto& bb : detect_vec)
                    {
                        // obj_id 1 = body, obj_id 0 = head  (same convention as V2)
                        if (bb.obj_id == 1 || bb.obj_id == 0)
                        {
                            const int scaledX = static_cast<int>(std::round(static_cast<float>(bb.x) * scaleX));
                            const int scaledY = static_cast<int>(std::round(static_cast<float>(bb.y) * scaleY));
                            const int scaledW = static_cast<int>(std::round(static_cast<float>(bb.w) * scaleX));
                            const int scaledH = static_cast<int>(std::round(static_cast<float>(bb.h) * scaleY));
                            const int scaledCx = scaledX + scaledW / 2;
                            const int scaledCy = scaledY + scaledH / 2;
                            if (bb.obj_id == 1)
                            {
                                newBodyCoM = Point(scaledCx, scaledCy);
                                newBodyBox = Rect(scaledX, scaledY, scaledW, scaledH);
                                bodyFound = true;
                            }
                            else
                            {
                                newHeadCoM = Point(scaledCx, scaledCy);
                                newHeadBox = Rect(scaledX, scaledY, scaledW, scaledH);
                                headFound = true;
                            }
                        }
                    }

                    // V2-style filter flow: measure distance from frame center, then Predict/Correct
                    {
                        std::lock_guard<std::mutex> lock(sharedCtx.yoloMutex);
                        sharedCtx.flyDetectedFresh = bodyFound;
                        sharedCtx.filter.Predict();

                        if (bodyFound)
                        {
                            consecutiveBodyMisses = 0;
                            hasLastKnownBody = true;
                            // Map camera pixel error to gantry control axes (X/Y swapped).
                            Point2f currentDist(
                                static_cast<float>(newBodyCoM.y - frame.rows / 2),
                                static_cast<float>(newBodyCoM.x - frame.cols / 2));

                            // Smooth command point: average center offset from the last N detections.
                            recentBodyOffsets.push_back(currentDist);
                            while (recentBodyOffsets.size() > kCenterAverageWindow)
                            {
                                recentBodyOffsets.pop_front();
                            }

                            Point2f avgDist(0.0f, 0.0f);
                            for (const Point2f& d : recentBodyOffsets)
                            {
                                avgDist += d;
                            }
                            avgDist.x /= static_cast<float>(recentBodyOffsets.size());
                            avgDist.y /= static_cast<float>(recentBodyOffsets.size());
                            lastKnownDist = avgDist;

                            bodyDetectionCount++;
                            //Prints the fly's offset from the camera center every 30 detections
                            // if (bodyDetectionCount % 30 == 0)
                            // {
                            //     cout << "Fly offset from camera center (px): X="
                            //          << lastKnownDist.x << " Y=" << lastKnownDist.y << endl;
                            // }
                            sharedCtx.filter.Correct(lastKnownDist);
                            sharedCtx.estDist = sharedCtx.filter.statePt_pos;
                            sharedCtx.estVel = sharedCtx.filter.statePt_vel;
                            sharedCtx.flyDetected = true;
                            sharedCtx.bodyCoM = newBodyCoM;
                            sharedCtx.bodyBox = newBodyBox;
                        }
                        else
                        {
                            if (hasLastKnownBody && consecutiveBodyMisses < kFlyMissHoldFrames)
                            {
                                // Keep using last known fly location while detector briefly drops out.
                                consecutiveBodyMisses++;
                                sharedCtx.filter.Correct(lastKnownDist);
                                sharedCtx.estDist = sharedCtx.filter.statePt_pos;
                                sharedCtx.estVel = sharedCtx.filter.statePt_vel;
                                sharedCtx.flyDetected = true;
                            }
                            else
                            {
                                sharedCtx.filter.Init(Point2f(0.0f, 0.0f));
                                sharedCtx.estDist = Point2f(0.0f, 0.0f);
                                sharedCtx.estVel = Point2f(0.0f, 0.0f);
                                sharedCtx.flyDetected = false;
                                recentBodyOffsets.clear();
                            }
                        }

                        sharedCtx.headDetected = headFound;
                        if (headFound) { sharedCtx.headCoM = newHeadCoM; sharedCtx.headBox = newHeadBox; }
                    }
                }
            }
            catch (const exception& e)
            {
                cerr << "YOLO thread error: " << e.what() << endl;
            }
        });

        std::thread thSideCam(threadSideCamera);
        std::thread thInput(threadManualInput);
        std::thread thSave(threadDataSave);
        std::thread thProjector([&]() { threadProjectorDisplay(H); });
        std::thread thConsole(threadConsoleInput);

        auto accumulatedSaveDuration = std::chrono::steady_clock::duration::zero();
        bool saveTimerRunning = false;
        auto saveTimerStart = std::chrono::steady_clock::now();

        // Main thread handles display (OpenCV requires main thread for imshow/waitKey)
        while (!sharedCtx.stopRequested)
        {
            Mat bottomFrame;
            if (!displayBottomFrameQueue.try_pop(bottomFrame))
            {
                if (sharedCtx.stopRequested)
                    break;
                waitKey(1);
                continue;
            }

            Mat sideFrame;
            {
                std::lock_guard<std::mutex> lock(sharedCtx.frameMutex);
                sideFrame = sharedCtx.sideFrame.clone();
            }

            if (bottomFrame.empty())
                continue;

            Point2f velocity;
            {
                std::lock_guard<std::mutex> lock(sharedCtx.velocityMutex);
                velocity = sharedCtx.manualVelocity;
            }

            Mat displayFrame;
            cvtColor(bottomFrame, displayFrame, COLOR_GRAY2BGR);
            putText(displayFrame, "BOTTOM CAMERA", Point(20, bottomFrame.rows - 20), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 255, 0), 2);
            line(displayFrame, Point(bottomFrame.cols / 2 - 15, bottomFrame.rows / 2), Point(bottomFrame.cols / 2 + 15, bottomFrame.rows / 2), Scalar(0, 255, 255), 1);
            line(displayFrame, Point(bottomFrame.cols / 2, bottomFrame.rows / 2 - 15), Point(bottomFrame.cols / 2, bottomFrame.rows / 2 + 15), Scalar(0, 255, 255), 1);

            bool saveEnabled;
            {
                std::lock_guard<std::mutex> lock(sharedCtx.saveMutex);
                saveEnabled = sharedCtx.saveEnabled;
            }

            const auto now = std::chrono::steady_clock::now();
            if (saveEnabled && !saveTimerRunning)
            {
                saveTimerStart = now;
                saveTimerRunning = true;
            }
            else if (!saveEnabled && saveTimerRunning)
            {
                accumulatedSaveDuration += (now - saveTimerStart);
                saveTimerRunning = false;
            }

            auto displayedSaveDuration = accumulatedSaveDuration;
            if (saveTimerRunning)
            {
                displayedSaveDuration += (now - saveTimerStart);
            }

            putText(displayFrame, saveEnabled ? "SAVING" : "NOT SAVING", Point(20, 30), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 200, 255), 2);
            putText(displayFrame, sharedCtx.autoTrackEnabled ? "AUTO (M to toggle)" : "Manual: Arrows/IJKL | M=auto", Point(20, 55), FONT_HERSHEY_SIMPLEX, 0.5, sharedCtx.autoTrackEnabled ? Scalar(0, 255, 0) : Scalar(255, 255, 255), 1);
            putText(displayFrame, "Vel(mm/s): X=" + to_string(static_cast<int>(velocity.x)) + " Y=" + to_string(static_cast<int>(velocity.y)), Point(20, 80), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(255, 255, 255), 1);

            // --- YOLO detection overlay ---
            bool yoloFlyDetected, yoloHeadDetected;
            Point yoloBodyCoM, yoloHeadCoM;
            Rect  yoloBodyBox, yoloHeadBox;
            {
                std::lock_guard<std::mutex> lock(sharedCtx.yoloMutex);
                yoloFlyDetected  = sharedCtx.flyDetected;
                yoloHeadDetected = sharedCtx.headDetected;
                yoloBodyCoM = sharedCtx.bodyCoM;
                yoloHeadCoM = sharedCtx.headCoM;
                yoloBodyBox = sharedCtx.bodyBox;
                yoloHeadBox = sharedCtx.headBox;
            }

            if (yoloFlyDetected)
            {
                // Body bounding box in green, center dot
                rectangle(displayFrame, yoloBodyBox, Scalar(0, 255, 0), 2);
                circle(displayFrame, yoloBodyCoM, 5, Scalar(0, 255, 0), cv::FILLED);
                putText(displayFrame, "BODY", Point(yoloBodyBox.x, yoloBodyBox.y - 5),
                        FONT_HERSHEY_SIMPLEX, 0.45, Scalar(0, 255, 0), 1);
            }
            if (yoloHeadDetected)
            {
                // Head bounding box in cyan, center dot
                rectangle(displayFrame, yoloHeadBox, Scalar(255, 255, 0), 2);
                circle(displayFrame, yoloHeadCoM, 4, Scalar(255, 255, 0), cv::FILLED);
                putText(displayFrame, "HEAD", Point(yoloHeadBox.x, yoloHeadBox.y - 5),
                        FONT_HERSHEY_SIMPLEX, 0.45, Scalar(255, 255, 0), 1);
            }

            // Detection status banner
            if (yoloFlyDetected || yoloHeadDetected)
            {
                putText(displayFrame, "FLY DETECTED", Point(20, 110),
                        FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
            }
            else
            {
                putText(displayFrame, "FLY NOT DETECTED", Point(20, 110),
                        FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 255), 2);
            }

            Mat sideDisplay = Mat::zeros(displayFrame.size(), CV_8UC3);
            if (sideCamera && !sideFrame.empty())
            {
                Mat sideBgr;
                cvtColor(sideFrame, sideBgr, COLOR_GRAY2BGR);
                if (sideBgr.size() != displayFrame.size())
                {
                    resize(sideBgr, sideBgr, displayFrame.size(), 0.0, 0.0, INTER_LINEAR);
                }
                sideDisplay = sideBgr;
            }
            putText(sideDisplay, "SIDE CAMERA", Point(20, sideDisplay.rows - 20), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 255, 0), 2);
            if (!sideCamera)
            {
                putText(sideDisplay, "NOT DETECTED", Point(20, 40), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0, 200, 255), 2);
            }

            Mat combinedDisplay;
            hconcat(displayFrame, sideDisplay, combinedDisplay);

            const int controlPanelHeight = 72;
            Mat uiDisplay(combinedDisplay.rows + controlPanelHeight, combinedDisplay.cols, CV_8UC3, Scalar(25, 25, 25));
            combinedDisplay.copyTo(uiDisplay(Rect(0, 0, combinedDisplay.cols, combinedDisplay.rows)));

            const int buttonWidth = 140;
            const int buttonHeight = 36;
            const int buttonGap = 16;
            const int panelTop = combinedDisplay.rows;
            const int buttonY = panelTop + (controlPanelHeight - buttonHeight) / 2;
            const int exitButtonX = uiDisplay.cols - buttonWidth - 20;
            const int stopButtonX = exitButtonX - buttonGap - buttonWidth;
            const Rect stopButtonRect(stopButtonX, buttonY, buttonWidth, buttonHeight);
            const Rect exitButtonRect(exitButtonX, buttonY, buttonWidth, buttonHeight);

            {
                std::lock_guard<std::mutex> lock(stopButtonUi.mutex);
                stopButtonUi.stopButtonRect = stopButtonRect;
                stopButtonUi.exitButtonRect = exitButtonRect;
            }

            putText(uiDisplay,
                    "RUN TIME (saving): " + formatDurationHMS(displayedSaveDuration),
                    Point(20, panelTop + 45),
                    FONT_HERSHEY_SIMPLEX,
                    0.7,
                    saveEnabled ? Scalar(0, 255, 255) : Scalar(180, 180, 180),
                    2);

            rectangle(uiDisplay, stopButtonRect, Scalar(30, 30, 200), cv::FILLED);
            rectangle(uiDisplay, stopButtonRect, Scalar(220, 220, 255), 1);
            putText(uiDisplay, "STOP", Point(stopButtonX + 38, buttonY + 24), FONT_HERSHEY_SIMPLEX, 0.65, Scalar(255, 255, 255), 2);

            rectangle(uiDisplay, exitButtonRect, Scalar(70, 70, 70), cv::FILLED);
            rectangle(uiDisplay, exitButtonRect, Scalar(220, 220, 220), 1);
            putText(uiDisplay, "EXIT", Point(exitButtonX + 42, buttonY + 24), FONT_HERSHEY_SIMPLEX, 0.65, Scalar(255, 255, 255), 2);

            imshow("camera feeds", uiDisplay);
            int key = waitKey(1);
            if (key == VK_ESCAPE)
            {
                sharedCtx.stopRequested = true;
            }

            if (ConsumeStopButtonClick(stopButtonUi))
            {
                cout << "STOP button pressed: halting gantry and stopping data collection." << endl;
                if (motors)
                {
                    motors->SetVelocity(Point2f(0.0f, 0.0f), Point2f(0.0f, 0.0f), false);
                }
                {
                    std::lock_guard<std::mutex> lock(sharedCtx.saveMutex);
                    sharedCtx.saveEnabled = false;
                }
            }

            if (ConsumeExitButtonClick(stopButtonUi))
            {
                cout << "EXIT button pressed: halting gantry, stopping data collection, and exiting." << endl;
                if (motors)
                {
                    motors->SetVelocity(Point2f(0.0f, 0.0f), Point2f(0.0f, 0.0f), false);
                }
                {
                    std::lock_guard<std::mutex> lock(sharedCtx.saveMutex);
                    sharedCtx.saveEnabled = false;
                }
                sharedCtx.stopRequested = true;
            }
        }

        // Signal threads to stop
        sharedCtx.stopRequested = true;
        sharedCtx.frameCV.notify_all();

        // Wait for all threads to finish
        thBottomCam.join();
        thSideCam.join();
        thInput.join();
        thSave.join();
        thProjector.join();
        thYolo.join();
        thConsole.detach();  // console thread may be blocked on getline; detach to avoid hang

        bottomCamera.StopGrabbing();
        bottomCamera.Close();
        if (sideCamera)
        {
            sideCamera->StopGrabbing();
            sideCamera->Close();
        }
    }
    catch (const GenericException& e)
    {
        fatalError = true;
        cerr << "An exception occurred." << endl << e.GetDescription() << endl;
        cerr << "Last step: " << lastStep << endl;
    }
    catch (const exception& e)
    {
        fatalError = true;
        cerr << "Fatal error: " << e.what() << endl;
        cerr << "Last step: " << lastStep << endl;
    }
    catch (...)
    {
        fatalError = true;
        cerr << "Fatal unknown error." << endl;
        cerr << "Last step: " << lastStep << endl;
    }

    if (writer.isOpened())
    {
        writer.release();
    }
    if (sideWriter.isOpened())
    {
        sideWriter.release();
    }
    if (yoloWriter.isOpened())
    {
        yoloWriter.release();
    }

    textOut.close();

    ofstream metaOut(metaFileName, ofstream::out);
    if (!metaOut.is_open())
    {
        cerr << "Warning: could not open meta CSV for writing: " << metaFileName << endl;
    }
    metaOut << "# NOTE: Optostim output fields are not populated in this system version (optostim removed).\n";
    metaOut
        << "Arena center coordinate X," << "Arena Center coordinate Y," << "Arena Radius," << "Object space resolution,"
        << "Ending Optogenetic Stimulation Center X," << "Ending Optogenetic Stimulation Center Y," << "Optogenetic Stimulation Radius,"
        << "Stimulus Type," << "Optogenetic Stimulus Slope," << "Optogenetic Stimulus Width," << "Stimulus Voltage," << "Yolo,"
        << "Optogenetic Inner Circle Radius\n";

    metaOut
        << 0 << "," << 0 << "," << 0 << "," << kObjectSpaceResolutionUmPerPixel << ","
        << 0 << "," << 0 << "," << 0 << ","
        << 0 << "," << 0 << "," << 0 << ","
        << 0 << "," << "Yes" << "," << 0;
    metaOut.close();
    cout << "Saved meta CSV to: " << metaFileName << endl;

    if (matSaveData)
    {
        matSaveData->saveMatFile();
        cout << "Saved MAT file to: " << matFileName << endl;
    }

    if (motors)
    {
        motors->SetVelocity(Point2f(0.0f, 0.0f), Point2f(0.0f, 0.0f), false);
    }
    if (pylonInitialized)
    {
        PylonTerminate();
    }

    if (!fatalError)
    {
        cout << "session complete" << endl;
    }
    return fatalError ? 1 : 0;
}
