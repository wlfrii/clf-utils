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

namespace clf {
namespace log {

// #define CLF_LOG_FATAL    SR_LOG_FATAL
// #define CLF_LOG_ERROR    SR_LOG_ERROR
// #define CLF_LOG_WARNING  SR_LOG_WARNING
// #define CLF_LOG_NOTICE   SR_LOG_NOTICE
// #define CLF_LOG_DEBUG    SR_LOG_DEBUG
// #define CLF_LOG_TRACE    SR_LOG_TRACE

// /** Assert */
// #define CLF_ASSERT(condition, msg, ...)                              \
//     do {                                                                \
//         if (!(condition)) {                                             \
//             VISION_LOG_FATAL("Assertion failed: " msg,  ##__VA_ARGS__); \
//             std::exit(EXIT_FAILURE);                                    \
//         }                                                               \
//     } while (0)

// #define SIMU_LOG_FATAL(fmt, ...)   SIMU_LOG(fatal, fmt, ##__VA_ARGS__)
// #define SIMU_LOG_ERROR(fmt, ...)   SIMU_LOG(error, fmt, ##__VA_ARGS__)
// #define SIMU_LOG_WARNING(fmt, ...) SIMU_LOG(warning, fmt, ##__VA_ARGS__)
// #define SIMU_LOG_NOTICE(fmt, ...)  SIMU_LOG(notice, fmt, ##__VA_ARGS__)
// #define SIMU_LOG_DEBUG(fmt, ...)   SIMU_LOG(debug, fmt, ##__VA_ARGS__)
// #define SIMU_LOG_TRACE(fmt, ...)   SIMU_LOG(trace, fmt, ##__VA_ARGS__)

// /**
//  * @brief Initiliaze loger for given module.
//  *
//  * @param module_name The module name.
//  */
// void initModuleLog(const char* module_name = nullptr);

// /**
//  * @brief Change output log level
//  *
//  * @param log_level The spdlog level.
//  */
// void changeVisionLogLevel(U8 log_level);

// /**
//  * @brief Change output log level
//  *
//  * @param log_level The spdlog level.
//  */
// void changeSimulationLogLevel(U8 log_level);

}}  // namespace clf::log
#endif /* H_CLF_B48BA4D5_9B80_4BC0_A4E2_BCD07B5E7DDF */
