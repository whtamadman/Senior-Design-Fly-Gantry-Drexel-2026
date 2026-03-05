#pragma once
#include <string>
#include <opencv2/opencv.hpp>
struct flyViewStruc
{
	// Variables that are being saved to the output text file. 
	cv::Mat img;
	unsigned long long int camTime; // The timestamp (in nanoseconds) where the camera captures a frame.
	int grabSucceeded; // Whether or not the camera was successfully able to capture a frame. (1=Y,0=N)
	int imageDamaged; // Whether or not the image was damaged upon acquisition. (1=Y,0=N)
	int frameCoMX; // The number of pixels the fly's center of mass is away from the frame's X axis (pixels). The frame itself is a 6x6 pixel grid. 
	int frameCoMY; // The number of pixels the fly's center of mass is away from the frame's Y axis (pixels).
	unsigned long dataNum; // dataNum stores the iteratively increasing imgCnt (image count) and encCnt (encoder count) and eventually checks whether the two are different. 
	// If they are different then frames are being skipped. 

	//encoder data fields. Only use for making structure for data saving.
	unsigned long encoderX; // Sets the field where the encoder's X position can be stored
	unsigned long encoderY; // Sets the field where the encoder's Y position can be stored
	unsigned long decoderdt; // Sets the field where the decoder can calculate the change in time of the encoder to figure out if frames are being skipped. (ns)

	//final positional value for saving
	unsigned long absCoMX; // Stores the bottom camera's recently identified fly X position
	unsigned long absCoMY; // Stores the bottom camera's recently identified fly Y position

	//point used for stimulus on or off
	unsigned long stimPointX;
	unsigned long stimPointY;

	int bottomCamSeesFly; // Stores the state of whether the bottom camera can see the fly. 

	//optogenetic stimulation information
	bool onLED;
	long long center[2];
	float stimulusVoltage;

	bool bottomCamInCharge;

	std::string clockTime;

	int sumPixel;

	bool manualOrAuto;
};

