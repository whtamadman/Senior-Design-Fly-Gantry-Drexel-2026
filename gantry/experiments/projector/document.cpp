#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <common/pattern/pattern.hpp>
#include <dlp_platforms/lightcrafter_4500/lcr4500.hpp>
#include <structured_light/grid/grid.hpp>

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
    std::cout << "Starting grid pattern generation test..." << std::endl;

    // Connect projector
    dlp::LCr4500 projector;
    dlp::ReturnCode ret = projector.Connect("0");
    if (ret.hasErrors()) {
        std::cerr << "Failed to connect to projector: " << ret.ToString() << std::endl;
        return 1;
    }

    std::cout << "Connected to projector successfully." << std::endl;

    dlp::Grid grid;
    dlp::Parameters params;

    // Grid params
    params.Set(dlp::Grid::Parameters::GridSpacingRows(20));
    params.Set(dlp::Grid::Parameters::GridSpacingColumns(20));
    params.Set(dlp::Grid::Parameters::LineThickness(1));

    // Structured light params
    params.Set(dlp::StructuredLight::Parameters::PatternRows(1140));
    params.Set(dlp::StructuredLight::Parameters::PatternColumns(912));
    params.Set(dlp::StructuredLight::Parameters::PatternColor(dlp::Pattern::Color::WHITE));
    params.Set(dlp::StructuredLight::Parameters::PatternOrientation(
        dlp::Pattern::Orientation::VERTICAL
    ));

    params.Set("STRUCTURED_LIGHT_SETTINGS_SEQUENCE_COUNT", 1);
    params.Set("STRUCTURED_LIGHT_SETTINGS_SEQUENCE_INCLUDE_INVERTED", false);

    ret = grid.Setup(params);
    if (ret.hasErrors()) {
        std::cerr << "Failed to setup grid pattern generator: " << ret.ToString() << std::endl;
        return 1;
    }
    std::cout << "Grid pattern generator setup successfully." << std::endl;

    dlp::Pattern::Sequence sequence;
    ret = grid.GeneratePatternSequence(&sequence);
    if (ret.hasErrors()) {
        std::cerr << "Failed to generate pattern sequence: " << ret.ToString() << std::endl;
        return 1;
    }

    // Set valid timing for each pattern
    for (unsigned int i = 0; i < sequence.GetCount(); i++) {
        dlp::Pattern p;
        sequence.Get(i, &p);

        // Use correct exposure based on bit depth
        unsigned long int minExposure = dlp::LCr4500::Pattern::Exposure::MININUM(p.bitdepth);
        p.exposure = std::max(minExposure, 10000000UL); // 10 ms or min exposure
        p.period   = p.exposure + 2000; // period slightly longer than exposure

        sequence.Set(i, p);
    }

    unsigned int pattern_count = sequence.GetCount();
    std::cout << "Generated " << pattern_count << " patterns in sequence." << std::endl;

    if (pattern_count == 0) {
        std::cerr << "No patterns generated!" << std::endl;
        return 1;
    }

    // Save first pattern to file to verify it looks right
    dlp::Pattern pattern;
    ret = sequence.Get(0, &pattern);
    std::cout << "Get pattern: " << ret.ToString() << std::endl;

    std::cout << "Image empty: " << pattern.image_data.isEmpty() << std::endl;

    ret = pattern.image_data.Save("grid_test.png");
    std::cout << "Save: " << ret.ToString() << std::endl;

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

    ret = projector.StartPatternSequence(0, pattern_count, false);  // Start from pattern 0, show all patterns, don't repeat
    if (ret.hasErrors()) {
        std::cerr << "Failed to start pattern sequence projection: " << ret.ToString() << std::endl;
        return 1;
    }

    std::cout << "Grid pattern test completed successfully!" << std::endl;
    std::cout << "Check grid_test.png for the generated pattern." << std::endl;

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
