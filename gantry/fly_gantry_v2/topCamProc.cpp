#include "pch.h"
#include "topCamProc.h"
#include <math.h>
#include <stdio.h>
#include <NIDAQmx.h>
#include "gantry.h"
using namespace std; // 'std' refers to the standard library


ArenaProc::ArenaProc(OptoStim& optoStim_in, WindowManager& wnd_in)
	:
	optoStim(optoStim_in),
	wnd(wnd_in),
	windowName("Top Camera")
{
	optoStim.setArenaPReference(this);
	centersPtr = &centers;
	spacer_found = false;
	coordinate_calibrated = false;
	cameraMatrix = Mat::eye(3, 3, CV_64F);
	first_frame = true;
	markersPlaced = false;
	set_for_exp = false;
	thresh = 75; // 150; // 75; // 200; //230;// 450; // Currently used thresh = 200; // Changing to 150 seemed to improve ability to see fly in arena. 
	calib_markers_encoder.resize(3);
	calib_marker_saved.resize(3, false);
	topCamFlyFound = false;
	allowBottomCamToGo = true;
}

// the following checks if all elements in calib_marker are saved.
bool ArenaProc::bottomcam_calib_markers_found() {
#if (!DEBUG)
	imshow(windowName, undistorted);
	waitKey(1);
#endif
	return std::all_of(calib_marker_saved.begin(), calib_marker_saved.end(), [](bool v) { return v; });
}

// load camera matrix from file
bool ArenaProc::loadCameraCalibration(string name)
{
	ifstream inStream(name);
	if (inStream)
	{
		uint16_t rows;
		uint16_t columns;

		inStream >> rows;
		inStream >> columns;

		cameraMatrix = Mat(Size(rows, columns), CV_64F);

		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c < columns; c++)
			{
				double read = 0.0f;
				inStream >> read;
				cameraMatrix.at<double>(r, c) = read;
				cout << cameraMatrix.at<double>(r, c) << "\n";

			}
		}

		//Distortion Coefficients
		inStream >> rows;
		inStream >> columns;

		distCoefficient = Mat::zeros(rows, columns, CV_64F);

		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c < columns; c++)
			{
				double read = 0.0;
				inStream >> read;
				distCoefficient.at<double>(r, c) = read;
				cout << distCoefficient.at<double>(r, c) << "\n";
			}
		}
		inStream.close();
		return true;
	}
	return false;


}

// undistort the camera image using camera matrix
void ArenaProc::undistort(Mat frame)
{
	// encode the frame into the videofile stream

	//Sam Edit:
	//Mat RegOI2(frame, Rect(546, 4, 1000, 900));



	if (first_frame) {

		// Original:
		initUndistortRectifyMap(cameraMatrix, distCoefficient, Mat(),
			getOptimalNewCameraMatrix(cameraMatrix, distCoefficient, frame.size(), 1, frame.size(), 0),
			frame.size(), CV_16SC2, map1, map2);

		// Sam Edit:
	//	initUndistortRectifyMap(cameraMatrix, distCoefficient, Mat(),
	//		getOptimalNewCameraMatrix(cameraMatrix, distCoefficient, RegOI2.size(), 1, RegOI2.size(), 0),
	//		RegOI2.size(), CV_16SC2, map1, map2);


	//	Point2f newFrameSize(592, 600);
	//	initUndistortRectifyMap(cameraMatrix, distCoefficient, Mat(),
	//		getOptimalNewCameraMatrix(cameraMatrix, distCoefficient, frame.size(), 1, frame.size(), 0),
	//		newFrameSize, CV_16SC2, map1, map2);
		// FRAME SIZE 1080 x 1920 
		//cout << frame.size() << endl;

		wnd.newCVWindow(windowName.c_str());
		setMouseCallback(windowName, calibrationMouseCallbackFunc, centersPtr);

		first_frame = false;

	}
	
	remap(frame, undistorted, map1, map2, INTER_LINEAR); // Original
	rotate(undistorted, undistorted, ROTATE_90_CLOCKWISE);
	//remap(RegOI2, undistorted, map1, map2, INTER_LINEAR); // Sam Edit

}

