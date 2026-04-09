#include <algorithm>
#include <iostream>
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

constexpr unsigned int kPatternColumns = 912;
constexpr unsigned int kPatternRows = 1140;
constexpr unsigned int kDisplayedSquareSize = 100;
constexpr unsigned int kDisplayedCellSize = 5;

// Start with one arbitrary target cell inside the existing grid.
constexpr unsigned int kInitialTargetCellColumn = 7;
constexpr unsigned int kInitialTargetCellRow = 12;

// Make the target visible enough to confirm the optical path while still
// keeping every non-target area black.
constexpr unsigned int kMinimumSpotWidthPixels = 3;
constexpr unsigned int kMinimumSpotHeightPixels = 6;
constexpr unsigned int kLargeSpotWidthPixels = 40;
constexpr unsigned int kLargeSpotHeightPixels = 80;

// For video-mode targeting, the projector can be left under TI GUI control and
// this app only needs to render the fullscreen target window. Set to true only
// if you want this program to also own the USB HID projector configuration.
constexpr bool kUseUsbProjectorControl = false;

enum class ProjectionMode {
    FullWhite,
    FullBlack,
    LargeTarget,
    SingleTarget
};

struct GridGeometry {
    unsigned int startCol;
    unsigned int startRow;
    unsigned int squareWidth;
    unsigned int squareHeight;
    unsigned int cellSpacingColumns;
    unsigned int cellSpacingRows;
    unsigned int cellColumns;
    unsigned int cellRows;
};

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
    auto* monitorRects = reinterpret_cast<std::vector<RECT>*>(userData);
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
            for (const RECT& rect : monitorRects) {
                const bool containsPrimaryOrigin = (rect.left <= 0 && rect.right > 0 && rect.top <= 0 && rect.bottom > 0);
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

GridGeometry BuildGridGeometry() {
    GridGeometry grid;
    grid.squareWidth = kDisplayedSquareSize;
    grid.squareHeight = std::min(kDisplayedSquareSize * 2U, kPatternRows);
    grid.cellSpacingColumns = kDisplayedCellSize;
    grid.cellSpacingRows = kDisplayedCellSize * 2U;
    grid.startCol = (kPatternColumns > grid.squareWidth) ? (kPatternColumns - grid.squareWidth) / 2U : 0U;
    grid.startRow = (kPatternRows > grid.squareHeight) ? (kPatternRows - grid.squareHeight) / 2U : 0U;
    grid.cellColumns = std::max(1U, grid.squareWidth / grid.cellSpacingColumns);
    grid.cellRows = std::max(1U, grid.squareHeight / grid.cellSpacingRows);
    return grid;
}

dlp::ReturnCode ConfigureProjectorForVideoMode(dlp::LCr4500& projector) {
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

const char* ProjectionModeName(const ProjectionMode mode) {
    switch (mode) {
    case ProjectionMode::FullWhite:
        return "full white";
    case ProjectionMode::FullBlack:
        return "full black";
    case ProjectionMode::LargeTarget:
        return "large bright block";
    case ProjectionMode::SingleTarget:
        return "single target";
    default:
        return "unknown";
    }
}

dlp::ReturnCode BuildProjectionFrame(const GridGeometry& grid,
                                     const ProjectionMode projectionMode,
                                     unsigned int targetCellColumn,
                                     unsigned int targetCellRow,
                                     bool blankOutput,
                                     dlp::Image* outputImage,
                                     unsigned int* targetColumn,
                                     unsigned int* targetRow) {
    dlp::ReturnCode ret;

    if (!outputImage || !targetColumn || !targetRow) {
        return ret.AddError(IMAGE_NULL_POINTER_ARGUMENT_DATA);
    }

    const unsigned int clampedCellColumn = std::min(targetCellColumn, grid.cellColumns - 1U);
    const unsigned int clampedCellRow = std::min(targetCellRow, grid.cellRows - 1U);

    *targetColumn = grid.startCol + (clampedCellColumn * grid.cellSpacingColumns) + (grid.cellSpacingColumns / 2U);
    *targetRow = grid.startRow + (clampedCellRow * grid.cellSpacingRows) + (grid.cellSpacingRows / 2U);

    cv::Mat frame(static_cast<int>(kPatternRows), static_cast<int>(kPatternColumns), CV_8UC3, cv::Scalar(0, 0, 0));

    if (blankOutput) {
        return outputImage->Create(frame);
    }

    if (projectionMode == ProjectionMode::FullWhite) {
        frame.setTo(cv::Scalar(255, 255, 255));
        return outputImage->Create(frame);
    }

    if (projectionMode == ProjectionMode::FullBlack) {
        return outputImage->Create(frame);
    }

    unsigned int spotWidthPixels = 0;
    unsigned int spotHeightPixels = 0;

    if (projectionMode == ProjectionMode::LargeTarget) {
        spotWidthPixels = std::max(kLargeSpotWidthPixels, grid.cellSpacingColumns * 6U);
        spotHeightPixels = std::max(kLargeSpotHeightPixels, grid.cellSpacingRows * 6U);
    } else {
        spotWidthPixels = std::max(kMinimumSpotWidthPixels, grid.cellSpacingColumns > 2U ? grid.cellSpacingColumns - 2U : 1U);
        spotHeightPixels = std::max(kMinimumSpotHeightPixels, grid.cellSpacingRows > 2U ? grid.cellSpacingRows - 2U : 1U);
    }

    const int spotStartColumn = std::max(0, static_cast<int>(*targetColumn) - static_cast<int>(spotWidthPixels / 2U));
    const int spotStartRow = std::max(0, static_cast<int>(*targetRow) - static_cast<int>(spotHeightPixels / 2U));
    const int spotWidth = std::min(static_cast<int>(spotWidthPixels), static_cast<int>(kPatternColumns) - spotStartColumn);
    const int spotHeight = std::min(static_cast<int>(spotHeightPixels), static_cast<int>(kPatternRows) - spotStartRow);

    cv::rectangle(
        frame,
        cv::Rect(spotStartColumn, spotStartRow, std::max(1, spotWidth), std::max(1, spotHeight)),
        cv::Scalar(255, 255, 255),
        cv::FILLED);

    return outputImage->Create(frame);
}

void PrintControls() {
    std::cout << "Controls:" << std::endl;
    std::cout << "  1       : full white test" << std::endl;
    std::cout << "  2       : full black test" << std::endl;
    std::cout << "  3       : large bright block (easy visibility check)" << std::endl;
    std::cout << "  4       : precise single target" << std::endl;
    std::cout << "  W/A/S/D : move the target cell for modes 3 and 4" << std::endl;
    std::cout << "  B       : blank/unblank the output" << std::endl;
    std::cout << "  P       : save the current frame preview" << std::endl;
    std::cout << "  H       : print controls again" << std::endl;
    std::cout << "  Q or ESC: quit" << std::endl;
    std::cout << "Recommended test order: press 1, then 2, then 3, and finally 4." << std::endl;
}

}  // namespace

int main() {
    std::cout << "Starting video-mode single-target projector test..." << std::endl;

    dlp::LCr4500 projector;
    bool projectorControlAvailable = false;
    dlp::ReturnCode ret;

    if (kUseUsbProjectorControl) {
        ret = projector.Connect("0");
        if (ret.hasErrors()) {
            std::cerr << "Warning: USB control connection to the LCr4500 failed: "
                      << ret.ToString() << std::endl;
            std::cerr << "Continuing in video-only mode. If the TI LightCrafter GUI is open, it may already be using the USB HID connection." << std::endl;
            std::cerr << "Leave the GUI configured for Video Mode + LVDS/FPDLink while this program runs, or close the GUI and rerun if you want the code to own USB control." << std::endl;
        } else {
            projectorControlAvailable = true;
            std::cout << "Connected to projector successfully over USB control." << std::endl;

            ret = projector.StopPatternSequence();
            if (ret.hasErrors()) {
                std::cout << "Pattern stop returned: " << ret.ToString()
                          << " (continuing while switching into video mode)." << std::endl;
            }

            ret = ConfigureProjectorForVideoMode(projector);
            if (ret.hasErrors()) {
                std::cerr << "Warning: Failed to switch projector into video mode over USB: "
                          << ret.ToString() << std::endl;
                std::cerr << "Continuing anyway; make sure the TI GUI is already set to Video Mode + LVDS/FPDLink." << std::endl;
            }
        }
    } else {
        std::cout << "USB control is intentionally disabled for this video-mode test." << std::endl;
        std::cout << "Use the TI LightCrafter GUI to keep the projector in Video Mode + LVDS/FPDLink, then let this app only render the target window." << std::endl;
    }

    const GridGeometry grid = BuildGridGeometry();
    unsigned int targetCellColumn = std::min(kInitialTargetCellColumn, grid.cellColumns - 1U);
    unsigned int targetCellRow = std::min(kInitialTargetCellRow, grid.cellRows - 1U);
    bool blankOutput = false;
    ProjectionMode projectionMode = ProjectionMode::LargeTarget;

    dlp::Image targetFrame;
    unsigned int targetColumn = 0;
    unsigned int targetRowValue = 0;

    ret = BuildProjectionFrame(grid, projectionMode, targetCellColumn, targetCellRow, blankOutput, &targetFrame, &targetColumn, &targetRowValue);
    if (ret.hasErrors()) {
        std::cerr << "Failed to build target frame: " << ret.ToString() << std::endl;
        if (projectorControlAvailable) {
            projector.Disconnect();
        }
        return 1;
    }

    ret = targetFrame.Save("video_mode_target_preview.png");
    std::cout << "Preview save: " << ret.ToString() << std::endl;
    std::cout << "Grid size: " << grid.cellColumns << "x" << grid.cellRows << std::endl;
    std::cout << "Initial target cell: (col=" << targetCellColumn << ", row=" << targetCellRow << ")" << std::endl;
    std::cout << "Approximate DMD target pixel: (x=" << targetColumn << ", y=" << targetRowValue << ")" << std::endl;
    std::cout << "Startup mode: " << ProjectionModeName(projectionMode) << std::endl;
    std::cout << "Use the numbered keys to switch between easy verification views." << std::endl;

    cv::Mat frameToDisplay;
    ret = targetFrame.GetOpenCVData(&frameToDisplay);
    if (ret.hasErrors()) {
        std::cerr << "Failed to extract OpenCV frame: " << ret.ToString() << std::endl;
        if (projectorControlAvailable) {
            projector.Disconnect();
        }
        return 1;
    }

    const std::string windowName = "LCr4500 Video Target";
    const DisplayPlacement displayPlacement = GetProjectorDisplayPlacement();

    cv::namedWindow(windowName, cv::WINDOW_NORMAL);
    if (displayPlacement.width > 0 && displayPlacement.height > 0) {
        cv::resizeWindow(windowName, displayPlacement.width, displayPlacement.height);
    }
    cv::moveWindow(windowName, displayPlacement.x, displayPlacement.y);
    cv::imshow(windowName, frameToDisplay);
    cv::setWindowProperty(windowName, cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
    cv::waitKey(1);

    std::cout << "Video target window is ready." << std::endl;
    std::cout << "Detected " << displayPlacement.displayCount << " display(s)." << std::endl;
    if (displayPlacement.usingSecondaryDisplay) {
        std::cout << "The fullscreen target window was moved to the secondary display at origin ("
                  << displayPlacement.x << ", " << displayPlacement.y << ")." << std::endl;
    } else {
        std::cout << "Only one display was detected, so the window stayed on the primary screen." << std::endl;
        std::cout << "If the projector is connected as an extended display, drag or move this fullscreen window onto it." << std::endl;
    }
    if (!projectorControlAvailable) {
        std::cout << "Running without USB control. This is fine for video-mode display as long as the TI GUI remains set correctly." << std::endl;
    }
    PrintControls();

    bool running = true;
    while (running) {
        const int key = cv::waitKey(0);
        bool refreshFrame = false;

        switch (key) {
        case '1':
            projectionMode = ProjectionMode::FullWhite;
            blankOutput = false;
            refreshFrame = true;
            break;
        case '2':
            projectionMode = ProjectionMode::FullBlack;
            blankOutput = false;
            refreshFrame = true;
            break;
        case '3':
            projectionMode = ProjectionMode::LargeTarget;
            blankOutput = false;
            refreshFrame = true;
            break;
        case '4':
            projectionMode = ProjectionMode::SingleTarget;
            blankOutput = false;
            refreshFrame = true;
            break;
        case 'a':
        case 'A':
            if (targetCellColumn > 0U) {
                --targetCellColumn;
                refreshFrame = true;
            }
            break;
        case 'd':
        case 'D':
            if ((targetCellColumn + 1U) < grid.cellColumns) {
                ++targetCellColumn;
                refreshFrame = true;
            }
            break;
        case 'w':
        case 'W':
            if (targetCellRow > 0U) {
                --targetCellRow;
                refreshFrame = true;
            }
            break;
        case 's':
        case 'S':
            if ((targetCellRow + 1U) < grid.cellRows) {
                ++targetCellRow;
                refreshFrame = true;
            }
            break;
        case 'b':
        case 'B':
            blankOutput = !blankOutput;
            refreshFrame = true;
            break;
        case 'h':
        case 'H':
            PrintControls();
            break;
        case 'p':
        case 'P':
            ret = targetFrame.Save("video_mode_target_preview.png");
            std::cout << "Saved current preview: " << ret.ToString() << std::endl;
            break;
        case 'q':
        case 'Q':
        case 27:
            running = false;
            break;
        default:
            break;
        }

        if (!running) {
            break;
        }

        if (refreshFrame) {
            ret = BuildProjectionFrame(grid, projectionMode, targetCellColumn, targetCellRow, blankOutput, &targetFrame, &targetColumn, &targetRowValue);
            if (ret.hasErrors()) {
                std::cerr << "Failed to refresh target frame: " << ret.ToString() << std::endl;
                break;
            }

            ret = targetFrame.GetOpenCVData(&frameToDisplay);
            if (ret.hasErrors()) {
                std::cerr << "Failed to update OpenCV frame: " << ret.ToString() << std::endl;
                break;
            }

            cv::imshow(windowName, frameToDisplay);
            cv::waitKey(1);

            if (blankOutput) {
                std::cout << "Output blanked." << std::endl;
            } else {
                std::cout << "Mode: " << ProjectionModeName(projectionMode);
                if (projectionMode == ProjectionMode::LargeTarget || projectionMode == ProjectionMode::SingleTarget) {
                    std::cout << " | target cell (col=" << targetCellColumn << ", row=" << targetCellRow
                              << ") | approx DMD pixel (x=" << targetColumn << ", y=" << targetRowValue << ")";
                }
                std::cout << std::endl;
            }
        }
    }

    cv::destroyWindow(windowName);

    if (projectorControlAvailable) {
        ret = projector.Disconnect();
        if (ret.hasErrors()) {
            std::cerr << "Warning: Failed to disconnect projector cleanly: " << ret.ToString() << std::endl;
            return 1;
        }

        std::cout << "Projector disconnected. Exiting." << std::endl;
    } else {
        std::cout << "Exiting video-only mode." << std::endl;
    }

    return 0;
}
