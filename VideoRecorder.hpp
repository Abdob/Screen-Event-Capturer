#include <iostream>
#include <gst/gst.h>
#include <unistd.h>
#include <string>
#include <iomanip>
#include <sstream>

class VideoRecorder{

public:
    VideoRecorder(unsigned short identifier);
    ~VideoRecorder();
    void startRecording();
    void stopRecording();
    void setSaveFile();

private:
    const unsigned short id;
    std::string strId;
    GstElement *pipeline;
    GstElement *source;
    GstElement *scale;
    GstElement *convert;
    GstElement *encode;
    GstElement *parse;
    GstElement *mux;
    GstElement *sink;
    std::string filename;
    bool saveFile = false;
};