// not currently being used
void ArenaProc::getSpacers() {
	//const int max_thresh = 500;
	//Mat undistortedInvert;
	//Mat canny_output;
	//Mat contours2;
	//static RNG rng(12345);
	//Canny(undistorted, canny_output, thresh , thresh * 2);
	//vector<vector<Point> > contours;
	//findContours(canny_output, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);
	//vector<vector<Point>> contours_poly;// (contours.size());
	//vector<vector<Point>> contours_poly2;// (contours.size());
	////vector<Rect> boundRect(contours.size());
	//vector<Point2f> centers;// (contours.size());
	//vector<float> radius;// (contours.size());
	//float radiusTemp;
	//Point2f centersTemp;
	//vector<Point> countourPloyTemp;
	//for (size_t i = 0; i < contours.size(); i++)
	//{
	//	approxPolyDP(contours[i], countourPloyTemp, 3, true);
	//	//boundRect[i] = boundingRect(contours_poly[i]);
	//	minEnclosingCircle(countourPloyTemp, centersTemp, radiusTemp);

	//	// Initial values: <7 and >5
	//	if (radiusTemp < 7 && radiusTemp > 3) {//Here, radius means the size of the object. We are looking for spacer markers. Adjust the range of "radius" if needed.
	//		bool distinctive = true;
	//		if (centers.size() > 0)
	//		{
	//			for (size_t j = 0; j < centers.size(); j++)
	//			{
	//				float distance = norm(centers[j] - centersTemp);
	//				if (distance < 100) {
	//					distinctive = false;
	//				}
	//			}
	//		}

	//		if (distinctive) {
	//			centers.push_back(centersTemp);
	//			radius.push_back(radiusTemp);
	//			contours_poly.push_back(countourPloyTemp);
	//		}

	//	}

	//}
	//Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	//for (size_t i = 0; i < contours_poly.size(); i++)
	//{
	//	Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
	//	drawContours(drawing, contours_poly, (int)i, color);
	//	//rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2);
	//	circle(drawing, centers[i], (int)radius[i], color, 2);

	//	// Draw circles and identify shapes on greyscale top cam view
	//	threshold(undistorted, undistortedInvert, 116, 255, THRESH_BINARY); // 116 works really well. slight improvements can be made.
	//	//threshold(undistortedInvert, undistortedInvert, 50, 255, THRESH_BINARY);
	//	drawContours(undistortedInvert, contours_poly, (int)i, color);
	//	circle(undistortedInvert, centers[i], (int)radius[i], color, 2);

	//}

	//for (int y = 100; y < 200; y++)
	//{
	//	for (int x = 0; x < undistorted.cols; x++)
	//	{
	//		Vec3b& color = undistorted.at<Vec3b>(y, x);

	//		const int redChannelValue = color[2];
	//		const int cappedRedValue = min(redChannelValue + 50, 255);

	//		color[2] = cappedRedValue;
	//	}
	//}

	//imshow("Contours", drawing); // shows binarized shape-outlined top cam view
#if (!DEBUG)
	imshow(windowName, undistorted); // Shows greyscale top cam view
	//imshow("Top Cam View - Inverted", undistortedInvert); // Shows greyscale top cam view
	waitKey(1);
#endif
	//cout << contours_poly.size() << endl;

	// press Q

	Mat testMat();

	//if (wnd.keyPressed(81)) {
		//automatic calibration:
	centers.push_back(Point2f(328, 30));
	centers.push_back(Point2f(725, 138));
	centers.push_back(Point2f(829, 535));
	centers.push_back(Point2f(541, 825));
	centers.push_back(Point2f(149, 722));
	centers.push_back(Point2f(39, 325));

		char yesno = 'n';
		if (centers.size() == 6) {
			//cout << "Six points found. Please confirm that the spacer markers are correctly identified (y/n)" << endl;
			//cin >> yesno;
			//if (yesno == 'y')
			//{
				cout << "Spacer found" << endl;
				spacer_markers_cam = centers;

				Mat mean_;
				reduce(centers, mean_, 01, REDUCE_AVG);
				// convert from Mat to Point 
				Point2f mean(mean_.at<float>(0, 0), mean_.at<float>(0, 1));

				spacer_center_cam = mean;

				vector<float> radiuses;
				for (int k = 0; k < spacer_markers_cam.size(); k++)
				{
					radiuses.push_back(cv::norm(Mat(spacer_markers_cam[k]), Mat(spacer_center_cam), NORM_L2));
				}
				spacer_radius_cam = std::accumulate(radiuses.begin(), radiuses.end(), 0.0) / radiuses.size();
				spacer_found = true;
				//destroyWindow("Top Cam View - Grayscale");
				cout << "Centers for Calibration Step 1: " << centers << endl;
				centers.clear();
			//}
		}

		//if (centers.size() != 6 || yesno == 'n')
		//{
		//	int input;
		//	cout << "Try different threshold for finding contours (any number between 1~500ish). Currently " << thresh << "." << endl;
		//	cin >> input;
		//	thresh = input;
		//}
	//}
}

