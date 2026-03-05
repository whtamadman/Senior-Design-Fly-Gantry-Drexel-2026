#pragma once
#include <NIDAQmx.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

#define RIGHT 0;
#define LEFT 1;
#define UP 0;
#define DOWN 1;

class Gantry {
private:
	//int somenum;
	uInt8 xyDir[2];
	TaskHandle taskHandleX;
	TaskHandle taskHandleY;
	TaskHandle taskHandleD;
	TaskHandle  taskHandleDAQ;
	float freqx, freqy;
	float	outputX, outputY;
	int right, left, up, down;
	uint pixelThresX;
	uint pixelThresY;
	bool xPermittedToGo;
	bool yPermittedToGo;
	float errorX;
	float errorY;
	float errorX_prev;
	float errorY_prev;
	float kp;
	float ki;
	float kd;
	float iErrorX;
	float iErrorY;
	float dErrorX;
	float dErrorY;
	double dt;

	// Added by Sam on 10/11 for testing purposes:
	TaskHandle taskHandleOptoLED;

	// Illumination Light
	TaskHandle taskHandleIlluminatingLED;

public:
	Gantry();
	bool onX;
	bool onY;
	void configure(const double frequency);
	void SetDirAndFreq(cv::Point2f pt, cv::Point2f vel, bool automatic, bool encoder_based); //bool == true: automatic. false: manual
	void DriveX();
	void DriveY();
	void StopX();
	void StopY();
	void SetDir(const int &section);
	bool eStopUpX;
	bool eStopDownX;
	bool eStopUpY;
	bool eStopDownY;
	void startDataAcquisition();
	bool manualOrAuto;

	// Added by Sam on 10/11 for testing purposes:
	void DriveOptoLED(float voltage);
	void StopOptoLED();
	bool onLED;

	// Illuminating Light
	void DriveIlluminatingLED();
	void StopIlluminatingLED();
	bool illuminatingLightOn = false;;
};