#pragma once
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/calib3d.hpp>
#include <iostream>

#include <sstream>
#include <fstream>
#include <windows.h>

#include <numeric>
#include <vector>

#include "OptoStim.h"
#include "WindowManager.h"

using namespace cv;
using namespace std;
typedef Point_<unsigned long> Point2us;
class OptoStim;

class ArenaProc {
private:
	//int somenum;
	vector<Point2f> spacer_markers_cam; // where the markers are for marking the edge of the arena- not currently being used
	Mat cameraMatrix; // holds camera values for undistorting image
	Mat distCoefficient; // distortion coefficients
	bool first_frame; // whether it's the first frame
	Mat map1, map2; // used for undistorting
	int thresh; // used for finding fly in arena- not working now
	bool markersPlaced;
	float spacer_radius_cam;
	vector<Point2f> calib_markers_cam;
	vector<Point2f> centers;
	vector<Point2f>* centersPtr;
	void showOptogeneticStimulusArea();
	Mat inverseTransMat;
	vector<Point2f> cameraBound1;
	vector<Point2f> cameraBound2;
	int cameraCircleRadiusSquared; // radius of the arena in the camera
	int cameraCircleCenter[2]; // where the arena is in the camera
	OptoStim& optoStim; // reference to OptoStim object
	void setOptoStimParameters(int x, int y);
	void setOptoCircleView();
	void calculateArenaDimensions();
	void setFlyEncoderPosition();
	bool saveDataIndicatorOn; // whether to display "save" on the top camera image
	Mat stimulusZoneView; // to set where the stimulus zone will be shown
	Mat encoderLocationsByPixel; // maps each pixel to real world coordinates
	
	static constexpr float radiusOffset = 7000.0f;
public:
	ArenaProc(OptoStim& optoStim_in, WindowManager& wnd_in);
	bool loadCameraCalibration(string name);
	Mat undistorted; // undistorted image
	void undistort(Mat rawImg);
	Mat calibMarkerImg;
	Mat topFlyImg;
	void getMarkersPosTopCam(vector<Point2f> clickedPoints);
	void getSpacers();

	void turnOnSaveIndicator();
	void turnOffSaveIndicator();

	void findFlyPos(unsigned long x, unsigned long y);

	void setOptoZoneViewMat();

	void showTopCamView();

	//short shx;
	//short shy; //markers for cam position

	Point2f flyPos_cam; //returned by findFlyPos
	Point2f flyPos_encoder; //returned by findFlyPos
	bool topCamFlyFound; //returned by findFlyPos

	bool allowBottomCamToGo; //manipulated in the main function

	// related to calibrate top camera
	bool spacer_found; //checked
	bool topcam_calib_markers_found;
	bool bottomcam_calib_markers_found();
	vector<Point2f> calib_markers_encoder;
	vector<bool> calib_marker_saved;

	void getTransformationMatrix();
	Mat transMat;

	// realted to finding the location of the arena using the spacers
	bool coordinate_calibrated;
	bool set_for_exp;
	Point2f spacer_center; //world mm
	Point2f spacer_center_cam;
	float arena_radius;
	long long arena_radius_squared;

	Point2f bottomCamRecentFlyPos; // the last location of the fly from the encoder and bottom camera

	void convertSpacerCenter(); //returns
	Point2f spacer_center_encoder;

	WindowManager& wnd; // reference to window manager
	String windowName; // name of window

	void setFlyMouseCallbackFunc(ArenaProc* arenaP);
	static void calibrationMouseCallbackFunc(int event, int x, int y, int flags, void* userdata);
	static void flyMouseCallbackFunc(int event, int x, int y, int flags, void* userdata);
};
