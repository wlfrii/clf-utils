#include "./tinylog.h"
#include <clf/utils/timer.h>
#include <clf/utils/fs.h>
#include <cstdio>

#include <fstream>
#include <iostream>
#include <thread>

namespace clf {
namespace log {

// -----------------------------------------------------------------------------------

TinyLog::TinyLog(const std::string log_folder)
    : _log_folder(log_folder) {

    // Create the log folder first.
    fs::createPathIfNotExists(_log_folder);

    // Open the file handle for write out log data.
    updateFileName();

    std::ofstream ofile(_filename, std::ios_base::out | std::ios_base::app);
    if(!ofile.is_open()) {
        fprintf(stderr, "Cannot open output file\n");
        std::exit(EXIT_FAILURE);
    }
    ofile.close();

    std::thread thread = std::thread(&TinyLog::write, this);
    thread.detach();
}

void TinyLog::log(const char* log_data) {
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _log_queue.push(log_data);
    }
    _cv.notify_one();
}

void TinyLog::updateFileName() {
    _filename = _log_folder + "/" + 
        timer::currentTimeStr(timer::Format::YYYY_mm_dd_HH_MM_SS) + ".log";
}

void TinyLog::write() {
    while(true) {
        std::unique_lock<std::mutex> lock(_mutex);
        _cv.wait(lock, [this] { return !_log_queue.empty(); });

        std::ofstream ofile(_filename, std::ios_base::out | std::ios_base::app);
        ofile << _log_queue.front() << '\n';
        _log_queue.pop();
        ofile.close();

        checkFileSize();
    }
}

void TinyLog::checkFileSize() {
    std::ifstream file(_filename, std::ios::binary);
    file.seekg(0, std::ios::end);
    std::streamoff size = file.tellg(); // Bytes
    if(size > 1024*1024*10) { // limit to 10 MB
        updateFileName();
    }
}

}} // namespace clf::log