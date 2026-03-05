#include <pylon/PylonIncludes.h>
#ifdef PYLON_WIN_BUILD
#include <pylon/PylonGUI.h> 
#endif
#include <pylon/usb/BaslerUsbInstantCamera.h>
#include "../HardwareTriggerConfiguration.h"

#include <opencv2/opencv.hpp>
#include <iostream>
#include <concurrent_queue.h>
#include <thread>
#include <atomic>

using namespace std;
using namespace cv;
using namespace concurrency;
using namespace Pylon;
using namespace GenApi;
using namespace Basler_UsbCameraParams;

// Global queues for passing frames from cameras to display
concurrent_queue<Mat> camera1FrameQueue;
concurrent_queue<Mat> camera2FrameQueue;

// Atomic flags for thread synchronization
atomic<bool> running(true);

// Camera data structures
struct CameraData {
    int grabSucceeded;
    int imageDamaged;
    unsigned long frameCount;
    unsigned long long timeStampChunk;
};

CameraData camera1Data = {0, 0, 0, 0};
CameraData camera2Data = {0, 0, 0, 0};

// Image event handler for Camera 1
class CCamera1ImageHandler : public Pylon::CImageEventHandler
{
public:
    Pylon::CImageFormatConverter formatConverter;
    
    CCamera1ImageHandler()
    {
        formatConverter.OutputPixelFormat = Pylon::PixelType_Mono8;
    }

    virtual void OnImageGrabbed(Pylon::CInstantCamera& camera, const Pylon::CGrabResultPtr& ptrGrabResult)
    {
        if (ptrGrabResult->GrabSucceeded())
        {
            camera1Data.grabSucceeded = int(ptrGrabResult->GrabSucceeded());
            
            if (ptrGrabResult->HasCRC() && ptrGrabResult->CheckCRC() == false)
            {
                camera1Data.imageDamaged = 1;
            }
            else
            {
                camera1Data.imageDamaged = 0;
            }

            // Use TimeStamp instead of ChunkTimestamp (compatible with all Pylon versions)
            if (ptrGrabResult->GetTimeStamp() != 0)
            {
                camera1Data.timeStampChunk = ptrGrabResult->GetTimeStamp();
            }

            camera1Data.frameCount++;

            // Convert to OpenCV Mat
            Pylon::CPylonImage pylonImage;
            formatConverter.Convert(pylonImage, ptrGrabResult);
            Mat opencvImage = Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), 
                                 CV_8UC1, (uint8_t*)pylonImage.GetBuffer());
            
            camera1FrameQueue.push(opencvImage.clone());
        }
    }
};

// Image event handler for Camera 2
class CCamera2ImageHandler : public Pylon::CImageEventHandler
{
public:
    Pylon::CImageFormatConverter formatConverter;
    
    CCamera2ImageHandler()
    {
        formatConverter.OutputPixelFormat = Pylon::PixelType_Mono8;
    }

    virtual void OnImageGrabbed(Pylon::CInstantCamera& camera, const Pylon::CGrabResultPtr& ptrGrabResult)
    {
        if (ptrGrabResult->GrabSucceeded())
        {
            camera2Data.grabSucceeded = int(ptrGrabResult->GrabSucceeded());
            
            if (ptrGrabResult->HasCRC() && ptrGrabResult->CheckCRC() == false)
            {
                camera2Data.imageDamaged = 1;
            }
            else
            {
                camera2Data.imageDamaged = 0;
            }

            // Use TimeStamp instead of ChunkTimestamp (compatible with all Pylon versions)
            if (ptrGrabResult->GetTimeStamp() != 0)
            {
                camera2Data.timeStampChunk = ptrGrabResult->GetTimeStamp();
            }

            camera2Data.frameCount++;

            // Convert to OpenCV Mat
            Pylon::CPylonImage pylonImage;
            formatConverter.Convert(pylonImage, ptrGrabResult);
            Mat opencvImage = Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), 
                                 CV_8UC1, (uint8_t*)pylonImage.GetBuffer());
            
            camera2FrameQueue.push(opencvImage.clone());
        }
    }
};

// Function to enumerate and list all Basler cameras
int ListBaslerCameras()
{
    try
    {
        PylonInitialize();
        DeviceInfoList_t devices;
        CTlFactory::GetInstance().EnumerateDevices(devices);
        
        cout << "\n=== Basler Cameras Found ===" << endl;
        cout << "Total Basler cameras: " << devices.size() << endl;
        
        if (devices.size() == 0)
        {
            cout << "ERROR: No Basler cameras found!" << endl;
            cout << "Please check:" << endl;
            cout << "  1. Camera is connected via USB" << endl;
            cout << "  2. Camera is powered on" << endl;
            cout << "  3. Pylon SDK is installed correctly" << endl;
            PylonTerminate();
            return 0;
        }
        
        for (size_t i = 0; i < devices.size(); i++)
        {
            cout << "  [" << i << "] " 
                 << devices[i].GetFriendlyName() 
                 << " (Serial: " << devices[i].GetSerialNumber() << ")" << endl;
        }
        
        PylonTerminate();
        return devices.size();
    }
    catch (const GenericException& e)
    {
        cerr << "Error enumerating Basler cameras: " << e.GetDescription() << endl;
        return 0;
    }
}

