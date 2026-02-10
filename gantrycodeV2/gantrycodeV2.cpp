/*
gantryCode.cpp: This file contains the main(). Program execution begins and ends there.
This project includes the following libraries:
1, OpenCV + OpenMP custom built library
2, US Digital's USB4 library
3, Spinnakr SDK library for the pointgrey camera(top)
4, Basler SDK library
*/

////// Include The Necessary Header Files in The Local Directory://////
// '#include' tells the preprocessor to treat the contents of these specified files as if 
//they appear in the source program at the point where the directive appears

/*
#include <conio.h>
#include <math.h>//For all the math functions
#include <iostream>// For cout, input output stream heade
#include <string> 
#include <ctime> // localtime
#include <iomanip> // put_time
#include <sstream> // stringstream
#include "windows.h"// windows API,communicate with windows. For BOOL, TRUE...
#include <chrono>

#include "stdio.h"
#include <fstream>
#include <algorithm> 
#include <stdlib.h> // standard library header. 

//---Hardware part---//
// The DAQ reads the encoder info from the decoder and modulates the proportional control of the motors.
#include "USB4.h" // USB4 is the DECODER. The decoder interprets the encoder quadrative signal, counting the marks it has passed and calculating the absolute X and Y positions of the bottom camera
#include <NIDAQmx.h> // NIDAQmx is a measurement software for the NI-DAQ.
#include "Spinnaker.h" // The SDK for the Top Camera
#include "SpinGenApi/SpinnakerGenApi.h"

#include <pylon/PylonIncludes.h>
#ifdef PYLON_WIN_BUILD
#    include <pylon/PylonGUI.h> 
#endif
#include <pylon/usb/BaslerUsbInstantCamera.h> // Basler and Pylon control the bottom camera
#include "HardwareTriggerConfiguration.h"

//---Parallele section---//
#include <thread>
#include <omp.h> // #pragma omp is used to specify directives and clauses
#include <queue>
#include <concurrent_queue.h> // A sequence container class that allows first-in, first-out access to its elements

//---Image processing---//
//To make opencv2 library work, add path. 
// Open Project-->Properties-->Configuration properties --> VC++ Directories
// After comparing, copy those paths from flygantryV2's propeties and add them in your properties
#include <opencv2/highgui/highgui.hpp> // openCV is an image processing packet for python and C++
#include <opencv2/imgproc/imgproc.hpp> // openCV provides functions to process the images acquired from the cameras. 
#include <opencv2/videoio/videoio.hpp> // openCV provides a means of accessing the inputs and outputs from the cameras. 
#include <opencv2/core/core.hpp> // CV = computer vision

//---YOLO---//
#include <yolo_v2_class.hpp>


//---For custom classes---//
// These head file need uderlying .cpp file in Source Files at the same time
#include "gantry.h"
#include "position.h"
#include "filter.h" // Interprets images from the arena and tries to track, predict, and correct those images.
#include "topCamProc.h"
#include "Calibration.h"
#include "OptoStim.h"
#include "Config.h"
#include "WindowManager.h"
#include "BinarySaveData.h"
#include "MatlabSaveData.h"
#include "flyViewStruc.h"
#include "pch.h"

*/

#include "pch.h"
#include <conio.h>
#include "stdio.h"
#include "windows.h"
#include "USB4.h" // USB4 is the DECODER. The decoder interprets the encoder quadrative signal, counting the marks it 
// has passed and calculating the absolute X and Y positions of the bottom camera.
#include <iostream> // input output stream header
#include <stdlib.h> // standard library header. 
#include <math.h>
#include <fstream>
#include <algorithm> // Added by Sam on 10/2 to allow use of copy function

#include <thread>
#include <omp.h> // #pragma omp is used to specify directives and clauses
#include <queue>
#include <concurrent_queue.h> // A sequence container class that allows first-in, first-out access to its elements
#include <sstream>
#include <chrono>
#include <opencv2/highgui/highgui.hpp> // openCV is an image processing packet for python and C++
#include <opencv2/imgproc/imgproc.hpp> // openCV provides functions to process the images acquired from the cameras. 
#include <opencv2/videoio/videoio.hpp> // openCV provides a means of accessing the inputs and outputs from the cameras. 
#include <opencv2/core/core.hpp> // CV = computer vision
//#include <C:/darknet/include/yolo_v2_class.hpp>
#include <yolo_v2_class.hpp>
//#include <opencv2/ximgproc.hpp>
#include <ctime>   // localtime
#include <sstream> // stringstream
#include <iomanip> // put_time
#include <string>  // string

//---For custom classes---//
#include "gantry.h" // provides access to gantry.cpp which controls the gantry itself
#include "position.h" // Figures out the positions of the encoder
#include "filter.h" // Interprets images from the arena and tries to track, predict, and correct those images.
#include "topCamProc.h"
#include "OptoStim.h"
#include "WindowManager.h"
#include "Calibration.h"
#include "flyViewStruc.h"
#include "BinarySaveData.h"
#include "MatlabSaveData.h"
#include "Config.h"

// The DAQ reads the encoder info from the decoder and modulates the proportional control of the motors. 
#include <NIDAQmx.h> // NIDAQmx is a measurement software for the NI-DAQ.
#include "Spinnaker.h" // The SDK for the Top Camera
#include "SpinGenApi/SpinnakerGenApi.h"

#include <pylon/PylonIncludes.h>
#ifdef PYLON_WIN_BUILD
#    include <pylon/PylonGUI.h> 
#endif
#include <pylon/usb/BaslerUsbInstantCamera.h> // Basler and Pylon control the bottom camera
#include "HardwareTriggerConfiguration.h"


////// Define Globel Variables//////
#define FREQ 479.987; //Andrew's version is 480, this should be the frequency of bottom camera.
#define DECODER_BUFFER_MAX 10000;

#define BOTTOMCAM_MODE 1; 
#define TOPBOTTOMCAM_TOGGLE_MODE 2; 
#define TOPBOTTOMCAM_PARALLEL_MODE 3; 

using namespace std; // 'std' refers to the standard library:coun,endl,vector,string, etc.
using namespace cv;// opencv
using namespace concurrency;// refers to PPL for current_queue, etc

// Determine the absolute minimum resolvable spot that can be seen on the object
//objectSpaceResolution = Pixel_Size/PMAG.
//for more info:https://www.edmundoptics.com/resources/application-notes/imaging/object-space-resolution/
// objectSpaceResolution is a bottom camera constant used for converting pixels to um micrometers
// objectSpaceResolution, along with Arena center coordinate are saved to the "*_meta.txt" file output
float objectSpaceResolution = 4.8 / 0.5; // 9.6 

unsigned long imgCnt = 0; // image count. Corresponds to chunkStruc.dataNum that is iteratively increased. Most likely corresponds to frame count
unsigned long encCnt = 0; // encoder count. Corresponds to encoderDataInst.dataNum that is iteratively increased. Most likely corresponds to encoder position

const double frequency = FREQ; // sets the frequency, 480.0, as a constant. 
// converting frequency to nanoseconds. This is done by converting the frequency (Hz) into gigaHertz (480million S^-1) then inversing it to give nanoseconds (2.083e-12 nanoseconds)

// used to check if a frame may be missing from the data if the time between frames is too long
unsigned long correctdt = 1.0 / frequency * pow(10, 9); //Camera time stamp uses nanoscale as a unit

// x and y positions of the encoder
unsigned long encoderX = 0;
unsigned long encoderY = 0;
Point2f bottomCamRecentFlyPos(150000.0f, 150000.0f); // initialize this value roughly to the center. Does not really matter what the initial value is though.
// 150000 is the default value for the initial position of the absolute X and Y position for the center of mass. This changes if you calibrate the top camera. 

boolean stream = true; // data stream is on and running

// The concurrent_queue class is a sequence container class that allows first-in, first-out access to its elements.
// The Stream class provides a generic view of a sequence of bytes. 

// flyViewStruct is the structure that will be used by chunkStruc, chunkStrucSave and fvStruc to store important information during gantry experiments.
// To initiallize, here all ther queue is empty at the beginning
concurrent_queue<flyViewStruc> flyViewQ; // anything involving concurrent_queue is happening in parallel with other concurrent_queue-associated functions/ processes.
concurrent_queue<Mat> arenaStream; // Shows a video of the arena.
concurrent_queue<Mat> flyStream; // This appears to setup flyStream which shows a popup video frame of the fly
concurrent_queue<Mat> flyStreamRaw; // Shows a video of the raw fly stream data. 
concurrent_queue<flyViewStruc> flyViewSaveQ;





//////Necessary Classes and Structures//////
// 1. Class for capturing video frames from the bottom camera, using the Pylon API. See Pylon documentation for CImageEventHandler
class CImageEventPrinter : public Pylon::CImageEventHandler
{
	// BASLER AND PYLON ARE FOR CONTROLLING THE BOTTOM CAMERA:
	//using namespace Pylon
	// The pylon API is the Basler Components C++ application programming interface (API) for certain cameras.
	// Link to Basler pylon programming guide: http://mlab.no/blog/wp-content/uploads/2009/06/basler_pylon_prog_guide_and_api_ref.pdf

public:
	CImageEventPrinter()
	{
		formatConverter.OutputPixelFormat = Pylon::PixelType_Mono8;// PixelType_BGR8packed;
	}

	virtual void OnImageGrabbed(Pylon::CInstantCamera& camera, const Pylon::CGrabResultPtr& ptrGrabResult)
	{
		if (ptrGrabResult->GrabSucceeded())
		{
			chunkStruc.grabSucceeded = int(ptrGrabResult->GrabSucceeded());
			if (ptrGrabResult->HasCRC() && ptrGrabResult->CheckCRC() == false)
			{
				chunkStruc.imageDamaged = 1; // 1 = IMAGE DAMAGED
			}
			else
			{
				chunkStruc.imageDamaged = 0; // 0 = IMAGE NOT DAMAGED
			}

			//if (ptrGrabResult->GetNumberOfSkippedImages())
			//{
			//	cout << "Skipped " << ptrGrabResult->GetNumberOfSkippedImages() << " image." << endl;
			//}

			GenApi::CIntegerPtr chunkTimestamp(ptrGrabResult->GetChunkDataNodeMap().GetNode("ChunkTimestamp"));


			// prints if there is too much time between frames. not used
			// should be NDEBUG?- if in debug, it will keep printing because the debug version lags
#if RELEASE
			if (imgCnt > 0)
			{
				if ((chunkTimestamp->GetValue() - prevTime) > correctdt * 1.5 || (chunkTimestamp->GetValue() - prevTime) < correctdt * 0.5)
				{
					cout << "One or more frame(s) skipped. Post-processing should take this into account or user should terminate this session" << endl;
				}

			}
#endif
			chunkStruc.camTime = chunkTimestamp->GetValue();
			prevTime = chunkTimestamp->GetValue();
			formatConverter.Convert(pylonImage, ptrGrabResult);
			cvimg = cv::Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), CV_8UC1, (uint8_t*)pylonImage.GetBuffer());

