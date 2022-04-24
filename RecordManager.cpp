#include "RecordManager.hpp"

RecordManager::RecordManager(unsigned short vn) : videoNumber(vn) {
};

RecordManager::~RecordManager() {
    remove("event");
};

unsigned int RecordManager::getVideoDuration(){
    unsigned int duration;
    std::cout << "RecordManager: Please enter a target duration in seconds" << std::endl;
    std::cin >> duration;
    // make shortest duration 3 seconds
    if(duration < 3)
	    duration = 3;
    std::cout << "RecordManager: Video duration is set to " << duration << " seconds." << std::endl;
    // return duration in ms
    return duration*1000;
};

bool RecordManager::eventOccured(){
    /* try to open file to read */
    FILE *file;
    if (file = fopen("event", "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

void RecordManager::overlappingSegment(){

    while(true){
        std::unique_ptr<VideoRecorder> scopedSession = nullptr;
        // first half
        {
            std::unique_lock<std::mutex> lck(_mtxFirstHalf);
            _condFirstHalf.wait(lck, [this] {return firstHalfReady;});
            firstHalfReady = false;
            std::unique_ptr<VideoRecorder> session(new VideoRecorder(videoNumber++));
            session->startRecording();
            std::this_thread::sleep_for(std::chrono::milliseconds(videoDuration / 4));
            if(eventOccured()){
                // event occured on other segment's center half, stop recording new session
                session->stopRecording();
                firstHalfReady = true;
                _condFirstHalf.notify_one();
                break;
            }
            else{
                // event hasn't occured finish recording this half and transfer scope
                std::this_thread::sleep_for(std::chrono::milliseconds(videoDuration / 4));
                scopedSession = std::move(session); 
                firstHalfReady = true;
                _condFirstHalf.notify_one();
            }
        }

        // second half
        {
            std::unique_lock<std::mutex> lck(_mtxSecondHalf);
            _condSecondHalf.wait(lck, [this] {return secondHalfReady;});
            secondHalfReady = false;
            std::this_thread::sleep_for(std::chrono::milliseconds(videoDuration  / 4));
            if(eventOccured()){
                // event occured on this session's center half, finish recording this half and save file
                std::this_thread::sleep_for(std::chrono::milliseconds(videoDuration  / 4));
                scopedSession->setSaveFile();
                scopedSession->stopRecording();
                secondHalfReady = true;
                _condSecondHalf.notify_one();
                break;
            }
            else{
                // event didn't occured on this session's center half, stop recording immediately
                scopedSession->stopRecording();
                secondHalfReady = true;
                _condSecondHalf.notify_one();
            }
        }
    }
}

void RecordManager::run() {

    std::cout << "RecordManager: Welcome to the Screen Recording App" << std::endl;
    // get duration from user
    videoDuration = getVideoDuration();
    firstHalfReady = true;
    secondHalfReady = true;
    threads.emplace_back(std::thread(&RecordManager::overlappingSegment, this));
    threads.emplace_back(std::thread(&RecordManager::overlappingSegment, this));

    // ensure both overlapping session are complete before exiting
    threads[0].join();
    threads[1].join();
};