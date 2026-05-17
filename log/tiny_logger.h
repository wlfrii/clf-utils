#ifndef H_WLF_F49F4440_4D9E_4EF7_A091_DA5AB205A6DC
#define H_WLF_F49F4440_4D9E_4EF7_A091_DA5AB205A6DC
#include <string>
#include <cstring>
#include <queue>
#include <mutex>
#include <condition_variable>

class TinyLogger {
public:
    TinyLogger(const std::string& log_folder);

    /**
     * @brief Return a default TinyLogger object, with log folder as "tiny_log".
     * 
     * @return TinyLogger* 
     */
    static TinyLogger* instance();

    /**
     * @brief Add log data.
     * 
     * @param log_data 
     */
    void log(const char* log_data);

private:
    void write();
    void checkFileSize();

private:
    std::string _log_folder;
    std::string _filename;
    std::queue<std::string> _log_queue;
    std::mutex  _mutex;
    std::condition_variable _cv;
};

#define TINY_LOG(fmt, ...)                                          \
    do {                                                            \
        const char* fullpath = __FILE__;                            \
        const char* filename = strrchr(fullpath, '/');              \
        filename = (filename != nullptr) ? filename + 1 : fullpath; \
        int size = snprintf(NULL, 0, "[%s][line:%d] " fmt,          \
            filename, __LINE__, ##__VA_ARGS__) + 1;                 \
        char* log_data = (char*)malloc(size);                       \
        snprintf(log_data, size, "[%s][line:%d] " fmt,              \
            filename, __LINE__, ##__VA_ARGS__);                     \
        TinyLogger::instance()->log(log_data);                      \
        free(log_data);                                             \
    } while (0)

#endif /* H_WLF_F49F4440_4D9E_4EF7_A091_DA5AB205A6DC */