// Thread function for Camera 1
void Camera1Thread(int cameraIndex)
{
    try
    {
        PylonInitialize();
        
        DeviceInfoList_t devices;
        CTlFactory::GetInstance().EnumerateDevices(devices);
        
        if (cameraIndex >= devices.size())
        {
            cerr << "Camera 1 index " << cameraIndex << " out of range!" << endl;
            PylonTerminate();
            return;
        }
        
        cout << "\nOpening Camera 1 [" << cameraIndex << "]: " 
             << devices[cameraIndex].GetFriendlyName() 
             << " (Serial: " << devices[cameraIndex].GetSerialNumber() << ")" << endl;
        
        CBaslerUsbInstantCamera camera(CTlFactory::GetInstance().CreateDevice(devices[cameraIndex]));
        
        camera.RegisterConfiguration(new CHardwareTriggerConfiguration, 
                                     RegistrationMode_ReplaceAll, Cleanup_Delete);
        camera.RegisterImageEventHandler(new CCamera1ImageHandler, 
                                         RegistrationMode_Append, Cleanup_Delete);
        
        camera.Open();
        
        // Configure camera parameters - Bottom camera settings from original code
        camera.ExposureTime.SetValue(1000.0);
        camera.SensorReadoutMode.SetValue(SensorReadoutMode_Fast);
        camera.Width.SetValue(592);
        camera.Height.SetValue(600);
        camera.OffsetX.SetValue(112);
        camera.OffsetY.SetValue(16);
        camera.ReverseX.SetValue(true);
        
        camera.ChunkModeActive.SetValue(true);
        camera.ChunkSelector.SetValue(ChunkSelector_Timestamp);
        camera.ChunkEnable.SetValue(true);
        camera.ChunkSelector.SetValue(ChunkSelector_PayloadCRC16);
        camera.ChunkEnable.SetValue(true);
        
        camera.MaxNumBuffer = 500;
        
        camera.StartGrabbing(GrabStrategy_OneByOne, GrabLoop_ProvidedByInstantCamera);
        
        cout << "Camera 1 started successfully (Resolution: 592x600)" << endl;
        
        while (running && camera.IsGrabbing())
        {
            this_thread::sleep_for(chrono::milliseconds(100));
        }
        
        camera.StopGrabbing();
        camera.Close();
        
        PylonTerminate();
        
        cout << "Camera 1 stopped. Total frames: " << camera1Data.frameCount << endl;
    }
    catch (const GenericException& e)
    {
        cerr << "Camera 1 error: " << e.GetDescription() << endl;
    }
}

// Thread function for Camera 2
void Camera2Thread(int cameraIndex)
{
    try
    {
        PylonInitialize();
        
        DeviceInfoList_t devices;
        CTlFactory::GetInstance().EnumerateDevices(devices);
        
        if (cameraIndex >= devices.size())
        {
            cerr << "Camera 2 index " << cameraIndex << " out of range!" << endl;
            PylonTerminate();
            return;
        }
        
        cout << "Opening Camera 2 [" << cameraIndex << "]: " 
             << devices[cameraIndex].GetFriendlyName()
             << " (Serial: " << devices[cameraIndex].GetSerialNumber() << ")" << endl;
        
        CBaslerUsbInstantCamera camera(CTlFactory::GetInstance().CreateDevice(devices[cameraIndex]));
        
        camera.RegisterConfiguration(new CHardwareTriggerConfiguration, 
                                     RegistrationMode_ReplaceAll, Cleanup_Delete);
        camera.RegisterImageEventHandler(new CCamera2ImageHandler, 
                                         RegistrationMode_Append, Cleanup_Delete);
        
        camera.Open();
        
        // Configure camera parameters - Can be different from Camera 1 if needed
        camera.ExposureTime.SetValue(1000.0);
        camera.SensorReadoutMode.SetValue(SensorReadoutMode_Fast);
        camera.Width.SetValue(592);
        camera.Height.SetValue(600);
        camera.OffsetX.SetValue(112);
        camera.OffsetY.SetValue(16);
        camera.ReverseX.SetValue(true);
        
        camera.ChunkModeActive.SetValue(true);
        camera.ChunkSelector.SetValue(ChunkSelector_Timestamp);
        camera.ChunkEnable.SetValue(true);
        camera.ChunkSelector.SetValue(ChunkSelector_PayloadCRC16);
        camera.ChunkEnable.SetValue(true);
        
        camera.MaxNumBuffer = 500;
        
        camera.StartGrabbing(GrabStrategy_OneByOne, GrabLoop_ProvidedByInstantCamera);
        
        cout << "Camera 2 started successfully (Resolution: 592x600)" << endl;
        
        while (running && camera.IsGrabbing())
        {
            this_thread::sleep_for(chrono::milliseconds(100));
        }
        
        camera.StopGrabbing();
        camera.Close();
        
        PylonTerminate();
        
        cout << "Camera 2 stopped. Total frames: " << camera2Data.frameCount << endl;
    }
    catch (const GenericException& e)
    {
        cerr << "Camera 2 error: " << e.GetDescription() << endl;
    }
}

