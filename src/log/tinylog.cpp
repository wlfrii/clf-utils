#include "./tinylog.h"
#include <clf/utils/timer.h>
#include <clf/utils/fs.h>
#include <cstdio>

#include <fstream>
#include <iostream>
#include <thread>
#include <utility>

namespace clf {
namespace log {

// -----------------------------------------------------------------------------------

TinyLog::TinyLog(const std::string& log_folder)
    : _log_folder(log_folder) {

    // Create the log folder first.
    if (!fs::createPathIfNotExists(_log_folder)) {
        std::fprintf(stderr, "Cannot create log directory: %s\n", _log_folder.c_str());
        std::exit(EXIT_FAILURE);
    }

    // Open the file handle for write out log data.
    updateFileName();

    std::ofstream ofile(_filename, std::ios_base::out | std::ios_base::app);
    if(!ofile.is_open()) {
        std::fprintf(stderr, "Cannot open output file: %s\n", _filename.c_str());
        std::exit(EXIT_FAILURE);
    }
    ofile.close();

    _worker = std::thread(&TinyLog::write, this);
}

TinyLog::~TinyLog() {
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _stopping = true;
    }
    _cv.notify_all();
    if (_worker.joinable()) {
        _worker.join();
    }
}

void TinyLog::log(const std::string& log_data) {
    {
        std::lock_guard<std::mutex> lock(_mutex);
        if (_stopping) {
            return;
        }
        _log_queue.push(log_data);
    }
    _cv.notify_one();
}

void TinyLog::updateFileName() {
    _filename = _log_folder + "/" + 
        timer::currentTimeStr(timer::Format::YYYY_mm_dd_HH_MM_SS) + ".log";
}

void TinyLog::write() {
    while (true) {
        std::string log_data;
        {
            std::unique_lock<std::mutex> lock(_mutex);
            _cv.wait(lock, [this] { return _stopping || !_log_queue.empty(); });
            if (_log_queue.empty()) {
                if (_stopping) {
                    break;
                }
                continue;
            }
            log_data = std::move(_log_queue.front());
            _log_queue.pop();
        }

        std::ofstream ofile(_filename, std::ios_base::out | std::ios_base::app);
        if (!ofile.is_open()) {
            std::fprintf(stderr, "Cannot open output file: %s\n", _filename.c_str());
            continue;
        }
        ofile << log_data << '\n';

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
