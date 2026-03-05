#include "pch.h"
#include "gantry.h"
#include <math.h>
#include <stdio.h>
#include <iostream> // added by Sam on 9/25 to try and get gantry.cpp to output values
#include <stdlib.h> // standard library header. 
//#include <NIDAQmx.h>
using namespace std; // 'std' refers to the standard library
Gantry::Gantry()
{
	xyDir[0] = 1;
	xyDir[1] = 1;

	taskHandleX = 0;
	taskHandleY = 0;
	taskHandleD = 0;
	taskHandleDAQ = 0;
	outputX = 0.0;
	outputY = 0.0;
	freqx = 0.0;
	freqy = 0.0;

	onX = false;
	onY = false;

	right = 0;
	left = 1;
	up = 0;
	down = 1;

	pixelThresX = 3;
	pixelThresY = 3;

	xPermittedToGo = true;
	yPermittedToGo = true;
	eStopUpX = false;
	eStopDownX = false;
	eStopUpY = false;
	eStopDownY = false;
	errorX = 0;
	errorY = 0;
	errorX_prev = 0;
	errorY_prev = 0;

	kp = 80.0;
	kd = 0.0;// 0.05; // 10000.0;// 30.0;
	ki = 0.0;// 7.0;

	dt = 0.0;

	iErrorX = 0.0;
	iErrorY = 0.0;
	dErrorX = 0.0;
	dErrorY = 0.0;

	manualOrAuto = true;
	onLED = false;
}


void Gantry::configure(const double frequency)
{
	// DAQmx Configure Code
	DAQmxCreateTask("", &taskHandleX);  // taskHandleX
	DAQmxCreateTask("", &taskHandleY); //taskHandleY
	DAQmxCreateTask("", &taskHandleD); // taskHandleDIRECTION
	DAQmxCreateTask("", &taskHandleDAQ); // Creates a task that next line's functions will populate with frequency and cycle information

	DAQmxCreateCOPulseChanFreq(taskHandleX, "Dev1/ctr0", "", DAQmx_Val_Hz, DAQmx_Val_Low, 0.0, 10000.00, 0.50);
	DAQmxCreateCOPulseChanFreq(taskHandleY, "Dev1/ctr1", "", DAQmx_Val_Hz, DAQmx_Val_Low, 0.0, 10000.00, 0.50);

	//Not sure what this is. should figure it out
	DAQmxCfgImplicitTiming(taskHandleX, DAQmx_Val_ContSamps, 100000); // Use this when you're not using time-dependent tasks (just counters)
	DAQmxCfgImplicitTiming(taskHandleY, DAQmx_Val_ContSamps, 100000); // Sets only the number of samples to acquire or generate without specifying timing. 
	DAQmxCreateDOChan(taskHandleD, "Dev1/port1/line2:3", "", DAQmx_Val_ChanForAllLines); // DAQmx create digital output channel "taskhandleD" with one channel for all lines
	DAQmxStartTask(taskHandleD); //only dir task starts now4628
	// DAQmxFcn(taskHandle, continuous vs finite sample number, if finite denote them here);
	// TaskHandle	The task to which to add the channels that this function creates.
	// DAQmxCreateDIChan = Creates channel(s) to measure digital signals and adds the channel(s) to the task you specify with taskHandle. ;

	//Setting clock pulse train
	DAQmxCreateCOPulseChanFreq(taskHandleDAQ, "Dev1/ctr2", "", DAQmx_Val_Hz, DAQmx_Val_Low, 0.0, frequency, 0.50); // "Dev2/ctr2" = counter number 2?
	// DAQmxCreateCOPulseChanFreq = Creates channel(s) to generate digital pulses that freq and dutyCycle define and adds the channel to the task you specify with taskHandle.
	DAQmxCfgImplicitTiming(taskHandleDAQ, DAQmx_Val_ContSamps, 100000); // Sets only the number of samples to acquire or generate without specifying timing. 


	dt = 1.0 / frequency;


	// Added by Sam on 10/15 for testing purposes:
	DAQmxCreateTask("", &taskHandleOptoLED);  // taskHandleLED
	int var = 1;
	DAQmxCreateAOVoltageChan(taskHandleOptoLED, "Dev1/ao0", "", -5.0, 5.0, DAQmx_Val_Volts, NULL);

	// Illuminating Light
	DAQmxCreateTask("", &taskHandleIlluminatingLED);
	DAQmxCreateAOVoltageChan(taskHandleIlluminatingLED, "Dev1/ao1", "", -5.0, 5.0, DAQmx_Val_Volts, NULL);
}

