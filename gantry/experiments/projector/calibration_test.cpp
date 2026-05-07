#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <thread>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <common/image/image.hpp>
#include <common/parameters.hpp>
#include <common/returncode.hpp>
#include <dlp_platforms/lightcrafter_4500/lcr4500.hpp>

namespace {

constexpr unsigned int kDmdColumns = 912;
constexpr unsigned int kDmdRows = 1140;
constexpr unsigned int kSpotWidthPixels = 3;
constexpr unsigned int kSpotHeightPixels = 4;

// Keep false when TI GUI already owns USB HID and projector is already in video mode.
constexpr bool kUseUsbProjectorControl = false;

// 3x3 homography matrix for camera -> projector transformation
struct HomographyMatrix {
	double data[3][3];
	bool loaded = false;
};

// Forward declaration
unsigned int ClampUnsigned(unsigned int value, unsigned int maxValue);

// Load camera_to_projector_matrix.csv (3x3 CSV file)
bool LoadHomographyMatrix(const std::string &filepath, HomographyMatrix &H) {
	std::ifstream file(filepath);
	if (!file.is_open()) {
		std::cerr << "Could not open " << filepath << std::endl;
		return false;
	}

	std::string line;
	for (int row = 0; row < 3 && std::getline(file, line); ++row) {
		std::istringstream lineStream(line);
		std::string cell;
		for (int col = 0; col < 3 && std::getline(lineStream, cell, ','); ++col) {
			try {
				H.data[row][col] = std::stod(cell);
			} catch (...) {
				std::cerr << "Parse error at row " << row << ", col " << col << std::endl;
				return false;
			}
		}
	}

	H.loaded = true;
	std::cout << "Loaded homography matrix from " << filepath << std::endl;
	return true;
}

// Try to find and load calibration matrix from common locations
bool TryLoadHomographyMatrix(HomographyMatrix &H) {
	// List of paths to try (relative to current working directory)
	const std::vector<std::string> paths = {
		"camera_to_projector_matrix.csv",
		"../camera_to_projector_matrix.csv",
		"../../camera_to_projector_matrix.csv",
		"../../../cameras/camera_to_projector_matrix.csv",
	};

	for (const auto &path : paths) {
		std::ifstream test(path);
		if (test.good()) {
			test.close();
			std::cout << "Searching for matrix file..." << std::endl;
			return LoadHomographyMatrix(path, H);
		}
	}

	std::cerr << "Could not find camera_to_projector_matrix.csv in any standard location." << std::endl;
	std::cerr << "Searched paths:" << std::endl;
	for (const auto &path : paths) {
		std::cerr << "  - " << path << std::endl;
	}
	return false;
}

// Apply homography: [px_tilde, py_tilde, w_tilde] = H * [cx, cy, 1]^T
// Then normalize: px = px_tilde / w_tilde, py = py_tilde / w_tilde
// Returns (px, py) clamped to [0, kDmdColumns-1] x [0, kDmdRows-1]
bool ApplyHomography(const HomographyMatrix &H, double cx, double cy,
					  unsigned int &out_px, unsigned int &out_py) {
	if (!H.loaded) {
		std::cerr << "Homography matrix not loaded." << std::endl;
		return false;
	}

	double px_tilde = H.data[0][0] * cx + H.data[0][1] * cy + H.data[0][2];
	double py_tilde = H.data[1][0] * cx + H.data[1][1] * cy + H.data[1][2];
	double w_tilde = H.data[2][0] * cx + H.data[2][1] * cy + H.data[2][2];

	if (std::fabs(w_tilde) < 1e-6) {
		std::cerr << "Homography scale factor near zero." << std::endl;
		return false;
	}

	double px = px_tilde / w_tilde;
	double py = py_tilde / w_tilde;

	// Clamp to valid range
	out_px = ClampUnsigned(static_cast<unsigned int>(std::round(px)), kDmdColumns - 1U);
	out_py = ClampUnsigned(static_cast<unsigned int>(std::round(py)), kDmdRows - 1U);

	return true;
}

struct DisplayPlacement {
	int x = 0;
	int y = 0;
	int width = 0;
	int height = 0;
	bool usingSecondaryDisplay = false;
	unsigned int displayCount = 1;
};

#ifdef _WIN32
BOOL CALLBACK CollectMonitorRects(HMONITOR, HDC, LPRECT monitorRect, LPARAM userData) {
	auto *monitorRects = reinterpret_cast<std::vector<RECT> *>(userData);
	monitorRects->push_back(*monitorRect);
	return TRUE;
}
#endif

DisplayPlacement GetProjectorDisplayPlacement() {
	DisplayPlacement placement;

#ifdef _WIN32
	std::vector<RECT> monitorRects;
	EnumDisplayMonitors(nullptr, nullptr, CollectMonitorRects, reinterpret_cast<LPARAM>(&monitorRects));

	if (!monitorRects.empty()) {
		placement.displayCount = static_cast<unsigned int>(monitorRects.size());

		RECT selectedRect = monitorRects.front();
		if (monitorRects.size() > 1U) {
			for (const RECT &rect : monitorRects) {
				const bool containsPrimaryOrigin =
					(rect.left <= 0 && rect.right > 0 && rect.top <= 0 && rect.bottom > 0);
				if (!containsPrimaryOrigin) {
					selectedRect = rect;
					placement.usingSecondaryDisplay = true;
					break;
				}
			}

			if (!placement.usingSecondaryDisplay) {
				selectedRect = monitorRects[1];
				placement.usingSecondaryDisplay = true;
			}
		}

		placement.x = selectedRect.left;
		placement.y = selectedRect.top;
		placement.width = selectedRect.right - selectedRect.left;
		placement.height = selectedRect.bottom - selectedRect.top;
	}
#else
	placement.width = 1280;
	placement.height = 720;
#endif

	return placement;
}

dlp::ReturnCode ConfigureProjectorForVideoMode(dlp::LCr4500 &projector) {
	dlp::Parameters videoParams;
	videoParams.Set(dlp::LCr4500::Parameters::OperatingMode(dlp::LCr4500::OperatingMode::VIDEO));
	videoParams.Set(dlp::LCr4500::Parameters::VideoInputSource(dlp::LCr4500::Video::InputSource::FPD_LINK));
	videoParams.Set(dlp::LCr4500::Parameters::VideoParallelPortWidth(dlp::LCr4500::Video::ParallelPortWidth::BITS_30));
	videoParams.Set(dlp::LCr4500::Parameters::InvertData(dlp::LCr4500::InvertData::NORMAL));
	videoParams.Set(dlp::LCr4500::Parameters::LED_SequenceAutomatic(true));
	videoParams.Set(dlp::LCr4500::Parameters::LED_EnableRed(true));
	videoParams.Set(dlp::LCr4500::Parameters::LED_EnableGreen(true));
	videoParams.Set(dlp::LCr4500::Parameters::LED_EnableBlue(true));
	return projector.Setup(videoParams);
}

dlp::ReturnCode BuildFrame(unsigned int targetX,
						   unsigned int targetY,
						   bool blankOutput,
						   dlp::Image *outputImage) {
	dlp::ReturnCode ret;
	if (!outputImage) {
		return ret.AddError(IMAGE_NULL_POINTER_ARGUMENT_DATA);
	}

	cv::Mat frame(static_cast<int>(kDmdRows), static_cast<int>(kDmdColumns), CV_8UC3, cv::Scalar(0, 0, 0));

	if (blankOutput) {
		return outputImage->Create(frame);
	}

	const int halfW = static_cast<int>(kSpotWidthPixels / 2U);
	const int halfH = static_cast<int>(kSpotHeightPixels / 2U);
	const int startX = std::max(0, static_cast<int>(targetX) - halfW);
	const int startY = std::max(0, static_cast<int>(targetY) - halfH);
	const int width = std::min(static_cast<int>(kSpotWidthPixels), static_cast<int>(kDmdColumns) - startX);
	const int height = std::min(static_cast<int>(kSpotHeightPixels), static_cast<int>(kDmdRows) - startY);

	cv::rectangle(
		frame,
		cv::Rect(startX, startY, std::max(1, width), std::max(1, height)),
		cv::Scalar(255, 255, 255),
		cv::FILLED);

	return outputImage->Create(frame);
}

void PrintHelp() {
	std::cout << "Commands:" << std::endl;
	std::cout << "  x y           Set target pixel in DMD coordinates (0-" << (kDmdColumns - 1U)
			  << ", 0-" << (kDmdRows - 1U) << ")" << std::endl;
	std::cout << "  cam cx cy     Transform from camera coords to DMD and display" << std::endl;
	std::cout << "  sweep [delay_ms]  Iterate through all 800x600 camera points (default delay 50ms)" << std::endl;
	std::cout << "  norm u v      Set target with normalized coords in [0, 1]" << std::endl;
	std::cout << "  blank         Set all-black frame" << std::endl;
	std::cout << "  unblank       Show current white target again" << std::endl;
	std::cout << "  save          Save current frame as calibration_test_preview.png" << std::endl;
	std::cout << "  help          Print this help" << std::endl;
	std::cout << "  quit          Exit" << std::endl;
}

unsigned int ClampUnsigned(unsigned int value, unsigned int maxValue) {
	return std::min(value, maxValue);
}

// Load camera points from CSV and sweep through them
void SweepCameraGrid(const HomographyMatrix &H,
					  cv::Mat &frameMat,
					  dlp::Image &frame,
					  unsigned int &targetX,
					  unsigned int &targetY,
					  const std::string &windowName,
					  unsigned int delayMs) {
	const std::vector<std::string> parentPrefixes = {
		".",
		"..",
		"../..",
		"../../..",
		"../../../..",
		"../../../../..",
		"../../../../../..",
		"../../../../../../..",
	};

	const std::vector<std::string> candidateSuffixes = {
		"camera_points.csv",
		"build/bin/Release/camera_points.csv",
		"DLP-ALC-LIGHTCRAFTER-SDK/build/bin/Release/camera_points.csv",
	};

	std::string filename;
	for (const auto &prefix : parentPrefixes) {
		for (const auto &suffix : candidateSuffixes) {
			const std::string candidate = (prefix == ".") ? suffix : (prefix + "/" + suffix);
			std::ifstream test(candidate);
			if (test.good()) {
				test.close();
				filename = candidate;
				break;
			}
		}
		if (!filename.empty()) {
			break;
		}
	}

	if (filename.empty()) {
		std::cerr << "Could not find camera_points.csv for sweep." << std::endl;
		std::cerr << "Searched prefixes:" << std::endl;
		for (const auto &prefix : parentPrefixes) {
			std::cerr << "  - " << prefix << std::endl;
		}
		return;
	}

	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Could not open " << filename << std::endl;
		return;
	}

