/**
 *  @file   log.h
 *  @brief  Log interface for printing or logging.
 *  @author Longfei Wang
 *  @date   2026.3
 *
 *  Copyright (c) 2026-now Longfei Wang
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this
 *  software and associated documentation files (the "Software"), to deal in the Software
 *  without restriction, including without limitation the rights to use, copy, modify,
 *  merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 *  permit persons to whom the Software is furnished to do so, subject to the following
 *  conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies
 *  or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 *  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 *  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 *  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 *  OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 **/
#ifndef H_CLF_B48BA4D5_9B80_4BC0_A4E2_BCD07B5E7DDF
#define H_CLF_B48BA4D5_9B80_4BC0_A4E2_BCD07B5E7DDF
#include <cstdint>
#include <string>

namespace clf {
namespace log {

/** Enable the log to file. */
// #define CLF_LOG_TO_FILE

/**
 * @brief The default folder to store the log files.
 */
const std::string DEFAULT_LOG_FOLDER = "clf-log";

/**
 * @brief Log level definition.
 */
enum class Level : uint8_t {
    FATAL,      ///< For fatal error level, identified as [F].
    ERROR,      ///< For error level, identified as [E].
    WARNING,    ///< For warning level, identified as [W].
    DEBUG,      ///< For debug level, identified as [D].
    TRACE       ///< For trace level, identified as [T].
};

/**
 * @brief CLF log interface.
 * 
 * @param level The level of the log.
 * @param file The file to log.
 * @param line The line of the file to log.
 * @param format The log format.
 * @param ... The arguments for the format.
 */
void log(Level level, const char* file, int line, bool tofile, const char* format, ...);

}}  // namespace clf::log

/**
 * @brief The CLF log definition.
 */
#ifdef CLF_LOG_TO_FILE
#define CLF_LOG(LOG_LEVEL, FMT, ...) \
    clf::log::log(LOG_LEVEL, __FILE__, __LINE__, true, FMT, ##__VA_ARGS__)
#else
#define CLF_LOG(LOG_LEVEL, FMT, ...) \
    clf::log::log(LOG_LEVEL, __FILE__, __LINE__, false, FMT, ##__VA_ARGS__)
#endif

/**
 * @brief Commonly used log definition.
 */
#define CLF_LOG_FATAL(FMT, ...)    CLF_LOG(clf::log::Level::FATAL, FMT, ##__VA_ARGS__)
#define CLF_LOG_ERROR(FMT, ...)    CLF_LOG(clf::log::Level::ERROR, FMT, ##__VA_ARGS__)
#define CLF_LOG_WARNING(FMT, ...)  CLF_LOG(clf::log::Level::WARNING, FMT, ##__VA_ARGS__)
#define CLF_LOG_DEBUG(FMT, ...)    CLF_LOG(clf::log::Level::DEBUG, FMT, ##__VA_ARGS__)
#define CLF_LOG_TRACE(FMT, ...)    CLF_LOG(clf::log::Level::TRACE, FMT, ##__VA_ARGS__)

/**
 * @brief Assert definition.
 */
#define CLF_ASSERT(CONDITION, MSG, ...)                                 \
    do {                                                                \
        if (!(CONDITION)) {                                             \
            CLF_LOG_FATAL("Assertion failed: " MSG,  ##__VA_ARGS__);    \
            std::exit(EXIT_FAILURE);                                    \
        }                                                               \
    } while (0)

#endif /* H_CLF_B48BA4D5_9B80_4BC0_A4E2_BCD07B5E7DDF */