// Sets the direction and frequency of the motors through modulatory input from DAQmx:
void Gantry::SetDirAndFreq(cv::Point2f pt, cv::Point2f vel, bool automatic, bool encoder_based)
{
	errorX = pt.x; // X encoder position
	errorY = pt.y; // Y encoder position
	dErrorX = vel.x * 100; // The derivative/ velocity of X position as a percent
	dErrorY = vel.y * 100; // The derivative/ velocity of Y position as a percent

	// Andrew: kp values may be changed for smoother or better tracking
	int maxFreq;
	if (encoder_based) // Whether or not the gantry is receiving info from the encoder? 
	{
		kp = 10; // what is kp? What is the relevance of 10?
		maxFreq = 7000;// 9000;// 5900;
		// Why 7000 instead of 480.0 like in the flyGantryV2?
	}
	else
	{
		kp = 40; // What is kp? What is the relevance of 80?
		maxFreq = 9000; // Why 9000 instead of 480.0 like in the flyGantryV2?
	}
	if (automatic)
	{
		if ((abs(errorX) < 1.0e9) & (abs(errorY) < 1.0e9))
		{
			
			iErrorX += (int)errorX * dt;
			iErrorY += (int)errorY * dt;

			outputX = kp * (int)errorX + ki * iErrorX + kd * dErrorX;
			outputY = kp * (int)errorY + ki * iErrorY + kd * dErrorY;

			//// Added by Sam on 9/25 to try and fix the +/- sign swapping due to errorX
			//if (errorX < 0 && outputX > 0) {
			//	outputX = -1 * outputX;
			//}
			//if (errorY < 0 && outputY > 0) {
			//	outputY = -1 * outputY;
			//}

			// ki and kd are both zero. What is their purpose?

			//cout << ki << endl;
		}

	}
	else
	{
		//cout << "else Condition:" << endl; // This just spams incessently 
		outputX = 1000.0 * errorX; // initial frequency * errorX? Only used value of 1000 besides the final resetting freqx to 1000.
		outputY = 1000.0 * errorY;

		//// Added by Sam on 9/25 to try and fix the +/- sign swapping due to errorX
		//if (errorX < 0 && outputX > 0) {
		//	outputX = -1 * outputX;
		//}
		//if (errorY < 0 && outputY > 0) {
		//	outputY = -1 * outputY;
		//}

	}
	freqx = abs(outputX);
	freqy = abs(outputY);


	// Added by Sam on 9/25 to check the transformation of position input:
//	if (outputX != 0 && outputX < 300000 && outputX > -300000) {
//	//cout << "outputX:" << endl;
//	//cout << outputX << endl;
//}
//	if (outputY != 0 && outputY < 300000 && outputY > -300000) {
//	//	cout << "outputY:" << endl;
//	//	cout << outputY << endl;
//	}
//	if (errorX != 0 && errorX < 300 && errorX > -300) {
//	//	cout << "errorX:" << endl;
//	//	cout << errorX << endl;
//	}
//	if (errorY != 0 && errorY < 300 && errorY > -300) {
//	//	cout << "errorY:" << endl;
//	//	cout << errorY << endl;
//	}
	if (outputX >= 0.0 && outputY >= 0.0)
	{
		Gantry::SetDir(1);
	}
	else if (outputX < 0.0 && outputY >= 0.0)
	{
		Gantry::SetDir(2);
	}
	else if (outputX < 0.0 && outputY < 0.0)
	{
		Gantry::SetDir(3);
	}
	else if (outputX >= 0.0 && outputY < 0.0)
	{
		Gantry::SetDir(4);

	}


	if (eStopUpX)
	{
		if (errorX >= 0) {
			xPermittedToGo = false;
		}
		else
		{
			xPermittedToGo = true;
		}
	}
	else if (eStopDownX)
	{
		if (errorX >= 0) {
			xPermittedToGo = true;
		}
		else
		{
			xPermittedToGo = false;
		}
	}
	else
	{
		xPermittedToGo = true;
	}

	if (eStopUpY)
	{
		if (errorY >= 0) {
			yPermittedToGo = false;
		}
		else
		{
			yPermittedToGo = true;
		}
	}
	else if (eStopDownY)
	{
		if (errorY >= 0) {
			yPermittedToGo = true;
		}
		else
		{
			yPermittedToGo = false;
		}
	}
	else
	{
		yPermittedToGo = true;
	}


	static const int minFreq = 30;// 9000;// 5900;

	//freqx = 0.3 * abs(x)*abs(x)+10;
	//freqy = 0.3 * abs(y)*abs(y)+10;


	//freqx = 3000 / (1 + exp(-0.2*abs(x) + 5)) + 1;
	//freqy = 3000 / (1 + exp(-0.2*abs(y) + 5)) + 1; 

	//freqx = 0.8*abs(x)*abs(x) + 10*abs(x) + 10;
	//freqy = 0.8*abs(y)*abs(y) + 10*abs(y) + 10;

	if (freqx >= maxFreq)
		freqx = maxFreq;
	if (freqy >= maxFreq)
		freqy = maxFreq;
	/*
	if (freqx <= minFreq && automatic)
		freqx = minFreq;
	if (freqy <= minFreq && automatic)
		freqy = minFreq;
	*/

	//std::cout << freqx << "\t" << freqy << std::endl;

	//std::cout << x << " " << y << std::endl;
	static const uint bigThres = 4;// 4;// 7;// 8;
	static const uint smallThres = 2;// 2;// 2;// 2;

	if (((!(abs(errorX) > pixelThresX) || abs(errorX) > 1.0e9) && onX == true) || !xPermittedToGo)
	{
		pixelThresX = bigThres;
		Gantry::StopX();
	}
	if (((!(abs(errorY) > pixelThresY) || abs(errorY) > 1.0e9) && onY == true) || !yPermittedToGo)
	{
		pixelThresY = bigThres;
		Gantry::StopY();
	}

	if ((abs(errorX) > pixelThresX && abs(errorX) < 1.0e9 && onX == false) && xPermittedToGo)
	{
		pixelThresX = smallThres;
		Gantry::DriveX();
	}
	if ((abs(errorY) > pixelThresY && abs(errorY) < 1.0e9 && onY == false) && yPermittedToGo)
	{
		pixelThresY = smallThres;
		Gantry::DriveY();
	}
	//double dutyx = 0.000167 * freqx;
	//double dutyy = 0.000167 * freqy;
	double dutyx = 0.00167 * freqx; // sets dutyx value based on modulation by freqx. freqx = abs(outputX);
	double dutyy = 0.00167 * freqy;

	//std::cout << freqx << "\t" << freqy << "\t" << onX*1 <<"\t" <<onY*1 << std::endl;

	// Based on the positional state of X and the duty cycle of X, the DAQ modulates the distance between pulses for X. AKA it modulates the proportional control of X's motor.
	DAQmxSetChanAttribute(taskHandleX, "Dev1/ctr0", DAQmx_CO_Pulse_DutyCyc, dutyx); // taskHandleX may simply be the positional state of X.
	DAQmxSetChanAttribute(taskHandleY, "Dev1/ctr1", DAQmx_CO_Pulse_DutyCyc, dutyy);
	DAQmxSetChanAttribute(taskHandleX, "Dev1/ctr0", DAQmx_CO_Pulse_Freq, (float64)freqx, 1000); // 
	DAQmxSetChanAttribute(taskHandleY, "Dev1/ctr1", DAQmx_CO_Pulse_Freq, (float64)freqy, 1000); // 1000 is the buffer size
	// Stores 2 attributes (duty cycle and frequency) under the same channel ("Dev2/ctr0") for taskHandleX/Y and denotes a buffer size of 1000.
	// This taskHandleX/Y information is then used to drive and stop the X and Y motors below. 
}


