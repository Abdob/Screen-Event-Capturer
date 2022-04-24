#include "RecordManager.hpp"

RecordManager::RecordManager(unsigned short vn) : videoNumber(vn) {
};

RecordManager::~RecordManager() {
};

unsigned int RecordManager::getVideoDuration(){
    unsigned int duration;
    std::cout << "RecordManager: Please enter a target duration in seconds" << std::endl;
    std::cin >> duration;
    // make shortest duration 3 seconds
    if(duration < 3)
	    duration = 3;
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

void RecordManager::overlappingSegment(){
    std::unique_ptr<VideoRecorder> scopedSession(new VideoRecorder(videoNumber++));
    scopedSession->startRecording();
    std::this_thread::sleep_for(std::chrono::milliseconds(videoDuration * 1000 / 2));
    while(true){
    
        std::unique_ptr<VideoRecorder> session(new VideoRecorder(videoNumber++));
        session->startRecording();
        std::this_thread::sleep_for(std::chrono::milliseconds(videoDuration * 1000 / 4));
        if(eventOccured()){
            // event occured on old session's third segment, stop recording new session
            session->stopRecording();
            // finish recording fourth segment
            std::this_thread::sleep_for(std::chrono::milliseconds(videoDuration * 1000 / 4));
            break;
        }
        else{
            // event hasn't occured, stop recording old session before leaving scope
            scopedSession->stopRecording();
            scopedSession->setSaveFile();
            // transfer scope to new session
	        scopedSession = std::move(session); 
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(videoDuration * 1000 / 4));
        if(eventOccured()){
            // event occured on new session's second segment, finish recording second half
            std::this_thread::sleep_for(std::chrono::milliseconds(videoDuration * 1000 / 2));
            break; 
        }
    }
    scopedSession->stopRecording();
    scopedSession->setSaveFile();
}

void RecordManager::run() {

    std::cout << "RecordManager: Welcome to the Screen Recording App" << std::endl;
    // get duration from user
    videoDuration = getVideoDuration();

    threads.emplace_back(std::thread(&RecordManager::overlappingSegment, this));

    std::cout << "threads size: " << threads.size() << std::endl;
    threads[0].join();
};