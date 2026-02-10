#include "pch.h"
#include "filter.h"
#include <stdio.h>
TrackerLocal::TrackerLocal()
{
	KF.init(4, 2, 0);

	measurement.create(2, 1);
	measurement.setTo(Scalar(0));

	statePt_pos.x = 0;
	statePt_pos.y = 0;
	statePt_vel.x = 0;
	statePt_vel.y = 0;

	KF.transitionMatrix = (Mat_<float>(4, 4) << 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1);

	setIdentity(KF.measurementMatrix);
	setIdentity(KF.processNoiseCov, Scalar::all(1e-2));		//adjust this for faster convergence - but higher noise (default: 1e-6)
	setIdentity(KF.measurementNoiseCov, Scalar::all(1e-1));
	setIdentity(KF.errorCovPost, Scalar::all(1e-1));
}


void TrackerLocal::Init(Point2f pt)
{
	KF.statePre.at<float>(0) = pt.x;
	KF.statePre.at<float>(1) = pt.y;
	KF.statePre.at<float>(2) = 0;
	KF.statePre.at<float>(3) = 0;
}


Point2f TrackerLocal::Predict()
{
	prediction = KF.predict();
	Point2f predictPt(prediction.at<float>(0), prediction.at<float>(1));

	return predictPt;
}

Point2f TrackerLocal::Correct(Point2f measPt)
{
	measurement(0) = measPt.x;
	measurement(1) = measPt.y;

	estimated = KF.correct(measurement);

	statePt_pos.x = estimated.at<float>(0);
	statePt_pos.y = estimated.at<float>(1);
	statePt_vel.x = estimated.at<float>(2);
	statePt_vel.y = estimated.at<float>(3);
	return statePt_pos;
}
