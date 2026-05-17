#include "tiny_logger.h"
#include <sys/stat.h>
#include <unistd.h>
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

void makeDir(const std::string& folder) { 
    if(access(folder.c_str(), 0) == -1){
        mkdir(folder.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); 
    }
}

inline std::string getCurrentTimeStr() {
    time_t timep;
    time(&timep);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y%m%d_%H%M%S", localtime(&timep));

    auto now = std::chrono::system_clock::now();
    uint64_t cms = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()).count() -
            std::chrono::duration_cast<std::chrono::seconds>(
            now.time_since_epoch()).count() * 1000;
    char strms[32];
    sprintf(strms, "_%03ld", cms);

    return std::string(tmp) + strms;
}

// -----------------------------------------------------------------------------------

TinyLogger::TinyLogger(const std::string& log_folder) 
    : _log_folder(log_folder) {
    makeDir(_log_folder);
    _filename = _log_folder + "/" + getCurrentTimeStr() + ".log";

    std::ofstream ofile(_filename, std::ios_base::out | std::ios_base::app);
    if(!ofile.is_open()) {  
        fprintf(stderr, "Cannot open output file\n");
        std::exit(EXIT_FAILURE);
    }
    ofile.close();

    std::thread thread = std::thread(&TinyLogger::write, this);
    thread.detach();
}

TinyLogger* TinyLogger::instance() {
    static TinyLogger instance("tiny_log");
    return &instance;
}

void TinyLogger::log(const char* log_data) {
    std::string log = "[" + getCurrentTimeStr() + "] " + log_data;
    size_t len = strlen(log_data);
    if (len > 0 && log_data[len - 1] != '\n') {
        log += "\n";
    }
    {   
        std::lock_guard<std::mutex> lock(_mutex);
        _log_queue.push(log);
    }
    _cv.notify_one();
}

void TinyLogger::write() {
    while(true) {
        std::unique_lock<std::mutex> lock(_mutex);
        _cv.wait(lock, [this] { return !_log_queue.empty(); });

        std::ofstream ofile(_filename, std::ios_base::out | std::ios_base::app);
        ofile << _log_queue.front();
        _log_queue.pop();
        ofile.close();

        checkFileSize();
    }
}

void TinyLogger::checkFileSize() {
    std::ifstream file(_filename, std::ios::binary);
    file.seekg(0, std::ios::end);
    std::streamoff size = file.tellg(); // Bytes
    if(size > 1024*1024*10) { // limit to 10 MB
        _filename = _log_folder + "/" + getCurrentTimeStr() + ".log";        
    }
}