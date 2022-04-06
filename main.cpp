#include "VideoRecorder.hpp"

int main(int arg, char *argv[]) {
  
    // Initialize GStreamer
    gst_init(&arg, &argv);

    VideoRecorder session;
    session.startRecording();
    sleep(10);
    session.stopRecording();

    return 0;
}
