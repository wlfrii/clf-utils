#include <clf/utils/inc/tinylog.h>
#include <clf/utils/timer.h>

#include <sys/stat.h>
#include <unistd.h>
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

#include <cstdio>
#include <cstdarg>

namespace clf {
namespace log {

void makeDir(const std::string& folder) {
    if(access(folder.c_str(), 0) == -1){
        mkdir(folder.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }
}

// -----------------------------------------------------------------------------------

// Preallocate buffer cache.
constexpr uint16_t LOG_BUFFER_SIZE = 1024;
constexpr uint16_t LOG_PREFIX_SIZE = 128;

TinyLog::TinyLog(const std::string& log_folder)
    : _log_folder(log_folder) {
    makeDir(_log_folder);
    _filename = _log_folder + "/" + timer::getCurrentTimeStr() + ".log";

    std::ofstream ofile(_filename, std::ios_base::out | std::ios_base::app);
    if(!ofile.is_open()) {
        fprintf(stderr, "Cannot open output file\n");
        std::exit(EXIT_FAILURE);
    }
    ofile.close();

    std::thread thread = std::thread(&TinyLog::write, this);
    thread.detach();
}

TinyLog* TinyLog::instance() {
    static TinyLog instance("tiny_log");
    return &instance;
}

void TinyLog::log(const char* log_data) {
    std::string log = "[" + timer::getCurrentClockStr() + "] " + log_data;
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

void TinyLog::log(const char* file, int line, const char* format, ...) {
    thread_local static std::string log_buffer(LOG_BUFFER_SIZE, '\0');
    thread_local static char prefix_buffer[LOG_PREFIX_SIZE];

    // Create prefix
    int prefix_len = snprintf(prefix_buffer, LOG_PREFIX_SIZE,
        "[%s] [INFO] [%s:%d] ", timer::getCurrentTimeStr().c_str(), file, line);

    if (prefix_len >= 0 && prefix_len < LOG_BUFFER_SIZE) {
        std::copy(prefix_buffer, prefix_buffer + prefix_len, log_buffer.begin());
    }

    // Get the length of the string.
    va_list args;
    va_start(args, format);
    int content_len = vsnprintf(
        log_buffer.data() + prefix_len,
        log_buffer.size() - prefix_len,
        format, args);
    va_end(args);

    // When string length is greater the buffer size.
    if(content_len >= (int)log_buffer.size()) {
        log_buffer.resize(content_len + 1);
        va_start(args, format);
        vsnprintf(log_buffer.data() + prefix_len, log_buffer.size() - prefix_len,
            format, args);
        va_end(args);
    }

    printf("[INFO] %s\n", log_buffer.c_str());
}

void TinyLog::write() {
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

void TinyLog::checkFileSize() {
    std::ifstream file(_filename, std::ios::binary);
    file.seekg(0, std::ios::end);
    std::streamoff size = file.tellg(); // Bytes
    if(size > 1024*1024*10) { // limit to 10 MB
        _filename = _log_folder + "/" + getCurrentTimeStr() + ".log";
    }
}

}} // namespace clf::log