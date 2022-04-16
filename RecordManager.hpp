#include <iostream>
#include "VideoRecorder.hpp"
#include <memory>
#include <thread>

class RecordManager{

public:
    RecordManager(unsigned short vn);
    ~RecordManager();
    void run();
    unsigned int getVideoDuration();

public:
    unsigned int videoDuration;
    unsigned short videoNumber;
};