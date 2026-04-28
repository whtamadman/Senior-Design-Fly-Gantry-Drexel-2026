#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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
constexpr unsigned int kSpotWidthPixels = 7;
constexpr unsigned int kSpotHeightPixels = 7;

// Keep false when TI GUI already owns USB HID and projector is already in video mode.
constexpr bool kUseUsbProjectorControl = false;

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

}  // namespace

int main() {
	std::cout << "Starting manual projector coordinate test..." << std::endl;

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
