#include <algorithm>
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <common/pattern/pattern.hpp>
#include <dlp_platforms/lightcrafter_4500/lcr4500.hpp>

// Queue to hold patterns to be projected, shared between the projection thread and to find where to project thread
std::queue<dlp::Pattern> patternQueue;
// Mutex and condition variable for thread synchronization (Not necessary)
std::mutex queueMutex;
std::condition_variable patternCV;

// void patternLoop(dlp::LCr4500& projector) {
//     while (true) {
//         std::unique_lock<std::mutex> lock(queueMutex);
//         patternCV.wait(lock, []{ return !patternQueue.empty(); });

//         if (patternQueue.empty()) continue; // Double check after waking up

//         dlp::Pattern pattern = patternQueue.front();
//         patternQueue.pop();
//         lock.unlock();

//         dlp::Pattern::Sequence sequence;
//         sequence.Add(pattern);

//         dlp::ReturnCode ret;
//         ret = projector.StopPatternSequence();
//         if (ret.hasErrors()) {
//             std::cerr << "Failed to stop pattern sequence: " << ret.ToString() << std::endl;
//             continue;
//         }

//         ret = projector.PreparePatternSequence(sequence);
//         if (ret.hasErrors()) {
//             std::cerr << "Failed to prepare pattern sequence: " << ret.ToString() << std::endl;
//             continue;
//         }

//         ret = projector.StartPatternSequence(0, 1, false);  // Start from pattern 0, show 1 pattern, don't repeat
//         if (ret.hasErrors()) {
//             std::cerr << "Failed to start pattern sequence: " << ret.ToString() << std::endl;
//             continue;
//         }
//     }
// }

//To be placed in the thread that finds where to beam to
// {
//     // FindLocationToBeam logic here
//     // This Pattern is an array of one pattern created based on the location to beam
//     // Change to 255 for white pattern, 0 for black pattern
//     dlp::Pattern newPattern = CreatePatternBasedOnLocation(FindLocationToBeam);
//     // Add the new pattern to the queue
//     {
//         std::lock_guard<std::mutex> lock(queueMutex);
//         patternQueue.push(newPattern);
//     }
//     // Notify the projection thread
//     patternCV.notify_one();
// }

