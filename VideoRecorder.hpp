#include <iostream>
#include <gst/gst.h>
#include <unistd.h>

class VideoRecorder{

public:
    VideoRecorder();
    ~VideoRecorder();
    void startRecording();
    void stopRecording();

public:
    GstElement *pipeline;
    GstElement *source;
    GstElement *scale;
    GstElement *convert;
    GstElement *encode;
    GstElement *parse;
    GstElement *mux;
    GstElement *sink;
};




