#include "VideoRecorder.hpp"
#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>

class RecordManager{

public:
    RecordManager(unsigned short vn);
    ~RecordManager();
    void run();

private:
    unsigned int getVideoDuration();
    bool eventOccured();
    void overlappingSegment();
    std::vector<std::thread> threads;
    std::mutex _mtxFirstHalf;
    std::condition_variable _condFirstHalf;
    std::mutex _mtxSecondHalf;
    std::condition_variable _condSecondHalf;
    unsigned int videoDuration;
    unsigned short videoNumber;
    bool firstHalfReady;
    bool secondHalfReady;
};