void ArenaProc::turnOnSaveIndicator()
{
	saveDataIndicatorOn = true;
}

void ArenaProc::turnOffSaveIndicator()
{
	saveDataIndicatorOn = false;
}

// calibrate the top camera image with the encoder position
// currently using calibration parameters saved in a file or calculated in Calibration class
void ArenaProc::getMarkersPosTopCam(vector<Point2f> clickedPoints) {
	//Mat canny_output;
	//static RNG rng(12345);
	//Canny(undistorted, canny_output, thresh, thresh * 2);
	//vector<vector<Point> > contours;
	//findContours(canny_output, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);
	//vector<vector<Point>> contours_poly;// (contours.size());
	////vector<Rect> boundRect(contours.size());
	//vector<Point2f> centers;// (contours.size());
	//vector<float> radius;// (contours.size());
	//float radiusTemp;
	//Point2f centersTemp;
	//vector<Point> countourPloyTemp;

	//for (size_t i = 0; i < contours.size(); i++)
	//{
	//	approxPolyDP(contours[i], countourPloyTemp, 3, true);
	//	//boundRect[i] = boundingRect(contours_poly[i]);
	//	minEnclosingCircle(countourPloyTemp, centersTemp, radiusTemp);

	//	if (radiusTemp < 7 && radiusTemp > 5) { //Here, radius means the size of the object. We are looking for calibration markers. Adjust the range of "radius" if needed. Currently, my calibration markers are smaller than the spcaer markers. Therefore the size requirement is smaller.
	//		bool distinctive = true;
	//		bool insideArena = true;
	//		if (centers.size() > 0)
	//		{
	//			//if the point is close (<100) to at least one of the saved points, mark it as NOT distinctive. 
	//			for (size_t j = 0; j < centers.size(); j++)
	//			{
	//				float distance = norm(centers[j] - centersTemp);
	//				if (distance < 100) {
	//					distinctive = false;
	//				}
	//			}
	//		}

	//		//if the point is exisiting beyond the arena markers mark it as NOT inside arena.
	//		float distanceToCenter = norm(Mat(centersTemp), Mat(spacer_center_cam), NORM_L2);
	//		if (distanceToCenter >= 0.9*spacer_radius_cam) {
	//			insideArena = false;
	//		}

	//		if (distinctive && insideArena) {
	//			centers.push_back(centersTemp);
	//			radius.push_back(radiusTemp);
	//			contours_poly.push_back(countourPloyTemp);
	//		}

	//	}

	//}
	//Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	//for (size_t i = 0; i < contours_poly.size(); i++)
	//{
	//	Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
	//	drawContours(drawing, contours_poly, (int)i, color);
	//	//rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2);
	//	circle(drawing, centers[i], (int)radius[i], color, 2);

	//	putText(drawing, to_string(i + 1), centers[i], FONT_HERSHEY_SIMPLEX, /*font scale*/4, color, /*thickness*/2,/*line type*/ 8);
	//}
	//imshow("Contours", drawing);
	//waitKey(1);
	////cout << contours_poly.size() << endl;
//#if (!DEBUG)
//	imshow(windowName, undistorted);
//	waitKey(1);
//#endif

	//if (wnd.keyPressed(81)) {
		//automatic calibration
		centers = clickedPoints;
		char yesno = 'n';
		//if (centers.size() == 3) {
			//cout << "Three points found. Please confirm that the calibration markers are correctly identified (y/n)" << endl;
			//cin >> yesno;
			//if (yesno == 'y')
			//{
				cout << "Calibration markers found" << endl;
				calib_markers_cam = centers;
				topcam_calib_markers_found = true;
				//calibMarkerImg = drawing;
				//destroyWindow("Top Cam View - Grayscale");
				cout << "Centers for Calibration step 2: " << centers << endl;
			//}
		//}

		//if (centers.size() != 3 || yesno == 'n')
		//{
		//	cout << "Try different threshold for finding contours (any number between 1~500ish). Currently " << thresh << "." << endl;
		//	cin >> thresh;
		//}
	//}


}

