#include "RecordManager.hpp"

RecordManager::RecordManager(unsigned short vn) : videoNumber(vn) {
    std::cout << "Record Manager: construtor called" << std::endl;
    std::cout << "Record Manager: starting with video " << vn << std::endl;
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

bool RecordManager::eventOccured(){
    return false;
}

void RecordManager::run() {

    std::cout << "RecordManager: Welcome to the Screen Recording App" << std::endl;
    // get duration from user
    videoDuration = getVideoDuration();

    std::unique_ptr<VideoRecorder> scopedSession(new VideoRecorder(videoNumber++));
    scopedSession->startRecording();
    sleep(videoDuration/2);
    while(true){
        std::unique_ptr<VideoRecorder> session(new VideoRecorder(videoNumber++));
        session->startRecording();
        sleep(videoDuration/4);
        // event hasn't occured stop recording before leaving scope
        scopedSession->stopRecording();
        // transfer scope to new session
	    scopedSession = std::move(session); 
        sleep(videoDuration/4);
    }
    sleep(videoDuration/2);
    scopedSession->stopRecording();
    scopedSession->setSaveFile();
};