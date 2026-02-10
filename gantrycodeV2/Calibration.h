#pragma once

#include "topCamProc.h"
#include <fstream>

class Calibration
{
public:
	Calibration(ArenaProc& arenaP_in, WindowManager& wnd_in);
	void startCalibratingTopCam();
	bool isCalibrationStarted();
	void calibrateCamera(cv::Point2f calibrationSquareEncoderLocation);
private:
	ArenaProc& arenaP;
	WindowManager& wnd;
	static void mouseCallbackFcn(int event, int x, int y, int flags, void* userdata);
private:
	std::vector<cv::Point2f> clickedPoints;
	std::string calibrationFileName = "C:\\ProgramData\\Gantry\\topCameraCalibrationParameters.dat";
	bool calibrationStarted = false;
	struct calibrationParameters
	{
		cv::Point2f clickedPoints[3];
		cv::Point2f encoderPoints[3];
	};
};