// get transformation matrix used to undistort the image
void ArenaProc::getTransformationMatrix() {
	transMat = getAffineTransform(Mat(calib_markers_cam), Mat(calib_markers_encoder));
	coordinate_calibrated = true;

	inverseTransMat = getAffineTransform(Mat(calib_markers_encoder), Mat(calib_markers_cam));

	calculateArenaDimensions();

	Mat cameraCoordinates(undistorted.size(), CV_32FC2);
	encoderLocationsByPixel = Mat(undistorted.size(), CV_32FC2);

	for (float y = 0; y < cameraCoordinates.rows; y++)
	{
		for (float x = 0; x < cameraCoordinates.cols; x++)
		{
			Vec2f& coordinates = cameraCoordinates.at<Vec2f>(y, x);
			coordinates[0] = x;
			coordinates[1] = y;
		}
	}
	transform(cameraCoordinates, encoderLocationsByPixel, transMat);

	setOptoZoneViewMat();

	//switch (optoStim.getStimulusType())
	//{
	//case CircleStimulus:
	//	setOptoCircleView();
	//	break;
	//case LineStimulus:
	//	setOptoZoneViewMat();
	//	break;
	//}
}

// old function not being used
void ArenaProc::setOptoCircleView()
{
	const float encoderCenter[2] = { float(optoStim.center[0]), float(optoStim.center[1]) };
	const float distance = optoStim.circleRadius;

	const float encoderXBound1 = encoderCenter[0] - distance;
	const float encoderXBound2 = encoderCenter[0] + distance;
	const float encoderYBound1 = encoderCenter[1] - distance;
	const float encoderYBound2 = encoderCenter[1] + distance;

	const vector<Point2f> encoderBound1{ Point2f(encoderXBound1, encoderYBound1) };
	const vector<Point2f> encoderBound2{ Point2f(encoderXBound2, encoderYBound2) };


	transform(encoderBound1, cameraBound1, inverseTransMat);
	transform(encoderBound2, cameraBound2, inverseTransMat);

	const int cameraCircleRadius = int((cameraBound1[0].x - cameraBound2[0].x)) / 2;
	cameraCircleRadiusSquared = cameraCircleRadius * cameraCircleRadius;
	cameraCircleCenter[0] = int(cameraBound1[0].x + cameraBound2[0].x) / 2;
	cameraCircleCenter[1] = int(cameraBound1[0].y + cameraBound2[0].y) / 2;

	cout << "cameraCircleCenter: (" << cameraCircleCenter[0] << ", " << cameraCircleCenter[1] <<  ")" << endl;
	cout << "cameraBound1: " << cameraBound1 << endl;
	cout << "cameraBound2: " << cameraBound2 << endl;
}


