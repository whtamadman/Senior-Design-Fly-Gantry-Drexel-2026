#include "pch.h"
#include "Calibration.h"

Calibration::Calibration(ArenaProc& arenaP_in, WindowManager& wnd_in)
	: arenaP(arenaP_in), wnd(wnd_in)
{
	// get saved calibration parameters from binary data file
	std::ifstream calibrationFile(calibrationFileName, std::ios::binary);
	if (calibrationFile.is_open())
	{
		calibrationParameters calParamsIn;
		calibrationFile.read(reinterpret_cast<char*>(&calParamsIn), sizeof(calibrationParameters));
		for (int i = 0; i < 3; i++)
		{
			clickedPoints.push_back(calParamsIn.clickedPoints[i]);
			arenaP.calib_markers_encoder[i] = calParamsIn.encoderPoints[i];
		}

		calibrationFile.close();

		arenaP.getMarkersPosTopCam(clickedPoints);
	}
	else
	{
		printf("Could not open top camera calibration file\n");
	}
}

// run the calibration steps for the top camera
void Calibration::startCalibratingTopCam()
{
	if (!calibrationStarted)
	{
		printf("Calibrate Top Camera\n");
		cv::setMouseCallback(arenaP.windowName, mouseCallbackFcn, &clickedPoints);
		clickedPoints.clear();
		arenaP.calib_marker_saved.clear();
		calibrationStarted = true;
		for (int i = 0; i < 3; i++)
		{
			arenaP.calib_marker_saved.push_back(false);
		}
	}
}

bool Calibration::isCalibrationStarted()
{
	return calibrationStarted;
}

// move the camera to each of the 3 squares and press 1, 2, or 3 to save the real world position
// according to the encoder and the location in the frame
// write calibration to file and use for experiment
void Calibration::calibrateCamera(cv::Point2f calibrationSquareEncoderLocation)
{
	int index;
	bool calibrationNumberKeyPressed = false;
	if (!arenaP.calib_marker_saved[0] && wnd.keyPressed(0x31))
	{
		index = 0;
		calibrationNumberKeyPressed = true;
	}
	else if (!arenaP.calib_marker_saved[1] && wnd.keyPressed(0x32))
	{
		index = 1;
		calibrationNumberKeyPressed = true;
	}
	else if (!arenaP.calib_marker_saved[2] && wnd.keyPressed(0x33))
	{
		index = 2;
		calibrationNumberKeyPressed = true;
	}

	if (calibrationNumberKeyPressed)
	{
		arenaP.calib_markers_encoder[index] = calibrationSquareEncoderLocation;
		arenaP.calib_marker_saved[index] = true;
		std::cout << "Marker " << index + 1 << " location saved:\n" << arenaP.calib_markers_encoder[index] << std::endl;
	}

	if (std::all_of(arenaP.calib_marker_saved.cbegin(), arenaP.calib_marker_saved.cend(), [](bool saved) {return saved; }))
	{
		std::ofstream calibrationFile(calibrationFileName, std::ios::binary);
		if (calibrationFile.is_open())
		{
			calibrationFile.clear();
			calibrationParameters calParamsOut;
			for (int i = 0; i < 3; i++)
			{
				calParamsOut.clickedPoints[i] = clickedPoints[i];
				calParamsOut.encoderPoints[i] = arenaP.calib_markers_encoder[i];
			}

			calibrationFile.write(reinterpret_cast<const char*>(&calParamsOut), sizeof(calParamsOut));
			calibrationFile.close();
			calibrationStarted = false;
			arenaP.getMarkersPosTopCam(clickedPoints);
			arenaP.getTransformationMatrix();
			arenaP.setFlyMouseCallbackFunc(&arenaP);
		}
		else
		{
			printf("ERROR: Could not save Calibration Parameters file\n");
			perror("Error details");
		}
	}
}

// click the 3 points on the screen to get their pixel locations
void Calibration::mouseCallbackFcn(int event, int x, int y, int flags, void* userdata)
{
	if (event == cv::EVENT_LBUTTONDOWN)
	{
		const cv::Point2f point((float)x, (float)y);
		std::vector<cv::Point2f>* clickedPoints = static_cast<std::vector<cv::Point2f>*>(userdata);
		if (clickedPoints->size() < 3)
		{
			printf("x = %d\ny= %d\n", x, y);
			clickedPoints->push_back(point);
		}
		else
		{
			printf("Three points already clicked\n");
		}
	}
}
