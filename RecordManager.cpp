#include "RecordManager.hpp"

RecordManager::RecordManager(unsigned short vn) : videoNumber(vn) {
};

RecordManager::~RecordManager() {
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
    /* try to open file to read */
    FILE *file;
    if (file = fopen("event", "r")) {
        fclose(file);
        remove("event");
        return true;
    } else {
        return false;
    }
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
        if(eventOccured()){
            // event occured on old session center, stop recording new session
            session->stopRecording();
            // finish recording last quarter
            sleep(videoDuration/4);
            break;
        }
        else{
            // event hasn't occured, stop recording old session before leaving scope
            scopedSession->stopRecording();
            // transfer scope to new session
	        scopedSession = std::move(session); 
        }
        sleep(videoDuration/4);
        if(eventOccured()){
            // event occured on new session center, finish recording second half
            sleep(videoDuration/2);
            break; 
        }
    }
    scopedSession->stopRecording();
    scopedSession->setSaveFile();
};