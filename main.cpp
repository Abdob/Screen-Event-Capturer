#include "VideoRecorder.hpp"
#include <memory>

int main(int arg, char *argv[]) {
  
    // Initialize GStreamer
    gst_init(&arg, &argv);

    std::unique_ptr<VideoRecorder> session(new VideoRecorder());
    session->startRecording();
    sleep(10);
    session->stopRecording();

    return 0;
}