int main()
{
    cout << "========================================" << endl;
    cout << "Dual Basler Camera Display" << endl;
    cout << "========================================" << endl;
    
    // List all available Basler cameras
    int numCameras = ListBaslerCameras();
    
    if (numCameras < 2)
    {
        cout << "\nERROR: Need at least 2 Basler cameras connected!" << endl;
        cout << "Found: " << numCameras << " camera(s)" << endl;
        cout << "\nOptions:" << endl;
        cout << "  - Connect a second Basler camera" << endl;
        cout << "  - Use bottom_camera_display.exe for single camera" << endl;
        cout << "\nPress any key to exit..." << endl;
        cin.get();
        return 1;
    }
    
    cout << "\n========================================" << endl;
    
    // Get user input for camera selection
    int camera1Index = 0;
    int camera2Index = 1;
    
    cout << "\nSelect cameras to use:" << endl;
    cout << "Enter Camera 1 index (default 0): ";
    string input;
    getline(cin, input);
    if (!input.empty())
    {
        camera1Index = stoi(input);
    }
    
    cout << "Enter Camera 2 index (default 1): ";
    getline(cin, input);
    if (!input.empty())
    {
        camera2Index = stoi(input);
    }
    
    if (camera1Index == camera2Index)
    {
        cout << "\nWARNING: Both cameras set to same index [" << camera1Index << "]" << endl;
        cout << "This may cause conflicts. Consider using different indices." << endl;
        cout << "Continue anyway? (y/n): ";
        getline(cin, input);
        if (input != "y" && input != "Y")
        {
            return 1;
        }
    }
    
    cout << "\nStarting cameras..." << endl;
    cout << "  Camera 1 index: " << camera1Index << endl;
    cout << "  Camera 2 index: " << camera2Index << endl;
    cout << "\nPress ESC in either window to exit" << endl;
    
    // Start camera threads
    thread cam1Thread(Camera1Thread, camera1Index);
    thread cam2Thread(Camera2Thread, camera2Index);
    
    // Give cameras time to initialize
    this_thread::sleep_for(chrono::seconds(2));
    
    // Create display windows
    namedWindow("Camera 1", WINDOW_AUTOSIZE);
    namedWindow("Camera 2", WINDOW_AUTOSIZE);
    
    Mat camera1Frame, camera2Frame;
    
    cout << "\nBoth cameras running. Displaying frames..." << endl;
    cout << "Frame counts - Camera 1: 0 | Camera 2: 0" << flush;
    
    int displayCounter = 0;
    
    // Main display loop
    while (running)
    {
        bool frameDisplayed = false;
        
        // Display Camera 1 frames
        if (camera1FrameQueue.try_pop(camera1Frame))
        {
            imshow("Camera 1", camera1Frame);
            frameDisplayed = true;
        }
        
        // Display Camera 2 frames
        if (camera2FrameQueue.try_pop(camera2Frame))
        {
            imshow("Camera 2", camera2Frame);
            frameDisplayed = true;
        }
        
        // Update frame counter display every 30 iterations
        if (displayCounter++ % 30 == 0)
        {
            cout << "\rFrame counts - Camera 1: " << camera1Data.frameCount 
                 << " | Camera 2: " << camera2Data.frameCount << flush;
        }
        
        // Handle keyboard input
        int key = waitKey(1);
        if (key == 27) // ESC key
        {
            cout << "\n\nESC pressed - stopping cameras..." << endl;
            running = false;
        }
        
        // Small delay if no frames
        if (!frameDisplayed)
        {
            this_thread::sleep_for(chrono::milliseconds(10));
        }
    }
    
    // Cleanup
    cout << "Waiting for camera threads to finish..." << endl;
    
    cam1Thread.join();
    cam2Thread.join();
    
    destroyAllWindows();
    
    cout << "\n========================================" << endl;
    cout << "Final Statistics:" << endl;
    cout << "  Camera 1: " << camera1Data.frameCount << " frames captured" << endl;
    cout << "  Camera 2: " << camera2Data.frameCount << " frames captured" << endl;
    cout << "========================================" << endl;
    cout << "\nProgram finished." << endl;
    
    return 0;
}
