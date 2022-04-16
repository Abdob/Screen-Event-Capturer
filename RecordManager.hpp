#include <iostream>
#include "VideoRecorder.hpp"
#include <memory>

class RecordManager{

public:
    RecordManager();
    ~RecordManager();
    void run();
    unsigned int getVideoDuration();

public:
    unsigned int videoDuration;
};