			chunkStruc.img = cvimg.clone();
			chunkStruc.dataNum = ++imgCnt;

			flyViewQ.push(chunkStruc);
		}
		else
		{
			std::cout << "Error: " << ptrGrabResult->GetErrorCode() << " " << ptrGrabResult->GetErrorDescription() << " " << std::endl;
		}
	}

private:
	Pylon::CImageFormatConverter formatConverter;
	Pylon::CPylonImage pylonImage;
	Mat cvimg;
	flyViewStruc chunkStruc;
	//2.083374*10^-3 
	unsigned long long int prevTime = 0;
	unsigned long long int currentTime = 0;
};



// 2. INITIATE THE VARIABLES THE ENCODER WILL STORE: 
struct encoderData
{
	unsigned long encoderX; // encoder X position
	unsigned long encoderY; // encoder Y position
	unsigned long dt; // calculated velocity (ns)
	unsigned long dataNum; // encoder position along track?
};
concurrent_queue<encoderData> encoderQ; // setting up encoderQ as a structure to contain information to be parallel processed. It is phonetic for "encoder queue"


// 3. OpenCV mouse callback function. Left click on bottom camera image prints world coordinates of the pixel location
void mouseCallbackFcn(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		y = 599 - y;

		const unsigned long worldPositionX = encoderX + (unsigned long)(objectSpaceResolution * (float)x);
		const unsigned long worldPositionY = encoderY + (unsigned long)(objectSpaceResolution * (float)y);

		cout << "x = " << worldPositionX << "\n" << "y = " << worldPositionY << endl;
	}
}




