#include "VideoRecorder.hpp"
#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <mutex>

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
    std::mutex _mtxSecondHalf;
    unsigned int videoDuration;
    unsigned short videoNumber;
};