// get dimensions of the arena- currently hard coded rather than using spacers
void ArenaProc::calculateArenaDimensions()
{
	//vector<Point2f> spacer_markers_encoder;

	//transform(spacer_markers_cam, spacer_markers_encoder, transMat);

	//Point2f diameters[3];
	//diameters[0] = spacer_markers_encoder[3] - spacer_markers_encoder[0];
	//diameters[1] = spacer_markers_encoder[4] - spacer_markers_encoder[1];
	//diameters[2] = spacer_markers_encoder[5] - spacer_markers_encoder[2];

	//float diametersLength[3];
	//diametersLength[0] = sqrt(double(diameters[0].x) * double(diameters[0].x) + double(diameters[0].y) * double(diameters[0].y));
	//diametersLength[1] = sqrt(double(diameters[1].x) * double(diameters[1].x) + double(diameters[1].y) * double(diameters[1].y));
	//diametersLength[2] = sqrt(double(diameters[2].x) * double(diameters[2].x) + double(diameters[2].y) * double(diameters[2].y));

	//const float arena_diameter = (diametersLength[0] + diametersLength[1] + diametersLength[2]) / 3;
	//arena_radius = (arena_diameter / 2) - radiusOffset;
	//arena_radius_squared = long long(arena_radius * arena_radius);

	//Point2f encoderCenters[3];
	//encoderCenters[0] = (spacer_markers_encoder[3] + spacer_markers_encoder[0]) / 2;
	//encoderCenters[1] = (spacer_markers_encoder[4] + spacer_markers_encoder[1]) / 2;
	//encoderCenters[2] = (spacer_markers_encoder[5] + spacer_markers_encoder[2]) / 2;

	//spacer_center = (encoderCenters[0] + encoderCenters[1] + encoderCenters[2]) / 3;

	//waitKey(5000);
	//cout << "arena_radius = " << arena_radius / 1000 << " mm" << endl;
	//cout << "spacer_markers_encoder = \n" << spacer_markers_encoder << endl;
	//cout << "spacer_center = " << spacer_center << endl;

	/*constexpr unsigned int xLeft = 85477;
	constexpr unsigned int xRight = 374889;
	constexpr unsigned int yFront = 44843;
	constexpr unsigned int yBack = 328782;

	constexpr unsigned int xCenter = (xLeft + xRight) / 2;
	constexpr unsigned int yCenter = (yFront + yBack) / 2;*/

	//spacer_center_encoder = { float(xCenter), float(yCenter) };



	//arena_radius = float((xRight - xLeft) / 2);
	//arena_radius_squared = arena_radius * arena_radius;
	spacer_center_encoder = { 230003, 189192 };
	arena_radius = 290000 / 2;
	arena_radius_squared = (long long)arena_radius * (long long)arena_radius;
	optoStim.setArenaCenter(spacer_center_encoder.x, spacer_center_encoder.y);
}

// show the optogenetic stimulus area in the top camera view
void ArenaProc::showOptogeneticStimulusArea()
{
	/*for (int y = cameraBound2[0].y; y <= cameraBound1[0].y; y++)
	{
		for (int x = cameraBound2[0].x; x <= cameraBound1[0].x; x++)
		{
			const int xDistance = x - cameraCircleCenter[0];
			const int xDistanceSquared = xDistance * xDistance;
			const int yDistance = y - cameraCircleCenter[1];
			const int yDistanceSquared = yDistance * yDistance;
			const int center2PointSquared = xDistanceSquared + yDistanceSquared;

			if (center2PointSquared <= cameraCircleRadiusSquared)
			{
				Vec3b& color = undistorted.at<Vec3b>(y, x);

				const int redChannelValue = color[2];
				const int cappedRedValue = min(redChannelValue + 50, 255);

				color[2] = cappedRedValue;
			}
		}
	}*/

	add(undistorted, stimulusZoneView, undistorted);

	//if ((encoderX > 81866 && encoderY < 234946) && (encoderX > 81866 && encoderY > 207946) && (encoderX < 361866 && encoderY > 207946) && (encoderX < 361866 && encoderY < 234946))
}