	std::cout << "Using camera points file: " << filename << std::endl;

	std::string line;
	std::getline(file, line);  // Skip header

	unsigned int pointCount = 0;
	unsigned int skippedCount = 0;

	std::cout << "Starting camera grid sweep (press Ctrl+C to stop)..." << std::endl;

	while (std::getline(file, line) && cv::getWindowProperty(windowName, cv::WND_PROP_VISIBLE) >= 1) {
		std::istringstream lineStream(line);
		std::string cell;
		double cx = 0.0, cy = 0.0;

		if (std::getline(lineStream, cell, ',')) {
			try {
				cx = std::stod(cell);
			} catch (...) {
				++skippedCount;
				continue;
			}
		}

		if (std::getline(lineStream, cell, ',')) {
			try {
				cy = std::stod(cell);
			} catch (...) {
				++skippedCount;
				continue;
			}
		}

		// Apply homography
		unsigned int px = 0, py = 0;
		if (!ApplyHomography(H, cx, cy, px, py)) {
			++skippedCount;
			continue;
		}

		targetX = px;
		targetY = py;

		// Rebuild and display frame
		dlp::ReturnCode ret = BuildFrame(targetX, targetY, false, &frame);
		if (ret.hasErrors()) {
			std::cerr << "Failed to rebuild frame: " << ret.ToString() << std::endl;
			break;
		}

		ret = frame.GetOpenCVData(&frameMat);
		if (ret.hasErrors()) {
			std::cerr << "Failed to refresh OpenCV frame: " << ret.ToString() << std::endl;
			break;
		}

		cv::imshow(windowName, frameMat);
		cv::waitKey(1);

		++pointCount;
		if (pointCount % 10000 == 0) {
			std::cout << "Processed " << pointCount << " points..." << std::endl;
		}

		// Delay between frames
		std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
	}