int main() {
    std::cout << "Starting one-cell scan sequence projection test..." << std::endl;

    // Connect projector
    dlp::LCr4500 projector;
    dlp::ReturnCode ret = projector.Connect("0");
    if (ret.hasErrors()) {
        std::cerr << "Failed to connect to projector: " << ret.ToString() << std::endl;
        return 1;
    }

    std::cout << "Connected to projector successfully." << std::endl;

    const unsigned int patternColumns = 912;
    const unsigned int patternRows = 1140;

    // The LCr4500 uses a diamond 912x1140 DMD. A raw square can look stretched,
    // so the row dimension is compensated to keep the projected target close to
    // a displayed 100x100 square.
    const unsigned int displayedSquareSize = 100;
    const unsigned int squareWidth = displayedSquareSize;
    const unsigned int squareHeight = std::min(displayedSquareSize * 2U, patternRows);

    // Increase density so more cells fit inside the 100x100 target.
    const unsigned int displayedCellSize = 5;
    const unsigned int gridSpacingColumns = displayedCellSize;
    const unsigned int gridSpacingRows = displayedCellSize * 2U;
    const unsigned int gridLineThickness = 1;

    const unsigned char blackPixel = 0;
    const unsigned char whitePixel = 255;
    const unsigned int startCol = (patternColumns > squareWidth) ? (patternColumns - squareWidth) / 2 : 0;
    const unsigned int startRow = (patternRows > squareHeight) ? (patternRows - squareHeight) / 2 : 0;
    const unsigned int endCol = std::min(startCol + squareWidth, patternColumns);
    const unsigned int endRow = std::min(startRow + squareHeight, patternRows);
    const unsigned int cellColumns = std::max(1U, squareWidth / gridSpacingColumns);
    const unsigned int cellRows = std::max(1U, squareHeight / gridSpacingRows);

    dlp::Pattern::Sequence sequence;

    for (unsigned int cellRow = 0; cellRow < cellRows; ++cellRow) {
        for (unsigned int cellCol = 0; cellCol < cellColumns; ++cellCol) {
            dlp::Image image;
            ret = image.Create(patternColumns, patternRows, dlp::Image::Format::MONO_UCHAR);
            if (ret.hasErrors()) {
                std::cerr << "Failed to create image buffer: " << ret.ToString() << std::endl;
                return 1;
            }

            for (unsigned int row = 0; row < patternRows; ++row) {
                for (unsigned int col = 0; col < patternColumns; ++col) {
                    ret = image.SetPixel(col, row, blackPixel);
                    if (ret.hasErrors()) {
                        std::cerr << "Failed to set black pixel value: " << ret.ToString() << std::endl;
                        return 1;
                    }
                }
            }

            const unsigned int cellStartCol = startCol + (cellCol * gridSpacingColumns) + gridLineThickness;
            const unsigned int cellStartRow = startRow + (cellRow * gridSpacingRows) + gridLineThickness;
            const unsigned int cellEndCol = std::min(startCol + ((cellCol + 1) * gridSpacingColumns), endCol);
            const unsigned int cellEndRow = std::min(startRow + ((cellRow + 1) * gridSpacingRows), endRow);

            for (unsigned int row = cellStartRow; row < cellEndRow; ++row) {
                for (unsigned int col = cellStartCol; col < cellEndCol; ++col) {
                    ret = image.SetPixel(col, row, whitePixel);
                    if (ret.hasErrors()) {
                        std::cerr << "Failed to set white pixel value: " << ret.ToString() << std::endl;
                        return 1;
                    }
                }
            }

            dlp::Pattern pattern;
            pattern.id = static_cast<int>(cellRow * cellColumns + cellCol);
            pattern.bitdepth = dlp::Pattern::Bitdepth::MONO_8BPP;
            pattern.color = dlp::Pattern::Color::WHITE;
            pattern.data_type = dlp::Pattern::DataType::IMAGE_DATA;
            pattern.orientation = dlp::Pattern::Orientation::VERTICAL;
            pattern.image_data = image;

            unsigned long int minExposure = dlp::LCr4500::Pattern::Exposure::MININUM(pattern.bitdepth);
            pattern.exposure = std::max(minExposure, 10000000UL);
            pattern.period = pattern.exposure + 2000;

            ret = sequence.Add(pattern);
            if (ret.hasErrors()) {
                std::cerr << "Failed to add cell pattern to sequence: " << ret.ToString() << std::endl;
                return 1;
            }
        }
    }

    unsigned int pattern_count = sequence.GetCount();
    if (pattern_count == 0) {
        std::cerr << "No cell patterns were generated." << std::endl;
        return 1;
    }

    dlp::Pattern previewPattern;
    ret = sequence.Get(0, &previewPattern);
    if (ret.hasErrors()) {
        std::cerr << "Failed to retrieve preview pattern: " << ret.ToString() << std::endl;
        return 1;
    }

    std::cout << "Generated " << pattern_count << " one-cell patterns from a "
              << cellColumns << "x" << cellRows << " grid." << std::endl;

    std::cout << "Image empty: " << previewPattern.image_data.isEmpty() << std::endl;

    ret = previewPattern.image_data.Save("cell_sequence_preview_0.png");
    std::cout << "Save: " << ret.ToString() << std::endl;
    std::cout << "Displayed target size: " << displayedSquareSize << "x" << displayedSquareSize << std::endl;
    std::cout << "Displayed cell size: " << displayedCellSize << "x" << displayedCellSize << std::endl;
    std::cout << "Raw DMD target size used: " << squareWidth << "x" << squareHeight << std::endl;
    std::cout << "Square bounds: cols " << startCol << "-" << (endCol - 1)
              << ", rows " << startRow << "-" << (endRow - 1) << std::endl;

    // TODO: Revisit to determine how to set params from main
    // dlp::Parameters projectorParams;
    // projectorParams.Set(
    //     dlp::LCr4500::Parameters::DLPC350_Firmware(
    //         "resources/lcr4500/DLPR350PROM_v2.0.0.bin"
    //     )
    // );

    // projectorParams.Set(
    //     dlp::LCr4500::Parameters::DLPC350_FlashParameters(
    //         "resources/lcr4500/DLPC350_FlashDeviceParameters.txt"
    //     )
    // );

    // Project it
    ret = projector.PreparePatternSequence(sequence);
    if (ret.hasErrors()) {
        std::cerr << "Failed to prepare pattern sequence for projection: " << ret.ToString() << std::endl;
        return 1;
    }

    ret = projector.StartPatternSequence(0, pattern_count, true);  // Repeat so the square stays projected until stopped
    if (ret.hasErrors()) {
        std::cerr << "Failed to start pattern sequence projection: " << ret.ToString() << std::endl;
        return 1;
    }
    std::cout << "Running..." << std::endl;    std::cout << "One-cell scan sequence projection started successfully!" << std::endl;
    std::cout << "Check cell_sequence_preview_0.png for the first generated pattern." << std::endl;

    // ===== Safe shutdown =====
    // ret = projector.StopPatternSequence();
    // if (ret.hasErrors()) {
    //     std::cerr << "Warning: Failed to stop pattern sequence: " << ret.ToString() << std::endl;
    // } else {
    //     std::cout << "Pattern sequence stopped successfully." << std::endl;
    // }

    // projector.Disconnect();
    // std::cout << "Projector disconnected. Safe to remove USB." << std::endl;

    return 0;
}