///// The Main Fuction////
int main(int argc, char* argv[]) // argc: argument count, argv: argument vector
{
	// Set process prioirty to high to try to keep other processes from messing up the tracking
	if (!SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS))
		std::cout << "Could not set priority class" << std::endl;

	// Check that there is enough free space on the main drive to save the data for an experiment
	double totalFreeGB = 0;
	while (totalFreeGB < 50.0)
	{
		LPCSTR lpRootPathName = "C:\\";
		DWORD lpSectorsPerCluster = 0;
		DWORD lpBytesPerSector = 0;
		DWORD lpNumberOfFreeClusters = 0;
		DWORD lpTotalNumberOfClusters = 0;
		GetDiskFreeSpaceA(lpRootPathName, &lpSectorsPerCluster, &lpBytesPerSector, &lpNumberOfFreeClusters, &lpTotalNumberOfClusters);
		totalFreeGB = static_cast<double>(lpNumberOfFreeClusters)
			* static_cast<double>(lpSectorsPerCluster) * static_cast<double>(lpBytesPerSector) /
			(1024.0 * 1024.0 * 1024.0);
		if (totalFreeGB < 50.0)
		{
			cout << "There is only " << totalFreeGB << " GB of hard drive space available.\nDelete some files, then press enter to continue." << endl;
			cin.get();
		}
	}


	//Initializing variables
	double samplingRate = 1000; //450.0
	double samplingPeriod = 1.0 / (samplingRate * pow(10.0, 6.0));//samplingPeriod = 1e-09;
	// pow(10,6) = 10^6
	int spmr = round(samplingPeriod) / 2 - 1;//sampling Period x register
	// Be Carefull! round(samplingPeriod) may not an even number(2,4,6,8...)
	// cout << samplingPeriod << " " << spmr << endl;// output 1e-09 -1

	short iDeviceCount = 0; // iDevice corresponds to the DECODER
	int iResult = 0; // initially set to 0, 
	//USB4 initializes using the iDeviceCount as an input and iResult as an output

	unsigned long ctrlmode = 0;
	unsigned long ulCounts[4] = { 0,0,0,0 };
	unsigned long ulLatchx;// This Latch is a way for X encoder to share its position with the decoder
	unsigned long ulLatchy;// This Latch is a way for X encoder to share its position with the decoder
	unsigned long ulCount0prev = 0; // literally only referenced on this line. redundant?
	unsigned long ulCount1prev = 0; // literally only referenced on this line. redundant?
	unsigned long ulTimeStamp = 0; // initializes the var which will become the indexed time 
	//value 
	unsigned long ulTimeStampPrev = 0;
	unsigned long dTimeStamp = 0;
	unsigned long presetVal = 500000;
	unsigned long dt = 0.0;

	BOOL bVal = TRUE;
	// assume found.
	// variables for deciding whether the bottom camera should move
	// left over from binarization image processing, now just sets both if yolo finds the fly
	bool bottomCamFlyFound = true; // whether or not the bottom camera has found the fly -> Why is this default set to true?--> IT WILL BE VALUED BY couldBeFlySize
	bool couldBeFlySize = false;// If a certain number of pixels acquired from the top! camera is within a range for what could be a fly, the system may have found a fly
	bool endcoderWithinArena = false;// Checks the positions of the encoder and determines if it is within the coordinates for the arena
	// Config it as false

	bool firstCalling1 = true;
	bool firstCalling2 = true;
	bool firstCalling3 = true;// these three variabels are using to defined if the top, bottom or
	//no camera is in control


	//Window Manager
	WindowManager wnd;
	//Configuration File Handler
	Config config;
	std::string configStimType = config.getStimulusShape();
	bool debugStim = config.getDebug(); // Added by Marcello 10/6/23, set to true if you want the light on to respond to camera position only, false for real experiments/final compile
	if (configStimType == "noise" || configStimType == "pulses" || configStimType == "pattern")
		debugStim = true;  //Hacky way to do non-spatial stimuli.  Ignores fly found condition.

	printf("---------------------------------\n");
	printf("-Robotic System for Fly Tracking-\n");
	printf("-Developer: Chanwoo Chun-\n");
	printf("-Bhandawat Lab-\n");
	printf("TestVersion 1 -- Last Updated: 12/03/2024 by MN\n"); // Line added by MN on 12/03
	printf("THIS IS THE COPY VERSION FROME gantryflyV2 TO UNDERSTAND CODE\n"); // Line added by MN on 12/03
	printf("---------------------------------\n");




	//swtting up foe the storage of time data
	time_t rawtime = time(0);
	tm timeinfo;
	localtime_s(&timeinfo, &rawtime);

	char str[70];
	strftime(str, sizeof(str), "%Y%m%d%H%M", &timeinfo);
	using String = std::string;

	// data folder and file names for saved data and video
	String dataFolder = getenv("USERPROFILE") + string("\\Documents\\Data");

	String dataName = dataFolder + "\\" + string(str);// return_current_time_and_date(); // dateName is a path name: "../Data/202412031500"
	
	// set class for saving .mat file at the end of the experiment for use in MATLAB
	string matFileName = dataName + ".mat";
	MatlabSaveData matSaveData(matFileName.c_str(), frequency);

	cout << str << endl; // Output current date and time


	// USB4 controls the encoder, which gives the absolute position of the bottom camera.
	// Initialize the USB4 driver.
	iResult = USB4_Initialize(&iDeviceCount);// initialize the card

	cout << iResult << endl;

	Position xPos;// Position is DWORD, a 32-bit unsigned integer.
	Position yPos;// This sets the xPos and yPos as 32-bit unsigned integers.

	if (iResult != USB4_SUCCESS)
	{

		printf("Failed to initialize USB4 driver! Result code = %d.\nPress any key to exit.\n", iResult);
		while (!_kbhit())//while no keyborad input is registered; kbhit() checks the console for keybored input; include in <conio.h>
		{
			Sleep(100);//Sleep() for 100ms
		}
		return 1;// 1: an error occurred or an impermissible action; 0: program ended with no errors
	}



	// Caution! The reset of the example is implemented without any error checking.

	// USB4 is the DECODER that interprets the encoder's quadrature signal
	// From the USB4.h code:
	// USB4_SetPresetValue(short iDeviceNo, short iEncoder, unsigned long ulVal);
	// Understanding the USB4 function structures:
	// USB4_functionName(decoder index value, encoder index, various other inputs);
	// the decoder index value, 0 in this case, is referring to the DECODER that interprets the encoder signals.There is only 1 decoder.
	// the encoder index, either 0 or 1, is referring to the axis-specific encoders. There are 2 encoders, one for the X - axis and one for the Y - axis.

	// Configure encoder channels

	USB4_SetPresetValue(0, 0, presetVal); // For all the set functions, The 1st 0 of each of these functions refers to the device number, which would most likely be the DECODER.
	USB4_SetPresetValue(0, 1, presetVal); // the 2nd input for these functions is the index of the encoder, which refers to either the X or Y encoder.
	USB4_SetMultiplier(0, 0, 3); // Set quadrature mode to X4
	USB4_SetMultiplier(0, 1, 3); 
	USB4_SetCounterMode(0, 0, 0); // Set counter mode to modulo-N. NOPE> changing to normal 24bit up / down counter;
	// modulo-N: counter range: 0 1 2 ...N-1 0 1 2 ...N-1 0 1 2 ...
	// 24bit up.down counter: range: [-2^23 ,2^23-1] = [- 8388608, 8388607]
	USB4_SetCounterMode(0, 1, 0);
	USB4_SetForward(0, 0, TRUE); // Optional: determines the direction of counting.
	USB4_SetForward(0, 1, TRUE);
	USB4_SetCounterEnabled(0, 0, TRUE); // Enable the counter. **IMPORTANT**
	USB4_SetCounterEnabled(0, 1, TRUE);
	USB4_PresetCount(0, 0); // Reset the counter to 0 for X(?) encoder 
	USB4_PresetCount(0, 1); // Reset the counter to 0 for Y(?) encoder
	USB4_ResetTimeStamp(0); // Reset TimeStamp
	USB4_SetCaptureEnabled(0, 0, TRUE);
	USB4_SetCaptureEnabled(0, 1, TRUE);
	USB4_SetTriggerOnIndex(0, 0, TRUE);
	USB4_SetTriggerOnIndex(0, 1, TRUE);// The USB4 is set to trigger after passing two encoder references.
	USB4_SetEnableIndex(0, 0, FALSE); // This stores when an index is passedon the X(?) axis.
	USB4_SetEnableIndex(0, 1, FALSE); // This stores when an index is passedon the Y(?) axis.
	USB4_SetTriggerOnIncrease(0, 0, FALSE); // Set trigger on increase for X axis encode to FALSE
	USB4_SetTriggerOnIncrease(0, 1, FALSE); // Set trigger on increase for Y axis encode to FALSE
	USB4_SetTriggerOnDecrease(0, 0, FALSE); // Set trigger on decrease for X axis encode to FALSE
	USB4_SetTriggerOnDecrease(0, 1, FALSE); // Set trigger on decrease for Y axis encode to FALSE

	// FIFO(first in, first out) Settings
	long lFIFOCount = 0; // initialize the long first in, first out position count.This variable used in Section 2
	const int maxBufferSize = DECODER_BUFFER_MAX; // Set the max size of the buffer to the pre - set value from earlier(10, 000)
	USB4_FIFOBufferRecord cbr[maxBufferSize]; // Checkerboard Rendering (CBR) is a technique that produces full - resolution pixels
	// with a significant reduction in shading and minimal impact on visual quality.
	
	// Clear the FIFO buffer
	USB4_ClearFIFOBuffer(0);
	// Enable the FIFO buffer
	USB4_EnableFIFOBuffer(0); // This is a re-enabling set to make sure the buffer is enabeled
	USB4_ClearCapturedStatus(0, 0); 
	USB4_ClearCapturedStatus(0, 1);// clears the captured status for the X and Y axis encoders

	// enable trigger on input 0
	BOOL bEnableTrigger[8] = { TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE }; // The T, F * 7 correspond to pin numbers.T is Pin 1, F is P2 - 8
	// trigger on rising edge of input 3
	BOOL bTriggerOnRisingEdge[8] = { TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
    USB4_SetDigitalInputTriggerConfig(0, bEnableTrigger, bTriggerOnRisingEdge); // boolean enable trigger and boolean trigger on rising edge
	// True : sensitive to Ringsing Edge: where signal rising quickly within a short time. e.g. time point = 0,1,2; signal = 0,0,1
	// False: sensitive to Descending Edge: which is inverse.

	//How these 2 trigger set work? 
	//In both, the first channel is TRUE, which means the first channel will be triggered when the input signal has a short quickly rising.
	//Note that there are 8 channels, and both 2 lines need to be set up as TRUE for one specific channel(usually 1st),
	//otherwise this channel will not sensitive to the rising signal.

	Gantry motors; // A class that uses "motors" to drive the movement of the motors
	const double frequency = FREQ;
	motors.configure(frequency);



	// How to introduce stim stimulus? GantryConfig will be found under C:/user/<your username> file, to make sure this test code can work, add the test GantryConfig.txt there
	// Note that original GantryConfig.txt is used to run current flygantrycodeV2, don't forget to remove the text config file when finish this code test 
	// Optogenetic Stimulation class
	OptoStim optoStim(motors, frequency, wnd, config);
	// Class for handling the top camera, its video images, and its data related to the arena dimensions
	ArenaProc arenaP(optoStim, wnd);
	// Loads camera calibration coefficients. This should be left alone unless a new camera is used.
	arenaP.loadCameraCalibration("C:\\Program Files\\Gantry\\Calibration\\coeffs_roi"); // 19 coeffs in this file, 14 will be shown 
	// arenaP and ArenaProc refer to arena proportional control, which changes the speed of the motor controlling the camera in a manner proportional to the distance from the center of the fly.
	// ArenaProc is from <topCamProc.h>

	int prev_rest = 1000; // prev_rest is only mentioned in this line. Does it do anything?
	Size fvFrameSize(592, 600); // sets frame size as 592x600 as the image resolution
	Point2f est_dist(0, 0); // sets the floating number for the estimated distance as 0
	Point2f est_vel(0, 0); // sets the floating number for the estimated distance as 0

	// Variables for calculating the distance of the next encoder location from the arena center
	// Was needed more when the image processing was used to keep the camera from constantly moving off the edge of the arena
	// Added in the newest version
	long long future_encoderXDist;
	long long future_encoderYDist;

	int8 option;

	// HAS NOT BEEN IMPLEMENTED YET:
	cout << "Select any mode from below:" << endl;
	cout << "	(1) Bottom camera only" << endl;
	cout << "	(2) Toggle between top and bottom cameras" << endl;
	cout << "	(3) Parallel run of top and bottom cameras" << endl;
	//	cin >> option;

	// Turn on illuminating LED
	motors.DriveIlluminatingLED();




	//----- Build 6 Parallel Sections----//
	// Six sections: CALIBRATING TOP CAMERA, CALIBRATING BOTTOM CAMERA, Fly tracking with yolo, Driving the motors(Controling part), Disply bottom view, Save Data
#pragma omp parallel sections num_threads(6)//6 section
	{
#pragma omp section

		{
			// CALIBRATING TOP CAMERA:
			// code for starting the video acquisition for the top camera. the width, height, and offsets can be changed if needed
			using namespace Spinnaker; // Driver that controls the top camera
			using namespace Spinnaker::GenApi;
			using namespace Spinnaker::GenICam;

			//////For arena view camera (Point Grey. Spinnaker SDK)//////
			// Initialize camera
			SystemPtr system = System::GetInstance(); // ptr = pointer: System pointer, get sponnaker system
			CameraList camList = system->GetCameras(); // identify the cameras being controlled by this system
			CameraPtr pCam = camList.GetByIndex(0); // pCam is set as the first camera in camListm, here it is the top Cam
			pCam->Init(); // initialize pCam (what is pCam referring to? proportional control camera? parallel camera? parallel run of top and bottom cameras?)
			pCam->Width = 864;
			pCam->Height = 864;
			pCam->OffsetX = 560;//
			pCam->OffsetY = 260;
			// Retrieve GenICam nodemap
			// nodemap: saves camera's perematers like exposuretime...
			INodeMap& nodeMap = pCam->GetNodeMap(); // initialized and regular node maps to get set
			CEnumerationPtr ptrAcquisitionMode = nodeMap.GetNode("AcquisitionMode"); // top camera is actively acquiring nodes
			CEnumEntryPtr ptrAcquisitionModeContinuous = ptrAcquisitionMode->GetEntryByName("Continuous"); // top camera is continuously acquiring frames 
			// Retrieve integer value from entry node
			int64_t acquisitionModeContinuous = ptrAcquisitionModeContinuous->GetValue(); // grabs the value acquired by the top camera's continuous node search as a 64 bit integer
			// Set integer value from entry node as new value of enumeration node
			ptrAcquisitionMode->SetIntValue(acquisitionModeContinuous);
			cout << "Acquisition mode set to continuous..." << endl;
			pCam->BeginAcquisition(); // start acquiring images
			bool allFound = false; // Sets the initial state for bottom camera calibration such that NOT ALL MARKERS HAVE BEEN FOUND
			char exp_yes = 'n'; // the initial input expression set to "n"

			// loop for capturing top camera images
			while (TRUE)
			{
				ImagePtr pResultImage = pCam->GetNextImage(); // gets the next image
				if (pResultImage->IsIncomplete()) // If the image acquired is incomplete
				{
					// Retreive and print the image status description
					cout << "Image incomplete: "
						<< Image::GetImageStatusDescription(pResultImage->GetImageStatus())
						<< "..." << endl << endl;
				}
				else
				{
					size_t width = pResultImage->GetWidth(); // get the width and height of the completed image

					size_t height = pResultImage->GetHeight();

					ImagePtr convertedImage = pResultImage->Convert(PixelFormat_BGR8, NEAREST_NEIGHBOR); // color processing algorithm from spinnaker library

					unsigned int XPadding = convertedImage->GetXPadding(); // Padding is the space between an image or cell contents and its outside border. 
					unsigned int YPadding = convertedImage->GetYPadding(); // (0,0)
					unsigned int rowsize = convertedImage->GetWidth(); // Stores row and column sizes based on width and height of completed, converted image
					unsigned int colsize = convertedImage->GetHeight();//(864,864)

					Mat cvimg = cv::Mat(colsize + YPadding, rowsize + XPadding, CV_8UC3, convertedImage->GetData(), convertedImage->GetStride()); // GetStride calculates an image stride, in bytes.

					arenaP.undistort(cvimg);//Open top camera view window
					// !! Seems like some of the libs are filed to open although window opened successfully, are they important?

					if (arenaP.set_for_exp)
					{
						// was used for automatically finding the fly in the top camera image if the bottom camera lost track of the fly
						// that part no longer works, but this function still includes code for showing the top camera view on the screen
						// with timer and optogenetics information
						arenaP.findFlyPos(encoderX, encoderY);
					}
					else
					{
						arenaP.showTopCamView();
					}
				}

				// ends the loop when escape is pressed
				//To test next sections, set:
				//stream = false;
				if (!stream)
				{
					break;
				}
				pResultImage->Release(); // release the image


			}

			pCam = nullptr; // The nullptr keyword represents a null pointer value, which indicate that an object handle, interior pointer, or native pointer type does not point to an object.
            // Below are for Point Grey (Top)Camera
            // Clear camera list before releasing system
			camList.Clear();
			// Release system
			system->ReleaseInstance(); // how are Release() and ReleaseInstance() different:  Release() only releases one single camera, ReleaseInstance() can release current whole system, here the Spinneaker Systerm

			// Note that the loop will continue until whole code finish, beacuse while() condition is always TRUE unless some errors happen.


		}
#pragma omp section
		{
			// CALIBRATING BOTTOM CAMERA
			// Code for running the bottom camera and for getting the encoder position of the camera in the x and y positions
			// Menglin: How this work is expalined in relevant word document.
			// Andrew: not sure how most of this works, but it should not need to be changed

			using namespace Pylon; // accesses the Pylon camera processing library
			using namespace GenApi;
			using namespace Basler_UsbCameraParams; // Basler USB4 Camera

			int rest2 = 1000;
			//int LEDState = 0; // LED Default State = OFF. Added by Sam on 10/18
			motors.onLED = 0;// LED Default State = OFF

			//////Setting For fly view camera (Basler. Pylon SDK)//////
			PylonInitialize(); // When the top camera is turned on. 
			try
			{
				//This setting part need to build a CLASS named 'CImageEventPrinter' before, which is used for capturing video frames from bottom camera
				CBaslerUsbInstantCamera camera(CTlFactory::GetInstance().CreateFirstDevice());
				cout << "Using device " << camera.GetDeviceInfo().GetModelName() << endl;
				
				// Register the standard configuration event handler for enabling software triggering.//
		        // The software trigger configuration handler replaces the default configuration as all currently registered configuration handlers are removed by setting the registration mode to RegistrationMode_ReplaceAll.
				camera.RegisterConfiguration(new CHardwareTriggerConfiguration, RegistrationMode_ReplaceAll, Cleanup_Delete);
				// The image event printer serves as sample image processing.
				// When using the grab loop thread provided by the Instant Camera object, an image event handler processing the grab
				// results must be created and registered.
				camera.RegisterImageEventHandler(new CImageEventPrinter, RegistrationMode_Append, Cleanup_Delete);


				camera.Open();

				// Sets parameters for bottom camera image capturing and image cropping. These values can be changed if needed
				camera.ExposureTime.SetValue(1000.0);
				camera.SensorReadoutMode.SetValue(SensorReadoutMode_Fast);
				camera.Width.SetValue(592);
				camera.Height.SetValue(600);
				camera.OffsetX.SetValue(112);
				camera.OffsetY.SetValue(16);
				camera.ReverseX.SetValue(true);

				camera.ChunkModeActive.SetValue(true); // Activates chunk mode so chunk mode data can be acquired

				camera.ChunkSelector.SetValue(ChunkSelector_Timestamp); // Selects a chunk from a timestamp
				camera.ChunkEnable.SetValue(true); // enables the chunk? I guess it accepts the acquisition?

				// Enable CRC checksum chunks.
				camera.ChunkSelector.SetValue(ChunkSelector_PayloadCRC16); // Determines whether or not the CRC checksum chunk can be enabled
				camera.ChunkEnable.SetValue(true);
				camera.MaxNumBuffer = 500; // So the buffer count for the camera is 1/10th of the max FILO buffer (10,000)?
				// Start the grabbing using the grab loop thread, by setting the grabLoopType parameter
				// to GrabLoop_ProvidedByInstantCamera. The grab results are delivered to the image event handlers.
				// The GrabStrategy_OneByOne default grab strategy is used.
				camera.StartGrabbing(GrabStrategy_OneByOne, GrabLoop_ProvidedByInstantCamera); // start grabbing images from camera frame by frame
				//(GrabStrategy_LatestImages);// (GrabStrategy_OneByOne);// (GrabStrategy_LatestImageOnly);

				// The End-of-Text character (ETX) (hex value of 0x03) is an ASCII control character used to inform the receiving computer that the end of the data stream has been reached. 
				unsigned char ucVal = 0x03; // unsigned char value 
				USB4_WriteOutputPortRegister(0, 0x02); // 0x02 is the Start of Text Character (STX) -> First character of message text, and may be used to terminate the message heading.
				
				//Catpure Frames and Get positions//
				while (TRUE)
				{
					// CHECKS IF EITHER THE X OR Y ENCODERS ARE CALIBRATED:
					if (!xPos.calibrated || !yPos.calibrated) //If the X encoder or Y encoder are not calibrated...
					{
						USB4_ReadOutputLatch(0, 0, &ulLatchx); // read the latch position of the x axis
						USB4_ReadOutputLatch(0, 1, &ulLatchy); // read the latch position of the y axis
						xPos.feedInLCnt(ulLatchx); // Feed in latch count for the x position
						yPos.feedInLCnt(ulLatchy); // Feed in latch count for the y position
						USB4_ClearCapturedStatus(0, 0); // clear the captured state for the x axis
						USB4_ClearCapturedStatus(0, 1); // clear the captured state for the y axis
					}
					else // If the position for the calibrated X or Y encoders are not set or is good
					{
						if (!xPos.setForAcquisition || !yPos.setForAcquisition) //If the X and Y encoder positions are not set for acquisition
						{
							cout << "XY Calibrated. Setting up for acquisition" << endl;
							// The encoders are ready to pass 2 index values to determine their absolute positions along the linear actuator:
							// USB4_SetTriggerOnIndex(decoder index position, encoder index position, boolean);
							USB4_SetTriggerOnIndex(0, 0, FALSE); // 
							USB4_SetTriggerOnIndex(0, 1, FALSE); // The encoder is calibrated now so the absolute position is known.

							// Clear the FIFO buffer
							USB4_ClearFIFOBuffer(0); // Clear out previous, unrelated information
							USB4_ResetTimeStamp(0); // set the time stamp for acquiring frames to 0

							motors.startDataAcquisition(); // start acquiring data

							xPos.setForAcquisition = true; // set the state of the x and y axis as ready for acquiring data.
							yPos.setForAcquisition = true;
							arenaP.set_for_exp = true;
							arenaP.setFlyMouseCallbackFunc(&arenaP);
							arenaP.getTransformationMatrix();
						}
						else // otherwise start acquiring positional and time information for the encoders and store that information in the constant-bit rate FIFO buffer structure:
						{
							lFIFOCount = DECODER_BUFFER_MAX; // the long First-In, First-out count is set to the max decoder buffer value, 10,000.
							USB4_ReadFIFOBufferStruct(0, &lFIFOCount, &cbr[0], 1000); // Read how the FIFO buffer's structure is setup. 
							// the "1000" refers to the unsigned long time readout, which makes sense given 1000 is the sampling rate.

							// loop through the buffer and iteratively add time stamps to it
							for (int i = 0; i < lFIFOCount; i++) 
							{
								ulTimeStamp = cbr[i].Time; // CBR stands for constant bit rate, aims for a constant or unvarying bandwidth level with video quality allowed to vary. 

								if (ulTimeStamp < ulTimeStampPrev) // If the time stamp value is less than the previous one...
								{
									dTimeStamp = numeric_limits<unsigned long int>::max() - ulTimeStampPrev + ulTimeStamp; // subract the sum of the previous and
									
									// current timestamp data from the max time stamp data acquired
                                    //cout << "rare" << endl;
								}
								else // otherwise if the current time stamp is equal to or greater than the previous time stamp...
								{
									dTimeStamp = ulTimeStamp - ulTimeStampPrev; // create a new timestamp based on the difference between them
								}

								dt = dTimeStamp / (48.0 * pow(10.0, 6.0)) * pow(10, 9); // Figure out the change in time (ns)
								// 48.0 is the frequency. This calculates the change in time divided by 48.0*10^6*10*9 -> Output value = dTimeStamp * 2.0833e-17. Output unit = ns

								//cout << xPos.getAbsPos(cbr[i].Count[0]) << "\t" << yPos.getAbsPos(cbr[i].Count[1]) << "\t" << dt << "\t" << lFIFOCount << endl;

								// Calculate the absolute position of the encoders:
								// Encoder structure should be established before main()
								encoderX = xPos.getAbsPos(cbr[i].Count[0]); // Get the absolute position of the encoder on the X axis
								encoderY = yPos.getAbsPos(cbr[i].Count[1]); // Get the absolute position of the encoder on the Y axis


								encoderData encoderDataInst; // sets up the class encoderDataInst
								encoderDataInst.encoderX = encoderX; // saves encoderX and encoderY to this encoderDataInst structure
								encoderDataInst.encoderY = encoderY;

								// Press "5" key on numberpad to post X and Y encoder positions. - Added by Sam on 9/18
								if (wnd.keyPressed(VK_NUMPAD5)) // the "4" key on the numberpad moves motor LEFT
								{


									//motors.StopX(); 
									//motors.DriveLED();
									cout << "encoder X: " << endl;
									cout << encoderX << endl;
									cout << "encoder Y: " << endl;
									cout << encoderY << endl;
									cout << "est_dist:" << endl;
									cout << est_dist << endl;

									int arenaCenterX = 222525;
									int arenaCenterY = 222450;
									int frameCenterX = (est_dist.x * 9.6);
									int frameCenterY = (est_dist.y * 9.6);
									int encoder_arenaCenter_dist = ((((arenaCenterX - (encoderX + frameCenterX)) ^ 2) + ((arenaCenterY - (encoderY + frameCenterY)) ^ 2)) ^ (1 / 2));
									cout << "encoder_arenaCenter_dist:" << endl;
									cout << abs(encoder_arenaCenter_dist) << endl;

									cout << "fvFrameSize:" << endl;
									cout << fvFrameSize << endl;

									//encoderDataInst.encoderX = encoderX; // saves encoderX and encoderY to this encoderDataInst structure
									//encoderDataInst.encoderY = encoderY;

									//arenaP.findFlyPos();
									//cout << arenaP.findFlyPos() << endl; 
									//cout << flyPos_encoder << endl;

									//	cout << "distance X: " << endl;
									//	cout << distance.x << endl;
									//	cout << "distance Y: " << endl;
									//	cout << distance.y << endl;
								}

								encoderDataInst.dt = dt; // saves the change in time
								encoderDataInst.dataNum = ++encCnt; // Iteratively increase encoder count, starting from 0
								encoderQ.push(encoderDataInst); // shares the information stored in encoderDataInst with encoderQ, a structure created on ~line 132

								//cout << dt << endl;
								if (dt > correctdt * 1.5 || dt < correctdt * 0.5) // If the change in time is within a corrected range then frames have been skipped. 
								{
									cout << "One or more encoder data skipped. Post-processing should take this into account or user should terminate this session" << endl;
									//cout << dt << endl;
								}
								if (lFIFOCount > 1) // If the FIFO buffer is being used at all...
								{
									//cout << "Buffering " << lFIFOCount << " data. Minimize computer usage." << endl;
									if (lFIFOCount == maxBufferSize) // If the FIFO buffer is full...
									{
										cout << "Skipped too many data. Terminating the session." << endl;
										stream = false; // turn stream of data OFF
										break; // End the sequence
									}
								}
								ulTimeStampPrev = ulTimeStamp; // sets the time stamp previous value to the currently stored one before moving on to the next iteration.
							}
							//USB4_ClearDigitalInputTriggerStatus(0);
						}
						// eStop is the pin #1 on the decoder/ USB4 --> eStop = LATCHING EMERGENCY STOP FOR THE 8 DIGITAL OUTPUTS
						motors.eStopUpX = xPos.eStopUp; // Move the x axis motor's position UP (right)
						motors.eStopDownX = xPos.eStopDown; // Move the x axis motor's position DOWN (left)
						motors.eStopUpY = yPos.eStopUp; // Move the y axis motor's position UP (up)
						motors.eStopDownY = yPos.eStopDown; // Move the y axis motor's position DOWN (down)
					}

					// Andrew: this is not currently set up to work
					/// MOVE THE TOP CAMERA UP OR DOWN:
					// MOVE THE TOP CAMERA STAGE DOWN:
					//if (wnd.keyPressed(VK_NUMPAD3)) // when user clicks the '3' on the numberpad...
					//{
					//	ucVal = 0x03; // unsigned character value. 0x03; // MOSFET on for lowest 2 bits. 
					//	USB4_WriteOutputPortRegister(0, ucVal); // sets the value stored in the output port register to 0x03 to the decoder. 
					//	std::this_thread::sleep_for(std::chrono::microseconds(rest2)); // tell the encoder to rest for 1000 us
					//	ucVal = 0x02; // 0x02 can be a Start-of-text control signal but I don't think that is being used here
					//	USB4_WriteOutputPortRegister(0, ucVal); // sets the value stored in the output port register to 0x02 to the decoder.
					//} 
					// Sam commented this out on 9/10/2020 to stop the top cam from moving down when I accidentally press the "3" key, since moving gantry up is not perfect. 

					// MOVE THE TOP CAMERA STAGE UP:
					//if (wnd.keyPressed(VK_NUMPAD9)) // when user clicks the '9' on the numberpad
					//{
					//	ucVal = 0x01; // 0x01 = E - Stop active (these are the latched emergency stop state, according to the USB4 documentation)
					//	USB4_WriteOutputPortRegister(0, ucVal); // Encoder events can also output on the output port to trigger external devices
					//	std::this_thread::sleep_for(std::chrono::microseconds(rest2));
					//	ucVal = 0x00; // 0x00 = E - Stop inactive
					//	USB4_WriteOutputPortRegister(0, ucVal);
					//}

					// press escape to exit, and set stream to false to exit all other loops in other threads
					if (wnd.keyPressed(VK_ESCAPE) || !stream)
					{
						motors.StopOptoLED();
						motors.onLED = 0;
						//LEDState = 0;
						USB4_StopAcquisition(0); // stop acquisition of the decoder
						stream = false; // stop stream from decoder
						break; // break sequence
					}
				}
			}
			
			catch (const GenericException& e) // check if an error has occured
			{
				// Error handling.
				cerr << "An exception occurred." << endl
					<< e.GetDescription() << endl;
				//exitCode = 1;
			}
			//Below are for Basler Camera
			PylonTerminate(); // terminate access to bottom camera
		
		}
#pragma omp section
		//FLY TRACKING WITH YOLO
		{
			Point2f distance(0, 0); // set floating number for distance to 0.
			Point2f distFilteredImgCoor(0, 0);
			Point2f pForImage(0, 0); // p = point for image. a coordinate for that image? -> I think this literally is the point where the view frame window goes. So changing it will change where the frame pops up. 

			Mat cvimg; // So we are re-using cvimg for both top and bot cam views?
			Mat dst;
			flyViewStruc chunkStruc; // set chunkstruct as a class with flyViewStruc's structure
			flyViewStruc chunkStrucSave; // set chunkStrucSave as a class with flyViewStruc's structure
			encoderData encoderDataInst; // set encoderDataInst as a class with encoderData's structure

			int streamCounter = 0;
			BOOL doSave = FALSE; // do not start saving data at start
			int saveState = 0; // save state initially set to off
			bool firstFrame = true; // the first frame is being processed

			TrackerLocal filter; // Initializes the tracker function for filter. 

			Point2f initCoM(0, 0); // initial center of mass coordinates, set initially to 0,0
			filter.Init(initCoM); // save the initial center of mass value in the "Init" initial field of the filter structure.


			time_t timeResult = time(NULL);
			char timeStr[26];

			// Set the calibration class for the mapping of the top camera pixels to encoder coordinates
			Calibration calib(arenaP, wnd);

			// Load the YOLO parameter files and set the vector for holding the detections on each loop
			const string yolo_obj_file = "C:\\darknet\\flyHeadYolov4.cfg";
			const string yolo_weights_file = "C:\\darknet\\flyHead_final.weights";
#if NDEBUG
			Detector detector(yolo_obj_file, yolo_weights_file);
			std::vector<bbox_t> detect_vec;
#endif
			Point p;
			Point pt1;
			Point pt2;
			Point pt3;
			Point pt4;
			Point comPt;
			Point headComPt(0,0);
			Point antPt;
			Point stimPt(0,0);
			Point2f stimDistance(0.0F ,0.0F);
			float yThresh = 0.9F;
			bbox_t headBox;
			constexpr double pi = static_cast<double>(std::_Pi);

			while (TRUE)
			{
				// calibrate top camera when pressing C
				if (wnd.keyPressed(0x43))
				{
					calib.startCalibratingTopCam();
				}
				// get images and struct from concurrent queue from other thread
				//if (!flyViewQ.empty() && !encoderQ.empty()) // If the flyView queue and the encoder queue are NOT empty...
				if (!flyViewQ.empty() && !encoderQ.empty())
				{
					flyViewQ.try_pop(chunkStruc); // dequeue the chunkStruc for parallel processing
					encoderQ.try_pop(encoderDataInst); // dequeue the encoderDataInst for parallel processing

					if (chunkStruc.dataNum - encoderDataInst.dataNum != 0) // if the chunk frame number and the encoder step number are unequal then the data is not synced
					{
						cout << "Data not synchronized. Check out concurrent queues." << endl;
						stream = false;
					}

					cvimg = chunkStruc.img;

					//Test detector()
					//Detector detector(yolo_obj_file, yolo_weights_file);
					//std::vector<bbox_t> detect_vec;
					//detect_vec = detector.detect(cvimg, yThresh);
					//detector.get_net_width();
					// detect the fly and the fly head at 60 fps. change this value if YOLO can be made to run faster
					if (streamCounter % 8 == 0)
					{
#if NDEBUG
						detect_vec = detector.detect(cvimg, yThresh);
						if (detect_vec.size() > 0)
						{
							for (auto& yolo_bbox : detect_vec) {
								// if head or body are found get the center point of the bounding box
								if (yolo_bbox.obj_id == 1 || yolo_bbox.obj_id == 0) {
									const unsigned int flyCOMX_bbox = yolo_bbox.x + (yolo_bbox.w / 2);
									const unsigned int flyCOMY_bbox = yolo_bbox.y + (yolo_bbox.h / 2);
									const unsigned int flyCOMY_bbox_flipped = cvimg.cols - 1 - flyCOMY_bbox;
									//const unsigned int flyCOMX_bbox = fly_bbox.x;
									//const unsigned int flyCOMY_bbox = cvimg.cols - 1 - fly_bbox.y;

									// set the body center of mass point to the center of the bounding box
									if (yolo_bbox.obj_id == 1) {
										p = Point(flyCOMX_bbox, flyCOMY_bbox_flipped);
										couldBeFlySize = true;
										pt1 = Point(yolo_bbox.x, yolo_bbox.y);
										pt2 = Point(yolo_bbox.x + yolo_bbox.w, yolo_bbox.y + yolo_bbox.h);
										comPt = Point(flyCOMX_bbox, flyCOMY_bbox);
									}
									// set the head center of mass point to the center of the bounding box
									else {
										headComPt = Point(flyCOMX_bbox, flyCOMY_bbox);
										headBox = yolo_bbox;
										pt3 = Point(yolo_bbox.x, yolo_bbox.y);
										pt4 = Point(yolo_bbox.x + yolo_bbox.w, yolo_bbox.y + yolo_bbox.h);
									}
								}
							}


							// approximate the point midway between the antennas by subtracting the center point
							// of the fly body from the center point of the fly head
							// use that vector to extrapolate to the edge of the head bounding box to approximate the point
							const Point flyVec = headComPt - comPt;
							const double orientAngle = atan2(static_cast<double>(flyVec.y), static_cast<double>(flyVec.x));
							int x;
							int y;
							// right side
							if (orientAngle > -pi / 4.0 && orientAngle <= pi / 4.0) {
								x = headBox.x + headBox.w;
								y = flyVec.y * (x - headComPt.x) / flyVec.x + headComPt.y;
							}
							// bottom side
							else if (orientAngle > pi / 4.0 && orientAngle <= 3 * pi / 4.0) {
								y = headBox.y + headBox.h;
								x = flyVec.x * (y - headComPt.y) / flyVec.y + headComPt.x;
							}
							// left side
							else if (orientAngle > 3.0 * pi / 4.0 || orientAngle <= -3.0 * pi / 4.0) {
								x = headBox.x;
								y = flyVec.y * (x - headComPt.x) / flyVec.x + headComPt.y;
							}
							// top side
							else {
								y = headBox.y;
								x = flyVec.x * (y - headComPt.y) / flyVec.y + headComPt.x;
							}
							antPt = Point(x, y);
						}
						else
						{
							p = Point(0, 0);
							couldBeFlySize = false;
						}
#endif
					}
					// Original: code for using image processing with binarization to find the fly
					//threshold(cvimg, dst, 28, 255, THRESH_BINARY); // sets a threshold, I imagine based on color from the 255 but I don't know what the 28 is. Low end of thresh maybe
					//threshold(cvimg, dst, 100, 255, THRESH_BINARY); // sets a threshold, I imagine based on color from the 255 but I don't know what the 28 is. Low end of thresh maybe

					// what is dst ? distance? Distance from an image based on a given threshold? dst is an output array
					// The threshold() function info can be found in topCamProc.h

					//morphologyEx(dst, dst, 2, element); // morphologyEx is a CV library function

					// find moments of the image
					//Moments m = moments(dst, true); // What constitutes a "moment"?
					//Point p(1.0 * m.m10 / (1.0 * m.m00), (cvimg.cols - 1) - 1.0 * m.m01 / (1.0 * m.m00)); //For y, I need to flip the coordinate. This is because top left corner is (0,0) in a matrix, but I now want bottom left to be (0,0).


					// Get the distance of the fly center of mass from the center of the frame
					//Point center(cvimg.rows / 2.0, cvimg.cols / 2.0); // Original.
					Point center(cvimg.cols / 2.0, cvimg.rows / 2.0);
					// Swap rows and cols then subtract 200 from center.y value to fix the deviated frame CoM static gray dot. 
					//distance.x = p.x - center.x; // figures out the distance X is from the center of the frame
					distance.x = p.x - center.x; // figures out the distance X is from the center of the frame
					distance.y = p.y - center.y; // figures out the distance Y is from the center of the frame
					stimDistance.x = antPt.x - center.x;
					stimDistance.y = cvimg.cols - 1 - antPt.y - center.y;

					if (arenaP.set_for_exp) {

						bottomCamFlyFound = couldBeFlySize; // If the encoder is within the arena and the sum of pixels is within a range that could be a fly
						// then the bottom camera may have found a fly.

						if (bottomCamFlyFound || debugStim) {
							// using the Kalman filter on the distance
							filter.Predict();
							filter.Correct(distance);

							// convert the distance from the center of the frame to real world coordinates
							bottomCamRecentFlyPos.x = encoderDataInst.encoderX + objectSpaceResolution * (float)distance.x; // grab the position of the bottom cam when it found a fly
							bottomCamRecentFlyPos.y = encoderDataInst.encoderY + objectSpaceResolution * (float)distance.y; // grab the position of the bottom cam when it found a fly

							// convert the stimulus point to real world coordinates
							stimPt.x = encoderDataInst.encoderX + objectSpaceResolution * stimDistance.x;
							stimPt.y = encoderDataInst.encoderY + objectSpaceResolution * stimDistance.y;
							arenaP.allowBottomCamToGo = true;
						}
						else {
							// stop the camera from moving
							filter.Init(initCoM);
							arenaP.allowBottomCamToGo = false;

							arenaP.bottomCamRecentFlyPos.x = bottomCamRecentFlyPos.x; // store the bottom cameras position anyway
							arenaP.bottomCamRecentFlyPos.y = bottomCamRecentFlyPos.y;

							// Instead of setting bottomCamRecentFlyPos, why not have the pos set to user-designated position?

							//cout << "Bot Cam did NOT find a fly..." << endl; // Displays if bot cam failed to find a fly. 
						}



						// send coordinates of stimulus point to setStimulus to check if it is in the zone to be stimulated with light
						if (debugStim)
						{

							//stimPt.x = encoderDataInst.encoderX + objectSpaceResolution * stimDistance.x;
							//stimPt.y = encoderDataInst.encoderY + objectSpaceResolution * stimDistance.y;
							optoStim.setStimulus((long long)stimPt.x, (long long)stimPt.y, true);
						}
						else
						{
							optoStim.setStimulus((long long)stimPt.x, (long long)stimPt.y, bottomCamFlyFound);
						}
					}
					else
					{
						filter.Predict();
						filter.Correct(distance);

					}
					est_dist = filter.statePt_pos; // This value is used at the other thread for automatic control
					est_vel = filter.statePt_vel; // This value is used at the other thread for automatic control=

					//distFilteredImgCoor.x = est_dist.x + center.x; // find the distance from the center on the y position
					distFilteredImgCoor.x = est_dist.x + center.x; // find the distance from the center on the y position
					distFilteredImgCoor.y = -est_dist.y + center.y; //I am putting (-) in front of the y moment. This is because top left corner is (0,0) in a matrix, but I now want bottom left to be (0,0).

					pForImage.x = p.x; // store the predicted x axis position
					pForImage.y = (cvimg.cols - 1) - p.y; // why does the y axis prediction/ point/ position differ from the x axis?

					if (arenaP.set_for_exp)
					{
						// get the current and future distances from the center of the arena for deciding whether to stop
						// the camera from moving too far off the edge
						// this is more useful when using image processing rather than YOLO detection

						const long long encoderXDist = (long long)(encoderDataInst.encoderX + (unsigned long)(distFilteredImgCoor.x * objectSpaceResolution)) - (long long)arenaP.spacer_center_encoder.x;
						const long long encoderYDist = (long long)(encoderDataInst.encoderY + (unsigned long)(distFilteredImgCoor.y * objectSpaceResolution)) - (long long)arenaP.spacer_center_encoder.y;
						const long long distanceToCenter_encoder_squared = (encoderXDist * encoderXDist) + (encoderYDist * encoderYDist);


						future_encoderXDist = encoderXDist + (long long)est_dist.x;
						future_encoderYDist = encoderYDist + (long long)est_dist.y;
						const long long future_distanceToCenter_encoder_squared = (future_encoderXDist * future_encoderXDist) + (future_encoderYDist * future_encoderYDist);
					}

					//Get size of the frame.
					if (firstFrame) //If the first frame is being processed then get the size of the frame and switch the state 
					{
						cout << "First Frame:" << endl; // Added by Sam on 9/29 for testing purposes. 
						fvFrameSize = cvimg.size(); // 832 x 632 -> Incorrect value? (-SPW, 9/29)

						int fvFrameSizeX = fvFrameSize.width; // cvimg[0].size();
						int fvFrameSizeY = fvFrameSize.height;
						//fvFrameSize = suggested_size.size();  // Added by Sam on 9/29 for testing purposes. 
						cout << fvFrameSizeX << endl;
						cout << fvFrameSizeY << endl;
						firstFrame = false;


					}
					//if (wnd.keyPressed(0x61)) // 0x53 is ASCII for: "a"
					//{
					//	int sumPixel = sum(dst)[0];
					//	cout << sumPixel << endl;
					//}

					/// TOGGLE WHETHER THE CURRENTLY VIEWED DATA IS SAVED OR NOT WITH THE "S" KEY:
					if (wnd.keyPressed(0x53)) // 0x53 is ASCII for: "S"
					{
						if (!saveState) // If there is no save state set
						{
							// I dont really get the logic for this one. If there is no save state and you no save command has been registered, then start saving? 
							if (!doSave) {
								doSave = TRUE; // start saving
								cout << "started saving" << endl;
								arenaP.turnOnSaveIndicator();
							}
							else // stop saving
							{
								doSave = FALSE;
								cout << "stopped saving" << endl;
								arenaP.turnOffSaveIndicator();
							}
						}

						saveState = 1; // if you press "S" it changes the save state to 1.
					}
					else
						saveState = 0; // otherwise set savestate to 0.

					// set the flyViewStruc values to send to another thread for saving to disk
					if (doSave)
					{
						// store important output data to chunkStrucSave
						chunkStrucSave = chunkStruc;
						//The signs and subtractions may need to be ajusted depending on your setup
						//distance.x and y are chosen as the position within the frame. Center of the frame is (0,0).
						//This is because we assume that the location of encoder and the center of the camera sensors are aligned.
						//Adaptor for the camera should be designed this way.
						chunkStrucSave.frameCoMX = static_cast<int>(round(distance.x));
						chunkStrucSave.frameCoMY = static_cast<int>(round(distance.y));
						chunkStrucSave.decoderdt = encoderDataInst.dt;
						chunkStrucSave.encoderX = encoderDataInst.encoderX;
						chunkStrucSave.encoderY = encoderDataInst.encoderY;
						chunkStrucSave.absCoMX = static_cast<unsigned long>(round(bottomCamRecentFlyPos.x));
						chunkStrucSave.absCoMY = static_cast<unsigned long>(round(bottomCamRecentFlyPos.y));
						chunkStrucSave.bottomCamSeesFly = (int)bottomCamFlyFound;
						chunkStrucSave.onLED = optoStim.getStimulusOnState();
						chunkStrucSave.center[0] = optoStim.center[0];
						chunkStrucSave.center[1] = optoStim.center[1];
						chunkStrucSave.bottomCamInCharge = arenaP.allowBottomCamToGo & bottomCamFlyFound;
						chunkStrucSave.manualOrAuto = motors.manualOrAuto;
						chunkStrucSave.stimulusVoltage = optoStim.getStimulusVoltage();
						chunkStrucSave.stimPointX = static_cast<unsigned long>(round(stimPt.x));
						chunkStrucSave.stimPointY = static_cast<unsigned long>(round(stimPt.y));

						string timeString;
						timeResult = time(NULL);
						ctime_s(timeStr, sizeof(timeStr), &timeResult);
						for (int i = 11; i < 19; i++)
							timeString.append(1, timeStr[i]);
						chunkStrucSave.clockTime = timeString;
						//chunkStrucSave.LEDState; // Added by Sam on 10/18
						flyViewSaveQ.push(chunkStrucSave);
					}

					// show the bottom camera view on screen by cloning the image, add a marker to show where the stimulus point is,
					// and send it into the queue to be shown on screen in another thread
					if (streamCounter % 16 == 0) // show us every 20th frame since human eyes cant really tell the difference anyway. The program still stores every frame, though. It just doesnt show them all
					{
						// show the image with a point mark at the centroid
						//circle(dst, pForImage, 5, Scalar(128, 0, 0), -1); // predicted fly CoM
						//circle(dst, center, 5, Scalar(128, 0, 0), -1); // Keep a circle at the center
						//circle(dst, distFilteredImgCoor, 10, Scalar(100, 0, 0), 2); // circle around predicted fly CoM
						//flyStream.push(dst.clone());
						const Mat cvimgWithBoundingBox(cvimg.clone());
						if (couldBeFlySize)
						{
							/*rectangle(cvimgWithBoundingBox, pt1, pt2, { 255,255,255 });
							rectangle(cvimgWithBoundingBox, pt3, pt4, { 255,255,255 });*/
							circle(cvimgWithBoundingBox, antPt, 5, { 255,255,255 });

						}
						flyStreamRaw.push(cvimgWithBoundingBox);
					}

					streamCounter++; // Iteratively increase stream counter
					if (streamCounter == 1000)
					{
						streamCounter = 0; // If the stream counter reaches 1000 reset it
					}
					/// TOP CAMERA CALIBRATION WITH THE 3 POINTS PLATE:
					// Andrew: old code for calibrating the top camera, which was being done for every experiment
					if (calib.isCalibrationStarted() && arenaP.set_for_exp)
					{
						const Point2f calibrationSquareEncoderLocation((float)encoderDataInst.encoderX + distance.x, (float)encoderDataInst.encoderY + distance.y);
						calib.calibrateCamera(calibrationSquareEncoderLocation);

						//	// Click "1" when the camera has reached the 1st plate:
						//	if (!arenaP.calib_marker_saved[0]) //  if the 1 key is pressed and the first arena calibration mark is not saved...
						//	{
						//	//	encoderDataInst.encoderX = encoderX; // Added by Sam on 10/1 for testing purposes
						//	//	encoderDataInst.encoderY = encoderY;

						//	//	//arenaP.calib_markers_encoder[0].x = encoderDataInst.encoderX + distance.x; // Original. set the x and y positions for the encoder that correspond to the first plate point
						//	//	arenaP.calib_markers_encoder[0].x = encoderDataInst.encoderX - distance.x; // Added by Sam on 9/29 for testing purposes
						//	//	arenaP.calib_markers_encoder[0].y = encoderDataInst.encoderY + distance.y; //
						//	//	arenaP.calib_marker_saved[0] = true;
						//	//	cout << "Got the world (encoder) coordinate of Point 1." << endl;
						//	//	cout << arenaP.calib_markers_encoder[0] << endl; // Added by Sam on 9/30 for testing purposes.

						//	//	//cout << "X: " << endl;
						//	//	//cout << arenaP.calib_markers_encoder[0].x << endl;
						//	//	//cout << "Y: " << endl;
						//	//	//cout << arenaP.calib_markers_encoder[0].y << endl;

						//	//cout << "distance: " << endl;
						//	//cout << distance << endl;
						//	//
						//	//cout << "encoderDataInst.encoderX: " << endl;
						//	//cout << encoderDataInst.encoderX << endl;
						//	//cout << "encoderDataInst.encoderY: " << endl;
						//	//cout << encoderDataInst.encoderY << endl;

						//	//cout << "encoder X: " << endl;
						//	//cout << encoderX << endl;
						//	//cout << "encoder Y: " << endl;
						//	//cout << encoderY << endl;

						//	//automatic calibration
						//	arenaP.calib_markers_encoder[0].x = 238205;
						//	arenaP.calib_markers_encoder[0].y = 86234;
						//	arenaP.calib_marker_saved[0] = true;
						//	cout << arenaP.calib_markers_encoder[0] << endl;
						//	}
						//	// Click "2" when the camera has reached the 2nd plate:
						//	if (!arenaP.calib_marker_saved[1]) // Cycle through the 2nd and 3rd plates and get their positions by leading the bottom camera to it
						//																				 // then pressing "2" to calibrate it
						//	{
						//		//encoderDataInst.encoderX = encoderX; // Added by Sam on 10/1 for testing purposes
						//		//encoderDataInst.encoderY = encoderY;

						//		////arenaP.calib_markers_encoder[1].x = encoderDataInst.encoderX + distance.x; // Original
						//		//arenaP.calib_markers_encoder[1].x = encoderDataInst.encoderX - distance.x; // Added by Sam on 9/29 for testing purposes
						//		//arenaP.calib_markers_encoder[1].y = encoderDataInst.encoderY + distance.y;
						//		//arenaP.calib_marker_saved[1] = true;
						//		//cout << "Got the world (encoder) coordinate of Point 2." << endl;
						//		//cout << arenaP.calib_markers_encoder[1] << endl; // Added by Sam on 9/30 for testing purposes.


						//		//cout << "distance: " << endl;
						//		//cout << distance << endl;

						//		//cout << "encoderDataInst.encoderX: " << endl;
						//		//cout << encoderDataInst.encoderX << endl;
						//		//cout << "encoderDataInst.encoderY: " << endl;
						//		//cout << encoderDataInst.encoderY << endl;

						//		//cout << "encoder X: " << endl;
						//		//cout << encoderX << endl;
						//		//cout << "encoder Y: " << endl;
						//		//cout << encoderY << endl;


						//		////cout << "X: " << endl;
						//		////cout << arenaP.calib_markers_encoder[1].x << endl;
						//		////cout << "Y: " << endl;
						//		////cout << arenaP.calib_markers_encoder[1].y << endl;

						//	//	cout << "distance X: " << endl;
						//	//	cout << distance.x << endl;
						//	//	cout << "distance Y: " << endl;
						//	//	cout << distance.y << endl;
						//	//automatic calibration
						//	arenaP.calib_markers_encoder[1].x = 159585;
						//	arenaP.calib_markers_encoder[1].y = 241237;
						//	arenaP.calib_marker_saved[1] = true;
						//	cout << arenaP.calib_markers_encoder[1] << endl;
						//	}
						//	// Click "3" when the camera has reached the 3rd plate:
						//	if (!arenaP.calib_marker_saved[2]) // Calibrate the 3rd plate position
						//	{
						//		//encoderDataInst.encoderX = encoderX; // Added by Sam on 10/1 for testing purposes
						//		//encoderDataInst.encoderY = encoderY;

						//		////arenaP.calib_markers_encoder[2].x = encoderDataInst.encoderX + distance.x; // Original
						//		//arenaP.calib_markers_encoder[2].x = encoderDataInst.encoderX - distance.x; // Added by Sam on 9/29 for testing purposes
						//		//arenaP.calib_markers_encoder[2].y = encoderDataInst.encoderY + distance.y;
						//		//arenaP.calib_marker_saved[2] = true;
						//		//cout << "Got the world (encoder) coordinate of Point 3." << endl;
						//		//cout << arenaP.calib_markers_encoder[2] << endl; // Added by Sam on 9/30 for testing purposes.

						//		//cout << "distance: " << endl;
						//		//cout << distance << endl;

						//		//cout << "encoderDataInst.encoderX: " << endl;
						//		//cout << encoderDataInst.encoderX << endl;
						//		//cout << "encoderDataInst.encoderY: " << endl;
						//		//cout << encoderDataInst.encoderY << endl;

						//		//cout << "encoder X: " << endl;
						//		//cout << encoderX << endl;
						//		//cout << "encoder Y: " << endl;
						//		//cout << encoderY << endl;

						//		////cout << "X: " << endl;
						//		////cout << arenaP.calib_markers_encoder[2].x << endl;
						//		////cout << "Y: " << endl;
						//		////cout << arenaP.calib_markers_encoder[2].y << endl;

						//	//	cout << "distance X: " << endl;
						//	//	cout << distance.x << endl;
						//	//	cout << "distance Y: " << endl;
						//	//	cout << distance.y << endl;
						//		//automatic calibration
						//	arenaP.calib_markers_encoder[2].x = 263650;
						//	arenaP.calib_markers_encoder[2].y = 261532;
						//	arenaP.calib_marker_saved[2] = true;
						//	cout << arenaP.calib_markers_encoder[2] << endl;
						//	}
						//}
						//// Press "5" key on numberpad to post X and Y encoder positions. - Added by Sam on 9/18
						////if (wnd.keyPressed(VK_NUMPAD5)) // the "4" key on the numberpad moves motor LEFT
						////{
						////	cout << "encoder X: " << endl;
						////	cout << encoderDataInst.encoderX << endl;
						////	cout << "encoder Y: " << endl;
						////	cout << encoderDataInst.encoderY << endl;

						////	cout << "distance X: " << endl;
						////	cout << distance.x << endl;
						////	cout << "distance Y: " << endl;
						////	cout << distance.y << endl;
						////}




					}
				}
				if (!stream) // If the stream is off
				{
					break; // break the sequence
				}
			}
		}
#pragma omp section
		
		{

			// DRIVING THE MOTORS(MANNULLY CONTROL)
			BOOL manualControl = TRUE; // Has manual control been set?
			int manualState = 0; // set the state for manual control to 0

			//Point2f wallCond_dist(0, 0); // Added by Sam on 10/26 to store est_dist corrected values. 
			//Point2f wallCond_vel(0, 0); // Added by Sam on 10/26 to store est_dist corrected values. 
			//Point2f arenaCenter(0, 0); // Added by Sam on 10/26 to store est_dist corrected values. 
			//Point2f frameCenter(0, 0); // Added by Sam on 10/26 to store est_dist corrected values. 

			// Loop is constantly running using data being set in other threads
			while (true) {

				Point2f virtualDist(0, 0); // set the initial values for virtual distance and virtual velocity to 0.
				Point2f virtualVel(0, 0); //
				int manualSpeed = 300; // Set the manual speed of the motor to 300. 300 what? Steps? yes, micrometer

				// Turn off illuminating LED when pressing L, in case it needs to be done to find the fly better in the top camera
				if (wnd.keyPressed(0x4C))
				{
					motors.StopIlluminatingLED();
				}
				else if (!motors.illuminatingLightOn)
				{
					motors.DriveIlluminatingLED();
				}

				// Click "M" to toggle between manual mode/ automatic mode:
				if (wnd.keyPressed(0x4D)) // 0x4D is ASCII for: "M"
				{
					if (!manualState) // If you click M and it is not in a manual state
					{
						// and there is no manual control
						if (!manualControl) 
						{
							manualControl = TRUE; // then set manual control to ON and turn automatic control OFF
							cout << "currently manual" << endl;
							motors.manualOrAuto = true;
						}
						else
						{
							manualControl = FALSE; // otherwise turn manual control OFF, and turn automatic control ON
							motors.manualOrAuto = false;
							cout << "currently automatic" << endl;
						}
					}
					manualState = 1; // manual state ON
				}
				else
					manualState = 0; // If no M key pressed, manualState is set to 0.


				// IF THE BOTTOM CAMERA IS SET TO AUTOMATIC:
				if (!manualControl)
				{

						// code for stopping the camera from leaving the arena
						//if (encoderLeavingArena)
						//{
						//	const long long future_encoderXOnlyDistSquared = (future_encoderXDist + (long long)encoderY) * (future_encoderXDist + (long long)encoderY);
						//	const long long future_encoderYOnlyDistSquared = ((long long)encoderX + future_encoderYDist) * ((long long)encoderX + future_encoderYDist);
						//	if (future_encoderXOnlyDistSquared > arenaP.arena_radius_squared)
						//	{
						//		est_dist.x = 0;
						//	}
						//	if (future_encoderYOnlyDistSquared > arenaP.arena_radius_squared)
						//	{
						//		est_dist.y = 0;
						//	}

						//}
						// Andrew: not sure what this is for, maybe for a previous process we don't do anymore
					if (!arenaP.set_for_exp) 
					{
						//This is before we start the experiement. We want to use the fake target, so we do not want allowBottomCamToGo permission. allowBottomCamToGo permission is only used when experiment is on going.
						motors.SetDirAndFreq(est_dist, est_vel, true, false);
					}
					else
							// runs if the top camera image is clicked to move the camera to the clicked point
							// fly position estimated in arenaP class in topCamProc.cpp
					{
						//cout << "Allow Bottom Cam To Go: "<< arenaP.allowBottomCamToGo << "\t" << "Bottom Cam Fly Found " << bottomCamFlyFound << endl;
						//---Control criteria after experiment started---//
						if (arenaP.topCamFlyFound) 
						{
							Point2f controlIn;
							Point2f controlInVel(0.0f, 0.0f);
							controlIn.x = (arenaP.flyPos_encoder.x - encoderX) / objectSpaceResolution;
							controlIn.y = (arenaP.flyPos_encoder.y - encoderY) / objectSpaceResolution;
							motors.SetDirAndFreq(controlIn, controlInVel, true, true); // if its automatic tracking and encoder-based
							if (norm(controlIn) < 30) 
							{
								arenaP.allowBottomCamToGo = true;
								arenaP.topCamFlyFound = false;
								//cout << "norm(controlIn) < 30" << endl;
							}
							if (firstCalling2) 
							{
								cout << "top cam in charge" << endl;
								firstCalling1 = true;
								firstCalling2 = false;
								firstCalling3 = true;
							}
						}
						// code for automatically following the fly
						else if (bottomCamFlyFound && arenaP.allowBottomCamToGo) 
						{
							// sleep call added after upgrading to a new computer caused loop to run faster and camera to become shakier
							Sleep(10);
							motors.SetDirAndFreq(est_dist, est_vel, true, false);

							if (firstCalling1) 
							{
								cout << "bottom cam in charge" << endl;
								firstCalling1 = false;
								firstCalling2 = true;
								firstCalling3 = true;
							}

						}

						else
							// stop the camera if fly is not found in the frame and nowhere in the top camera image is clicked
						{
							if (firstCalling3) {
								cout << "nobody in charge" << endl;
								firstCalling1 = true;
								firstCalling2 = true;
								firstCalling3 = false;
								motors.SetDirAndFreq(Point2f(0, 0), Point2f(0, 0), true, false);
							}
						}
					}
				}
				else // if MANUAL control is ON:
				{
					arenaP.allowBottomCamToGo = true;
					arenaP.topCamFlyFound = false;
					/// MOVING THE BOTTOM CAMERA MANUALLY WITH ARROW KEYS

						// MOVE BOT CAMERA UP/ FORWARD/ NORTH WITH UP KEY:
					if (wnd.keyPressed(VK_UP)) // the UP ARROW key on the numberpad moves motor UP
					{
						virtualDist.x = 0; // x position is unaffected
						virtualDist.y = manualSpeed; // Increase y position by set amount designated by manualSpeed (300)
					}

					// MOVE BOT CAMERA DOWN/ BACKWARD/ SOUTH WITH DOWN KEY:
					if (wnd.keyPressed(VK_DOWN)) // the DOWN ARROW key on the numberpad moves motor DOWN
					{
						virtualDist.x = 0; // x position is unaffected
						virtualDist.y = -manualSpeed; // move -300 steps *note there is a negative symbol in front of the 300*
					}

					// MOVE BOT CAMERA RIGHT/ EAST WITH RIGHT KEY:
					if (wnd.keyPressed(VK_RIGHT)) // the RIGHT ARROW key on the numberpad moves motor RIGHT
					{
						virtualDist.x = manualSpeed; // Increase X position by 300
						virtualDist.y = 0; // y position is unaffected
					}

					// MOVE BOT CAMERA LEFT/ WEST WITH LEFT KEY:
					if (wnd.keyPressed(VK_LEFT)) // the LEFT key on the numberpad moves motor LEFT
					{
						virtualDist.x = -manualSpeed; // move -300 steps *note there is a negative symbol in front of the 300*
						virtualDist.y = 0; // y position is unaffected
					}


					// THIS MOVEMENT IS NOT BASED ON INFORMATION FROM THE ENCODER (INDICATED BY THE 2ND "false"). THIS MEANS WE ARE MANUALLY CONTROLLING THE POSITION OF THE BOT CAMERA
					// AND THE PROPORTIONAL CONTROL IS NOT BEING USED. INSTEAD, A VIRTUAL DISTANCE AND VELOCITY ARE SET WHEN THE KEY IS PRESSED AND THOSE MOTIONS ARE INITIATED.
					motors.SetDirAndFreq(virtualDist, virtualVel, false, false); // Command motor to move based on virtual distance and virtual velocity while bot camera is under MANUAL control.
					//cout << virtualVel << endl;
					//motors.SetDirAndFreq(virtualDist, virtualVel, false, true); //
					// motors.SetDirAndFreq appears to be defined in gantry.cpp
					// line 81 of gantry.cpp: Gantry::SetDirAndFreq(cv::Point2f pt, cv::Point2f vel, bool automatic, bool encoder_based)
					// At the end of SetDirAndFreq, values for DAQmxSetChanAttribute are set. 

					// After the motor is moved with SetDirAndFreq, the changes are relayed to the DAQ.
				}
				if (!stream) // If no stream is present
				{
					break; // end the sequence
				}

			}
		}
#pragma omp section
		{
			//DISPLAY SETTING FOR BOTTOM VIEW
			// USE PARALLEL PROCESSING TO VIEW 1 ms OF A FRAME OF FLY DATA FROM THE BOTTOM CAMERA:
			// Thread for driving the motors "try_pop" TO REMOVE FRAMES FROM A STREAM AND DISPLAY THEM FOR 1 millisecond. 

			Mat tframe, t2frame, t2frameRaw;
			bool firstFrameT2Frame = true;
			bool firstFrameT2FrameRaw = true;
			while (true)
			{
				//try_pop provides a way of removing something from the queue in order to allow for parallel processing of certain things.
					// try_pop dequeues an item from the queue if one is available. This method is concurrency-safe.
				if (arenaStream.try_pop(tframe)) // If the arenaStream tframe is outside the queue...current, DO NOTHING
				{
					// showing top camera frame is now done in arenaP class
					// do some action on tframe 

					/*
					imshow("arena image", tframe);
					//namedWindow("current Image", WINDOW_NORMAL);
					//resizeWindow("current Image", tframe.rows / 2, tframe.cols / 2);
					*/
				}

				// old code for showing binarized image that is used for finding the fly after processing
				//			if (flyMaskStream.try_dequeue(tmask))
					//			imshow("fly mask", tmask);
				//if (flyStream.try_pop(t2frame)) // If t2frame is dequeued from the stream...
				//{
				//	if (firstFrameT2Frame)
				//	{
				//		wnd.newCVWindow("fly image");
				//		firstFrameT2Frame = false;
				//		cv::setMouseCallback("fly image", mouseCallbackFcn, NULL);
				//	}
				//	imshow("fly image", t2frame); // show an image of the fly
				//}

				//waitKey(1); // display the image for 1 millisecond

				if (flyStreamRaw.try_pop(t2frameRaw)) // If the t2frameRaw is dequeud from the stream...
				{
					if (firstFrameT2FrameRaw)
					{
						wnd.newCVWindow("fly image raw");
						firstFrameT2FrameRaw = false;
						cv::setMouseCallback("fly image raw", mouseCallbackFcn, NULL);
					}
					imshow("fly image raw", t2frameRaw); // show a raw image of the fly for 1 millisecond
				}

				waitKey(1); // display the image for 1 millisecond

				if (!stream) // If there is no stream...
				{
					// close the two generated windows
					destroyWindow("fly image");
					destroyWindow("fly image raw");
					break; // break the sequence
				}

			}

		}
#pragma omp section
		{
			// SAVEDATA PART
			/// WRITE THE ACQUIRED DATA TO A VIDEO FILE AND DOES SO IF SUCCESSFUL:
			// It also writes data to a text file and uses MatlabSaveData class for saving data to a mat file at the end

			Mat flyFrame;
			flyViewStruc fvStruc;

			//--- INITIALIZE VIDEOWRITER
			VideoWriter writer;
			// a "codec" encodes or decodes a digital data stream or signal.
			int codec = VideoWriter::fourcc('M', 'J', 'P', 'G');// fourcc('m', 'p', '4', 'v');  // select desired codec (must be available at runtime)
			double fps = 480;// 25.0;                          // framerate of the created video stream. 480 IS THE CONSTANT VALUE FOR FREQ, SET ON LINE ~55
			string filename = dataName + ".avi";             // name of the output video file
			//string filename = dataName + ".mp4v";             // name of the output video file
			writer.open(filename, codec, fps, fvFrameSize, false); // open the output video file for writing based on set criteria

			cout << "fvFrameSize:" << endl; // 800x600
			cout << fvFrameSize << endl;
			cout << "fps:" << endl; // 480
			cout << fps << endl;

			cout << "fvStruc.img:" << endl;
			cout << fvStruc.img << endl;

			int fvFrameSizeX = fvFrameSize.width;
			int fvFrameSizeY = fvFrameSize.height;

			// check if we succeeded
			if (!writer.isOpened())
			{ // If the output video file could not be opened. 
				cout << "Could not open the output video file for write\n" << endl;

			}

			//--- GRAB AND WRITE LOOP
			cout << "Writing videofile: " << filename << endl
				<< "Press any key to terminate" << endl;

			// ofstream = output file stream. The class "ofstream" describes an object that controls insertion of elements and encoded objects into a stream buffer
			ofstream wtextFile(dataName + ".txt", ofstream::out); // setup the output data file that will eventually have the stored structure data written to it.  
			//ofstream dataFile(dataName + ".dat", ios::binary);



			cout << (fvFrameSizeX - 592) / 2 << endl;
			cout << (fvFrameSizeY - 600) / 2 << endl;
			while (true)
			{
				if (flyViewSaveQ.try_pop(fvStruc)) // If the flyViewSave structure is removed from the stream queue...
				{
					try
					{

						if (fvStruc.onLED == 1)
						{
							putText(fvStruc.img, "ON", { 50, 50 }, FONT_HERSHEY_SIMPLEX, 1, Scalar(255), 4);
						}

						writer.write(fvStruc.img); // original

					}
					catch (const std::exception& e) // if an exception occurs (quite a vague description...)
					{
						cout << "exception" << endl; // output that an exception has occurred. 
					}


					/// WRITE THE DATA STORED IN fvStruc TO THE OUTPUT TEXT FILE:
					//wtextFile << fvStruc.dataNum << "\t" << fvStruc.camTime << "\t" << fvStruc.frameCoMX << "\t" << fvStruc.frameCoMY << "\t" << fvStruc.grabSucceeded << "\t" << fvStruc.imageDamaged << "\t" << fvStruc.decoderdt << "\t" << fvStruc.encoderX << "\t" << fvStruc.encoderY << "\t" << fvStruc.absCoMX << "\t" << fvStruc.absCoMY << "\t" << fvStruc.bottomCamSeesFly << "\n";
					wtextFile << fvStruc.dataNum << "\t" << fvStruc.camTime << "\t" << fvStruc.frameCoMX << "\t" << fvStruc.frameCoMY << "\t" << fvStruc.grabSucceeded << "\t" << fvStruc.imageDamaged << "\t" << fvStruc.decoderdt << "\t" << fvStruc.encoderX << "\t" << fvStruc.encoderY << "\t" << fvStruc.absCoMX << "\t" << fvStruc.absCoMY << "\t" << fvStruc.bottomCamSeesFly << "\t" << fvStruc.manualOrAuto << "\t" << fvStruc.onLED << "\t" << fvStruc.center[0] << "\t" << fvStruc.center[1] << "\t" << fvStruc.bottomCamInCharge << "\t" << fvStruc.clockTime << "\t" << 0 << "\t" << fvStruc.stimulusVoltage << "\n"; // Added LEDState
					//wtextFile << fvStruc.dataNum << "\t" << fvStruc.camTime << "\t" << fvStruc.frameCoMX << "\t" << fvStruc.frameCoMY << "\t" << fvStruc.grabSucceeded << "\t" << fvStruc.imageDamaged << "\t" << fvStruc.decoderdt << "\t" << fvStruc.encoderX << "\t" << fvStruc.encoderY << "\t" << fvStruc.absCoMX << "\t" << fvStruc.absCoMY << "\t" << fvStruc.bottomCamSeesFly << "\t" << motors.onLED << "\t" << motors.manualOrAuto << "\n"; // Added LEDState
					//cout << fvStruc.encoderX << endl;

					//CoM saved in pixel, time saved in nanoseconds, encoder positions + abs positions in micrometers
					//camTime: (ns)
					//frameCoMX, frameCoMY: pixels (distance from center of the ROI)
					//grabSucceeded: boolean
					//imageDamaged: boolean
					//decoderdt: (ns) ...i think
					//encoderX, Y, absCoMX, Y: (um micrometer)
					//

					//BinarySaveData binarySaveData(fvStruc);
					//dataFile.write(reinterpret_cast<char*>(&binarySaveData), sizeof(binarySaveData));

					// add all data to the vectors defined in matSaveData
					matSaveData.addFrameData(fvStruc);
				}

				if (!stream) // If there is no stream...
				{
					break; // break the sequence
				}
			}
			wtextFile.close(); // if the "while(true)" statement from above is false, then close the output text file.
			writer.release();
			//dataFile.close();

		}
	}
		

    /// WRITE A META TEXT FILE THAT LISTS THE ARENA CENTER COORDINATE AND THE OBJECT SPACE RESOLUTION:
	// These are both constant values 

	// Current time
	char timestr[26];
	time_t result = time(NULL);
	ctime_s(timestr, sizeof(timestr), &result);


	ofstream wtextFile(dataName + "_meta.csv", ofstream::out);
	wtextFile <<
		"Arena center coordinate X," <<
		"Arena Center coordinate Y," <<
		"Arena Radius," <<
		"Object space resolution," <<
		"Ending Optogenetic Stimulation Center X," <<
		"Ending Optogenetic Stimulation Center Y," <<
		"Optogenetic Stimulation Radius," <<
		"Stimulus Type," <<
		"Optogenetic Stimulus Slope," <<
		"Optogenetic Stimulus Width," <<
		"Stimulus Voltage," <<
		"Yolo," <<
		"Optogenetic Inner Circle Radius\n";

	wtextFile <<
		arenaP.spacer_center_encoder.x << "," <<
		arenaP.spacer_center_encoder.y << "," <<
		arenaP.arena_radius << "," <<
		objectSpaceResolution << "," <<
		optoStim.center[0] << "," <<
		optoStim.center[1] << "," <<
		optoStim.circleRadius << "," <<
		optoStim.getStimulusType() << "," <<
		optoStim.slope << "," <<
		optoStim.getStimulusWidth() << "," <<
		optoStim.getMaxVoltage() << "," <<
		"Yes" << "," <<
		optoStim.getSmallerCircleRadius();

	cout << "optoStim.centerX = " << optoStim.center[0] << endl;
	cout << "optoStim.centerY = " << optoStim.center[1] << endl;
	wtextFile.close(); // Close the output meta text file.

	cout << "session complete" << endl; // output that the fvStruc data has been written to the 2 text files 
	USB4_Shutdown(); // shutdown the decoder

	motors.StopX(); // stop the X axis motor.
	motors.StopY(); // stop the Y axis motor.
	motors.StopOptoLED();
	motors.StopIlluminatingLED();

	matSaveData.saveMatFile();
	return 0; 

		

} //END OF flyGantryV2.cpp CODE