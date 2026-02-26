#include <pylon/PylonIncludes.h>
#ifdef PYLON_WIN_BUILD
#    include <pylon/PylonGUI.h> 
#endif
#include <pylon/usb/BaslerUsbInstantCamera.h>
#include "../HardwareTriggerConfiguration.h"

#include <opencv2/opencv.hpp>
#include <iostream>
#include <concurrent_queue.h>

using namespace std;
using namespace cv;
using namespace concurrency;
using namespace Pylon;
using namespace GenApi;
using namespace Basler_UsbCameraParams;

// Global queue for passing frames from camera to display
concurrent_queue<Mat> flyStreamRaw;

// Structure to hold chunk data from camera
struct chunkDataStruc {
    int grabSucceeded;
    int imageDamaged;
    unsigned long dataNum;
    unsigned long long timeStampChunk;
} chunkStruc;

unsigned long imgCnt = 0; // Image counter

// Image event handler class for capturing frames from bottom camera
class CImageEventPrinter : public Pylon::CImageEventHandler
{
public:
    Pylon::CImageFormatConverter formatConverter;
    
    CImageEventPrinter()
    {
        formatConverter.OutputPixelFormat = Pylon::PixelType_Mono8;
    }

    virtual void OnImageGrabbed(Pylon::CInstantCamera& camera, const Pylon::CGrabResultPtr& ptrGrabResult)
    {
        if (ptrGrabResult->GrabSucceeded())
        {
            chunkStruc.grabSucceeded = int(ptrGrabResult->GrabSucceeded());
            
            if (ptrGrabResult->HasCRC() && ptrGrabResult->CheckCRC() == false)
            {
                chunkStruc.imageDamaged = 1; // IMAGE DAMAGED
            }
            else
            {
                chunkStruc.imageDamaged = 0; // IMAGE OK
            }

            // Get timestamp from chunk data
            if (IsReadable(ptrGrabResult->ChunkTimestamp))
            {
                chunkStruc.timeStampChunk = ptrGrabResult->ChunkTimestamp.GetValue();
            }

            chunkStruc.dataNum = imgCnt;
            imgCnt++;

            // Convert image to OpenCV Mat and push to display queue
            Pylon::CPylonImage pylonImage;
            formatConverter.Convert(pylonImage, ptrGrabResult);
            Mat opencvImage = Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), CV_8UC1, (uint8_t*)pylonImage.GetBuffer());
            
            flyStreamRaw.push(opencvImage.clone());
        }
    }
};

int main()
{
    cout << "---------------------------------" << endl;
    cout << "Bottom Camera Display" << endl;
    cout << "---------------------------------" << endl;

    // Initialize Pylon
    PylonInitialize();
    
    try
    {
        // Create bottom camera instance
        CBaslerUsbInstantCamera camera(CTlFactory::GetInstance().CreateFirstDevice());
        cout << "Using device: " << camera.GetDeviceInfo().GetModelName() << endl;
        
        // Register hardware trigger configuration
        camera.RegisterConfiguration(new CHardwareTriggerConfiguration, RegistrationMode_ReplaceAll, Cleanup_Delete);
        
        // Register image event handler for processing grabbed frames
        camera.RegisterImageEventHandler(new CImageEventPrinter, RegistrationMode_Append, Cleanup_Delete);

        // Open the camera
        camera.Open();

        // Configure camera parameters
        camera.ExposureTime.SetValue(1000.0);
        camera.SensorReadoutMode.SetValue(SensorReadoutMode_Fast);
        camera.Width.SetValue(592);
        camera.Height.SetValue(600);
        camera.OffsetX.SetValue(112);
        camera.OffsetY.SetValue(16);
        camera.ReverseX.SetValue(true);

        // Enable chunk mode for metadata
        camera.ChunkModeActive.SetValue(true);
        camera.ChunkSelector.SetValue(ChunkSelector_Timestamp);
        camera.ChunkEnable.SetValue(true);
        camera.ChunkSelector.SetValue(ChunkSelector_PayloadCRC16);
        camera.ChunkEnable.SetValue(true);
        
        camera.MaxNumBuffer = 500;

        // Start grabbing frames
        camera.StartGrabbing(GrabStrategy_OneByOne, GrabLoop_ProvidedByInstantCamera);
        
        cout << "Camera started. Press ESC to exit." << endl;

        // Create display window
        namedWindow("Bottom Camera View", WINDOW_AUTOSIZE);
        
        Mat frame;
        bool running = true;

        // Main display loop
        while (running && camera.IsGrabbing())
        {
            // Try to get frame from queue
            if (flyStreamRaw.try_pop(frame))
            {
                imshow("Bottom Camera View", frame);
                cout << "Frame " << imgCnt << " displayed" << endl;
            }
            
            // Check for ESC key to exit
            int key = waitKey(1);
            if (key == 27) // ESC key
            {
                running = false;
            }
        }

        // Cleanup
        camera.StopGrabbing();
        camera.Close();
        destroyAllWindows();
        
        cout << "Camera stopped. Total frames: " << imgCnt << endl;
    }
    catch (const GenericException& e)
    {
        cerr << "Pylon exception: " << e.GetDescription() << endl;
        return 1;
    }

    PylonTerminate();
    
    return 0;
}
