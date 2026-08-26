#ifndef H_CLF_C4954FD8_FD0E_49C8_B08A_A795358D4D2E
#define H_CLF_C4954FD8_FD0E_49C8_B08A_A795358D4D2E
#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <clf/utils/log.h>

namespace clf {
namespace log {

class TinyLog {
public:
    /**
     * @brief Construct a new TinyLog object.
     * 
     * @param log_folder The folder to store the log files.
     */
    explicit TinyLog(const std::string& log_folder);

    /** Flush queued messages and stop the writer thread. */
    ~TinyLog();

    TinyLog(const TinyLog&) = delete;
    TinyLog& operator=(const TinyLog&) = delete;
    TinyLog(TinyLog&&) = delete;
    TinyLog& operator=(TinyLog&&) = delete;

    /**
     * @brief CLF log interface.
     * 
     * @param log_data The information to log.
     */
    void log(const std::string& log_data);

private:
    /** Update log file name. */    
    void updateFileName();

    /** Writeout log. */
    void write();

    /** Check log file size. */
    void checkFileSize();

private:
    std::string _log_folder;                ///< The folder to store log.
    std::string _filename;                  ///< Currently log file.
    std::queue<std::string> _log_queue;
    std::mutex  _mutex;
    std::condition_variable _cv;
    std::thread _worker;
    bool _stopping = false;
};

}} // namespace clf::log
#endif /* H_CLF_C4954FD8_FD0E_49C8_B08A_A795358D4D2E */
