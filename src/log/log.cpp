#include <clf/utils/log.h>
#include <clf/utils/timer.h>
#include <clf/utils/fs.h>
#include "./tinylog.h"
#include "./log_level.h"
#include <cstdarg>
#include <cstdio>
#include <vector>

namespace clf {
namespace log {

constexpr std::size_t LOG_PREFIX_SIZE = 256;

TinyLog& fileLogger() {
    // Function-local static initialization is thread-safe since C++11.
    static TinyLog logger(DEFAULT_LOG_FOLDER);
    return logger;
}

void log(Level level, const char* file, int line, bool tofile, const char* format, ...) {
    thread_local char prefix_buffer[LOG_PREFIX_SIZE];

    // Create prefix
    const int prefix_len = std::snprintf(prefix_buffer, LOG_PREFIX_SIZE,
        "[%s][%c][%s:%d] ", timer::currentTimeStr(timer::Format::HH_MM_SS_CCC).c_str(), 
        logIdentifier(level), fs::getFilename(file).c_str(), line);
    const std::string prefix = prefix_len > 0
        ? std::string(prefix_buffer, static_cast<std::size_t>(prefix_len) < LOG_PREFIX_SIZE
            ? static_cast<std::size_t>(prefix_len) : LOG_PREFIX_SIZE - 1)
        : std::string{};

    va_list args;
    va_start(args, format);
    va_list args_copy;
    va_copy(args_copy, args);
    const int content_len = std::vsnprintf(nullptr, 0, format, args_copy);
    va_end(args_copy);

    if (content_len < 0) {
        va_end(args);
        std::fprintf(stderr, "%s<invalid log format>\n", prefix.c_str());
        return;
    }

    std::vector<char> content(static_cast<std::size_t>(content_len) + 1);
    std::vsnprintf(content.data(), content.size(), format, args);
    va_end(args);

    const std::string log_buffer = prefix + content.data();

    if(tofile) {
        fileLogger().log(log_buffer);
    }    
    else {
        std::printf("%s\n", log_buffer.c_str());
    }
}

}} // namespace clf::log
