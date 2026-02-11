#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <common/pattern/pattern.hpp>
#include <dlp_platforms/lightcrafter_4500/lcr4500.hpp>

//Queue to hold patterns to be projected, shared between the projection thread and to find where to project thread
std::queue<dlp::Pattern> patternQueue;
// Mutex and condition variable for thread synchronization (Not necessary)
std::mutex queueMutex;
std::condition_variable cv;

void patternLoop(dlp::LCr4500& projector) {
    while (true) {
        std::unique_lock<std::mutex> lock(queueMutex);
        cv.wait(lock, []{ return !patternQueue.empty(); });

        dlp::Pattern pattern = patternQueue.front();
        patternQueue.pop();
        lock.unlock();

        dlp::Pattern::Sequence sequence;
        sequence.Add(pattern);

        projector.StopPatternSequence();
        projector.PreparePatternSequence(sequence);
        projector.StartPatternSequence();
    }
}

//Example of Initialization of the Projector
dlp::LCr4500 projector;
projector.Connect("0");
std::thread loopThread(patternLoop, std::ref(projector));


//To be placed in the thread that finds where to beam to 
{
    FindLocationToBeam;
    //This Pattern is an array of one pattern created based on the location to beam
    //Change to 255 for white pattern, 0 for black pattern
    dlp::Pattern newPattern = CreatePatternBasedOnLocation(FindLocationToBeam);
    // Add the new pattern to the queue
    std::lock_guard<std::mutex> lock(queueMutex);
    patternQueue.push(newPattern);
    // Notify the projection thread
    cv.notify_one();
}