//These are all private
void Gantry::DriveX()
{
	DAQmxStartTask(taskHandleX);
	onX = true;
}

void Gantry::DriveY()
{
	DAQmxStartTask(taskHandleY);
	onY = true;
}

void Gantry::StopX()
{
	DAQmxStopTask(taskHandleX);
	onX = false;
}

void Gantry::StopY()
{
	DAQmxStopTask(taskHandleY); // Stops the task and data acquisition; stops the task without releasing the resources (As in it doesnt stop the motor, just the acquisition of info from the motor).
	// It stops the acquisition of data from the motor but retains the previous state with the Driver controlling the motor.
	// In this way, the DAQmx can cease gaining information from the motor while keeping the motor running.
	// Would this stop proportional control?
	onY = false;
}

void Gantry::SetDir(const int &section)
{
	switch (section)
	{
	case 1:
		xyDir[0] = left;
		xyDir[1] = down;
		break;

	case 2:
		xyDir[0] = right;
		xyDir[1] = down;
		break;

	case 3:
		xyDir[0] = right;
		xyDir[1] = up;
		break;

	case 4:
		xyDir[0] = left;
		xyDir[1] = up;
		break;
	}
	//std::cout << "working" << std::endl;
	DAQmxWriteDigitalLines(taskHandleD, 1, 1, 10.0, DAQmx_Val_GroupByChannel, xyDir, NULL, NULL);
}

void Gantry::startDataAcquisition()
{
	DAQmxStartTask(taskHandleDAQ);
}

void Gantry::DriveOptoLED(float voltage)
{
	DAQmxStartTask(taskHandleOptoLED);
	DAQmxWriteAnalogScalarF64(taskHandleOptoLED, 0, 1, voltage, NULL);
	onLED = true;
}

void Gantry::StopOptoLED()
{
	DAQmxWriteAnalogScalarF64(taskHandleOptoLED, 0, 1, 0, NULL);
	DAQmxStopTask(taskHandleOptoLED);
	onLED = false;
}

void Gantry::DriveIlluminatingLED()
{
	DAQmxStartTask(taskHandleIlluminatingLED);
	DAQmxWriteAnalogScalarF64(taskHandleIlluminatingLED, 0, 1, 5, NULL);
	illuminatingLightOn = true;
}

void Gantry::StopIlluminatingLED()
{
	DAQmxWriteAnalogScalarF64(taskHandleIlluminatingLED, 0, 1, 0, NULL);
	DAQmxStopTask(taskHandleIlluminatingLED);
	illuminatingLightOn = false;
}
