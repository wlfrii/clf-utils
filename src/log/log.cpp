#include <clf/utils/log.h>
#include <clf/utils/timer.h>
#include <clf/utils/fs.h>
#include "./tinylog.h"
#include "./log_level.h"
#include <cstdarg>
#include <memory>

namespace clf {
namespace log {

static std::shared_ptr<TinyLog> tinylog = nullptr;

// Preallocate buffer cache.
constexpr uint16_t LOG_BUFFER_SIZE = 1024;
constexpr uint16_t LOG_PREFIX_SIZE = 128;

void log(Level level, const char* file, int line, bool tofile, const char* format, ...) {
    thread_local static std::string log_buffer(LOG_BUFFER_SIZE, '\0');
    thread_local static char prefix_buffer[LOG_PREFIX_SIZE];

    // Create prefix
    int prefix_len = snprintf(prefix_buffer, LOG_PREFIX_SIZE,
        "[%s][%c][%s:%d] ", timer::currentTimeStr(timer::Format::HH_MM_SS_CCC).c_str(), 
        logIdentifier(level), fs::getFilename(file).c_str(), line);

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

    if(tofile) {
        if(!tinylog) {
            tinylog = std::make_shared<TinyLog>(DEFAULT_LOG_FOLDER);
        }
        tinylog->log(log_buffer.c_str());
    }    
    else {
        printf("%s\n", log_buffer.c_str());
    }
}

}} // namespace clf::log