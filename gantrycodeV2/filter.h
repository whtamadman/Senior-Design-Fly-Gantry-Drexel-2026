#pragma once

#include <opencv2/video/tracking.hpp>
#include <math.h>

using namespace std;
using namespace cv;

class TrackerLocal
{
private:

	KalmanFilter KF;
	Mat_<float> measurement, prediction, estimated;

public:

	TrackerLocal();

	void Init(Point2f pt);
	Point2f Predict();
	Point2f Correct(Point2f measPt);
	Point2f statePt_pos;
	Point2f statePt_vel;
};