// used to find the fly when top camera fly tracking is working
// currently only being used to show the top camera view on the screen
void ArenaProc::findFlyPos(unsigned long x, unsigned long y) {
	//thresh = 100; // Original thresh = 50; // 100 seemed to be good at identifying a fly in space. 
	//Mat canny_output;
	//static RNG rng(12345);
	//Canny(undistorted, canny_output, thresh, thresh * 2);
	//vector<vector<Point> > contours;
	//findContours(canny_output, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);
	//float radiusFly;
	//float radiusTemp;
	//Point2f centersTemp;
	//vector<Point> countourPloyTemp;

	//topCamFlyFound = false;
	//for (size_t i = 0; i < contours.size(); i++)
	//{
	//	approxPolyDP(contours[i], countourPloyTemp, 3, true);
	//	//boundRect[i] = boundingRect(contours_poly[i]);
	//	minEnclosingCircle(countourPloyTemp, centersTemp, radiusTemp);

	//	// OG = <4 >0
	//	if (radiusTemp < 4 && radiusTemp > 0) { //Here, radius means the size of the object. We are looking for calibration markers. Adjust the range of "radius" if needed. 
	//		//if the point is exisiting beyond the arena markers mark it as NOT inside arena.
	//		float distanceToCenter = norm(Mat(centersTemp), Mat(spacer_center_cam), NORM_L2);
	//		float distanceToLastSeenMin = 1000000;
	//		float distanceToLastSeenTemp;
	//		if (distanceToCenter < 0.98*spacer_radius_cam) {
	//			// 0.98*
	//			distanceToLastSeenTemp = norm(Mat(centersTemp), Mat(bottomCamRecentFlyPos), NORM_L2);

	//			if (distanceToLastSeenTemp < distanceToLastSeenMin) {
	//				distanceToLastSeenMin = distanceToLastSeenTemp;
	//				flyPos_cam = centersTemp;
	//				radiusFly = radiusTemp;
	//				//cout << flyPos_cam << endl; // Added by Sam on 9/30 for testing purposes. 
	//			}

	//			topCamFlyFound = true;
	//		}
	//	}
	//}
	if (optoStim.usingOptogenetics())
	{
		showOptogeneticStimulusArea();
		if (optoStim.getStimulusOnState())
		{
			putText(undistorted, "ON", { 140,140 }, FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 200), 4);
		}
	}
	if (saveDataIndicatorOn)
	{
		putText(undistorted, "SAVING", { undistorted.rows - 140, 140 }, FONT_HERSHEY_SIMPLEX, 1, Scalar(200, 200, 200), 4);
	}

	if (optoStim.isTimerRunning())
	{
		putText(undistorted, optoStim.getTimerString(), { undistorted.rows - 140, undistorted.cols - 140 }, FONT_HERSHEY_SIMPLEX, 1, Scalar(200, 200, 200), 4);
	}


	vector<Point2f> flyEncoderTemp;
	flyEncoderTemp.push_back(Point2f((float)x, (float)y));
	vector<Point2f> flyCamTemp;
	flyCamTemp.push_back(Point2f((float)0.0,(float)0.0));
	transform(flyEncoderTemp, flyCamTemp, inverseTransMat); // transforms flyEncoderTemp into flyCamTemp. hopefully.
	flyPos_cam = flyCamTemp[0];
	//if (true)
	//{
		//putText(undistorted, "*", {(short) floor(x * undistorted.rows / 290000)-140,(short) floor(y * undistorted.rows / 290000) }, FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 200), 1);
	putText(undistorted, ".", { flyPos_cam }, FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 0), 1);
	//short shx = map1.at<short>(x, y);
	//short shy = map2.at<short>(x, y);
	
		//putText(undistorted, "*", {shx,shy}, FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 200), 10);
	//}
#if (!DEBUG)
	imshow(windowName, undistorted);
	waitKey(1);