	file.close();
	std::cout << "Sweep complete. Processed: " << pointCount << " points, Skipped: " << skippedCount << std::endl;
}

}  // namespace

int main() {
	std::cout << "Starting manual projector coordinate test..." << std::endl;

	// Load homography matrix for camera -> projector transformation
	HomographyMatrix H;
	if (!TryLoadHomographyMatrix(H)) {
		std::cerr << "Warning: Could not load homography matrix. Camera->DMD mapping disabled." << std::endl;
	}

	dlp::LCr4500 projector;
	bool projectorControlAvailable = false;
	dlp::ReturnCode ret;

	if (kUseUsbProjectorControl) {
		ret = projector.Connect("0");
		if (ret.hasErrors()) {
			std::cerr << "Warning: USB control connection failed: " << ret.ToString() << std::endl;
			std::cerr << "Continuing in video-only mode; keep TI GUI configured to Video Mode + LVDS/FPDLink." << std::endl;
		} else {
			projectorControlAvailable = true;
			ret = projector.StopPatternSequence();
			if (ret.hasErrors()) {
				std::cout << "Pattern stop returned: " << ret.ToString() << " (continuing)." << std::endl;
			}

			ret = ConfigureProjectorForVideoMode(projector);
			if (ret.hasErrors()) {
				std::cerr << "Warning: projector video-mode setup failed: " << ret.ToString() << std::endl;
			}
		}
	} else {
		std::cout << "USB control is disabled. Make sure TI GUI is already in Video Mode + LVDS/FPDLink." << std::endl;
	}

	unsigned int targetX = kDmdColumns / 2U;
	unsigned int targetY = kDmdRows / 2U;
	bool blankOutput = false;

	dlp::Image frame;
	ret = BuildFrame(targetX, targetY, blankOutput, &frame);
	if (ret.hasErrors()) {
		std::cerr << "Failed to build initial frame: " << ret.ToString() << std::endl;
		if (projectorControlAvailable) {
			projector.Disconnect();
		}
		return 1;
	}

	cv::Mat frameMat;
	ret = frame.GetOpenCVData(&frameMat);
	if (ret.hasErrors()) {
		std::cerr << "Failed to extract OpenCV frame: " << ret.ToString() << std::endl;
		if (projectorControlAvailable) {
			projector.Disconnect();
		}
		return 1;
	}

	const std::string windowName = "Calibration Manual Pixel Test";
	const DisplayPlacement displayPlacement = GetProjectorDisplayPlacement();

	cv::namedWindow(windowName, cv::WINDOW_NORMAL);
	if (displayPlacement.width > 0 && displayPlacement.height > 0) {
		cv::resizeWindow(windowName, displayPlacement.width, displayPlacement.height);
	}
	cv::moveWindow(windowName, displayPlacement.x, displayPlacement.y);
	cv::imshow(windowName, frameMat);
	cv::setWindowProperty(windowName, cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
	cv::waitKey(1);

	std::cout << "Window ready. Displays detected: " << displayPlacement.displayCount << std::endl;
	std::cout << "Current target: (" << targetX << ", " << targetY << ")" << std::endl;
	PrintHelp();

	std::string line;
	bool running = true;
	while (running) {
		std::cout << "cmd> ";
		if (!std::getline(std::cin, line)) {
			break;
		}

		if (line.empty()) {
			continue;
		}

		std::istringstream iss(line);
		std::string token;
		iss >> token;

		bool refreshFrame = false;

		if (token == "quit" || token == "q" || token == "exit") {
			running = false;
		} else if (token == "help" || token == "h") {
			PrintHelp();
		} else if (token == "blank") {
			blankOutput = true;
			refreshFrame = true;
		} else if (token == "unblank") {
			blankOutput = false;
			refreshFrame = true;
		} else if (token == "save") {
			ret = frame.Save("calibration_test_preview.png");
			std::cout << "Save status: " << ret.ToString() << std::endl;
		} else if (token == "sweep") {
			unsigned int delayMs = 50;  // Default delay 50ms
			if (iss >> delayMs) {
				std::cout << "Using delay: " << delayMs << " ms" << std::endl;
			} else {
				std::cout << "Using default delay: 50 ms" << std::endl;
			}
			SweepCameraGrid(H, frameMat, frame, targetX, targetY, windowName, delayMs);
		} else if (token == "cam") {
			double cx = 0.0;
			double cy = 0.0;
			if (!(iss >> cx >> cy)) {
				std::cout << "Usage: cam cx cy" << std::endl;
			} else {
				unsigned int px = 0;
				unsigned int py = 0;
				if (ApplyHomography(H, cx, cy, px, py)) {
					targetX = px;
					targetY = py;
					blankOutput = false;
					refreshFrame = true;
					std::cout << "Camera (" << cx << ", " << cy << ") -> DMD (" << px << ", " << py << ")" << std::endl;
				} else {
					std::cout << "Homography transform failed." << std::endl;
				}
			}
		} else if (token == "norm") {
			double u = 0.0;
			double v = 0.0;
			if (!(iss >> u >> v)) {
				std::cout << "Usage: norm u v" << std::endl;
			} else {
				u = std::max(0.0, std::min(1.0, u));
				v = std::max(0.0, std::min(1.0, v));
				targetX = ClampUnsigned(static_cast<unsigned int>(u * static_cast<double>(kDmdColumns - 1U)), kDmdColumns - 1U);
				targetY = ClampUnsigned(static_cast<unsigned int>(v * static_cast<double>(kDmdRows - 1U)), kDmdRows - 1U);
				blankOutput = false;
				refreshFrame = true;
			}
		} else {
			std::istringstream pointParser(line);
			int x = -1;
			int y = -1;
			if (pointParser >> x >> y) {
				if (x < 0 || y < 0) {
					std::cout << "Coordinates must be >= 0." << std::endl;
				} else {
					targetX = ClampUnsigned(static_cast<unsigned int>(x), kDmdColumns - 1U);
					targetY = ClampUnsigned(static_cast<unsigned int>(y), kDmdRows - 1U);
					blankOutput = false;
					refreshFrame = true;
				}
			} else {
				std::cout << "Unknown command. Type 'help' for available commands." << std::endl;
			}
		}

		if (refreshFrame) {
			ret = BuildFrame(targetX, targetY, blankOutput, &frame);
			if (ret.hasErrors()) {
				std::cerr << "Failed to rebuild frame: " << ret.ToString() << std::endl;
				break;
			}

			ret = frame.GetOpenCVData(&frameMat);
			if (ret.hasErrors()) {
				std::cerr << "Failed to refresh OpenCV frame: " << ret.ToString() << std::endl;
				break;
			}

			cv::imshow(windowName, frameMat);
			cv::waitKey(1);

			if (blankOutput) {
				std::cout << "Output is black (blank)." << std::endl;
			} else {
				std::cout << "Target updated to DMD pixel (" << targetX << ", " << targetY << ")." << std::endl;
			}
		}

		if (cv::getWindowProperty(windowName, cv::WND_PROP_VISIBLE) < 1) {
			running = false;
		}
	}

	cv::destroyWindow(windowName);

	if (projectorControlAvailable) {
		ret = projector.Disconnect();
		if (ret.hasErrors()) {
			std::cerr << "Warning: projector disconnect failed: " << ret.ToString() << std::endl;
			return 1;
		}
	}

	std::cout << "Exiting calibration manual pixel test." << std::endl;
	return 0;
}
