#include <iostream>
#include "VideoRecorder.hpp"
#include <memory>
#include <thread>
#include <vector>
#include <mutex>

class RecordManager{

public:
    RecordManager(unsigned short vn);
    ~RecordManager();
    void run();
    unsigned int getVideoDuration();
    bool eventOccured();
    std::vector<std::thread> threads;
    std::mutex _mtxFirstHalf;
    std::mutex _mtxSecondHalf;

public:
    unsigned int videoDuration;
    unsigned short videoNumber;
private:
    void overlappingSegment();
};