#endif // RELEASE

	

	//cout << flyPos_encoder << endl;
	//radiusTemp;
	//countourPloyTemp;

	//Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	//Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
	//circle(drawing, flyPos_cam, (int)radiusFly, color, 2);

	//imshow("Contours", drawing);
	//waitKey(1);

	// Can I add a statement that displays something else instead of exiting when an exception occurs?

}

// set encoder position to move the bottom camera to
void ArenaProc::setFlyEncoderPosition()
{
	vector<Point2f> flyEncoderTemp;
	flyEncoderTemp.push_back(Point2f((float)0.0, (float)0.0));
	vector<Point2f> flyCamTemp;
	flyCamTemp.push_back(flyPos_cam);
	transform(flyCamTemp, flyEncoderTemp, transMat); // transforms flyCamTemp into flyEncoderTemp. 
	flyPos_encoder = flyEncoderTemp[0];
	topCamFlyFound = true;
}

// set the matrix for the pixels that will be altered in every frame to show the stimulus zone location
void ArenaProc::setOptoZoneViewMat()
{
	stimulusZoneView = Mat::zeros(undistorted.rows, undistorted.cols, undistorted.type());
	bool isAnyOver0 = false;
	for (int y = 0; y < stimulusZoneView.rows; y++)
	{
		for (int x = 0; x < stimulusZoneView.cols; x++)
		{
			Vec2f& encoderPoint = encoderLocationsByPixel.at<Vec2f>(y, x);

			if (optoStim.isInStimulusZone(encoderPoint[0], encoderPoint[1],true))
			{
				Vec3b& color = stimulusZoneView.at<Vec3b>(y, x);
				color[2] = 50;
				isAnyOver0 = true;
			}
		}
	}
}

// quick fix to deal with if-else statement in main function
void ArenaProc::showTopCamView()
{
	imshow(windowName, undistorted);
	waitKey(1);
}

// used set the stimulus by clicking the top camera
void ArenaProc::setOptoStimParameters(int x, int y)
{
	vector<Point2f> rightClickedPixelVector;
	rightClickedPixelVector.push_back(Point2f(float(x), float(y)));
	vector<Point2f> optoEncoderPosition;
	transform(rightClickedPixelVector, optoEncoderPosition, transMat);

	optoStim.setOptoZone(optoEncoderPosition[0].x, optoEncoderPosition[0].y);
	setOptoZoneViewMat();
	//cameraBound1.clear();
	//cameraBound2.clear();

	//setOptoCircleView();
}

void ArenaProc::convertSpacerCenter() {
	//vector<Point2f> spacerCenterCamTemp;
	//spacerCenterCamTemp.push_back(spacer_center_cam);
	//vector<Point2f> spacerEncoderTemp;
	//spacerEncoderTemp.push_back(Point2f((float)0.0, (float)0.0));
	//transform(spacerCenterCamTemp, spacerEncoderTemp, transMat);
	//spacer_center_encoder = spacerEncoderTemp[0];
	//cout << "spacer_center_encoder = " << spacer_center_encoder << endl;
}

void ArenaProc::setFlyMouseCallbackFunc(ArenaProc* arenaP)
{
	setMouseCallback(windowName, flyMouseCallbackFunc, arenaP);
}

void ArenaProc::calibrationMouseCallbackFunc(int event, int x, int y, int flags, void * userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		vector<Point2f>* mouseClickPtr = reinterpret_cast<vector<Point2f>*>(userdata);
		mouseClickPtr->push_back(Point2f(float(x), float(y)));
	}
}

// set callback function to move camera to clicked position or move stimulus zone to right-clicked position
void ArenaProc::flyMouseCallbackFunc(int event, int x, int y, int flags, void * userdata)
{
	ArenaProc* arenaP = static_cast<ArenaProc*>(userdata);

	if (event == EVENT_LBUTTONDOWN)
	{
		arenaP->flyPos_cam = Point2f(float(x), float(y));
		arenaP->setFlyEncoderPosition();
		//cout << arenaP->flyPos_cam << endl; 

	}

	if (event == EVENT_RBUTTONDOWN)
	{
		arenaP->setOptoStimParameters(x, y);
	}
}
