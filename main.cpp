#include "VideoRecorder.hpp"
#include <memory>

int main(int arg, char *argv[]) {

    // get duration from user
    unsigned int videoDuration;
    std::cout << "Welcome to the Screen Recording App" << std::endl;
    std::cout << "Please enter a duration in seconds" << std::endl;
    std::cin >> videoDuration;
    
    // make duration divisible by 4
    if(videoDuration == 0)
	videoDuration = 4;
    else
	videoDuration = (videoDuration + 3) / 4 * 4;

    std::cout << "Screen Recording App: video duration set to " << videoDuration << " seconds." << std::endl;

    // Initialize GStreamer
    gst_init(&arg, &argv);

    unsigned short i = 1;
    std::unique_ptr<VideoRecorder> scopedSession(new VideoRecorder(i++));
    scopedSession->startRecording();
    sleep(videoDuration/2);
    while(true){
        std::unique_ptr<VideoRecorder> session(new VideoRecorder(i++));
        session->startRecording();
        sleep(videoDuration/4);
        scopedSession->stopRecording();
	scopedSession = std::move(session); 
        sleep(videoDuration/4);
	if(i==6)
	    break;  
    }
    sleep(videoDuration/2);
    scopedSession->stopRecording();
    scopedSession->setSaveFile();
    return 0;
}
