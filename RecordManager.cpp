#include "RecordManager.hpp"

RecordManager::RecordManager() {
    std::cout << "Record Manager: construtor called" << std::endl;
};

RecordManager::~RecordManager() {
    std::cout << "RecordManager: destructor called" << std::endl;
};

unsigned int RecordManager::getVideoDuration(){
    unsigned int duration;
    std::cout << "RecordManager: Please enter a target duration in seconds" << std::endl;
    std::cin >> duration;
    // make duration divisible by 4
    if(duration == 0)
	    duration = 4;
    else
	    duration = (duration + 3) / 4 * 4;
    std::cout << "RecordManager: Video duration is set to " << duration << " seconds." << std::endl;
    return duration;
};

void RecordManager::run() {

    std::cout << "RecordManager: Welcome to the Screen Recording App" << std::endl;
    // get duration from user
    videoDuration = getVideoDuration();

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
};