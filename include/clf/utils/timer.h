/**
 *  @file   timer.h
 *  @brief  Commonly used function interfaces such as timing and timestamp printing.
 *  @author Longfei Wang
 *  @date   2019.12
 *
 *  Copyright (c) 2024-now Longfei Wang
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
#ifndef H_CLF_CA0705D0_992B_4D1A_99DF_D3310FDFF827
#define H_CLF_CA0705D0_992B_4D1A_99DF_D3310FDFF827
#include <chrono>
#include <ctime>
#include <string>
#include <vector>

namespace clf {
namespace timer {

/** Timepoint and clock for latency test */
using SteadyClock     = std::chrono::steady_clock;
using SystemClock     = std::chrono::system_clock;
using SteadyTimePoint = std::chrono::steady_clock::time_point;
using SystemTimePoint = std::chrono::system_clock::time_point;

using Microseconds = std::chrono::microseconds;
using Milliseconds = std::chrono::milliseconds;

/**
 * @brief Return current time point.
 *
 * @note Class std::chrono::steady_clock represents a monotonic clock. The time
 * points of this clock cannot decrease as physical time moves forward and the
 * time between ticks of this clock is constant. This clock is not related to
 * wall clock time (for example, it can be time since last reboot), and is most
 * suitable for measuring intervals.
 */
SteadyTimePoint getCurrentTimePoint();

/**
 * @brief Return the duration between the start time and stop time.
 *
 * @param time_start The start time point.
 * @param time_end The stop time point.
 *
 * @return float The duration in milliseconds.
 */
float durationBetween(const SteadyTimePoint& t_start, const SteadyTimePoint& t_end);

/**
 * @brief Return the duration between the start time and stop time.
 *
 * @param time_start The start time point.
 * @param time_end The stop time point.
 *
 * @return float The duration in milliseconds.
 */
float durationBetween(const SystemTimePoint& t_start, const SystemTimePoint& t_end);

/**
 * @brief Get the duration since the start time point, in milliseconds.
 *
 * @remark This is an overloaded function, provided for convenience. It differs
 * from the other functions only in what argument(s) it accepts.
 *
 * @param [in] start_time_point The start time point returned by
 * 						        mmath::timer::getCurrentTimePoint().
 *
 * @return The time duration represented by std::chrono::milliseconds
 *
 * @see vision::mtimer::getCurrentTimePoint().
 */
float durationSince(const SteadyTimePoint& start_time_point);

/**
 * @brief Get the duration since the start time point, in milliseconds.
 *
 * @remark This is an overloaded function, provided for convenience. It differs
 * from the other functions only in what argument(s) it accepts.
 *
 * @param [in] start_time_point The start time point returned by
 * 						        mmath::timer::getCurrentTimePoint().
 *
 * @return The time duration represented by std::chrono::milliseconds
 *
 * @see vision::mtimer::getCurrentTimePoint().
 */
float durationSince(const SystemTimePoint& start_time_point);

/**
 * @brief Definition of commonly used time string format.
 */
enum Format {
    YYYYmmdd,                   ///< Such as 20260516
    YYYY_mm_dd,                 ///< Such as 2026-05-16
    YYYYmmdd_HHMM,              ///< Such as 20260516_1218
    YYYYmmdd_HHMMSS,            ///< Such as 20260516_121856
    YYYYmmdd_HHMMSS_CCC,        ///< Such as 20260516_121856_698
    YYYY_mm_dd_HH_MM_SS,        ///< Such as 2026-05-16-12-18-56
    HHMMSS,                     ///< Such as 121856
    HHMMSS_CCC,                 ///< Such as 121856_698
    HH_MM_SS_CCC                ///< Such as 12:18:56.698
};

/**
 * @brief Return current time string.
 *
 * @param format The specified format.
 * @return std::string
 */
std::string currentTimeStr(Format format);

}  // namespace timer
}  // namespace clf

/**
 * @brief A macro for counting function time comsumption.
 * @param FUNC  The function to be timed
 * @param ITERATIONS  The iteration times.
 * @param MSG, ...  The message to be printed if the time comsumption greater
 *                  than the DURATION
 */
#define CLF_TIMER_ITER_COUNT_VOID_FUNC_TIME(FUNC, ITERATIONS, MSG, ...)     \
    do {                                                                    \
        auto t_start = clf::timer::getCurrentTimePoint();                   \
        float total_ms = 0, min_ms = 1e10f, max_ms = -1;                    \
        for(uint16_t i = 0; i < ITERATIONS; i++) {                          \
            t_start = clf::timer::getCurrentTimePoint();                    \
            FUNC;                                                           \
            float ms = clf::timer::durationSince(t_start);                  \
            total_ms += ms;                                                 \
            if(ms < min_ms) min_ms = ms;                                    \
            else if(ms > max_ms) max_ms = ms;                               \
        }                                                                   \
        float mean_ms = total_ms / static_cast<float>(ITERATIONS);          \
        CLF_LOG_DEBUG(MSG "\n  Iteration [%d] times, average runtime=[%.4f]"\
                      "ms, ranged in [%.4f, %.4f]", ITERATIONS,             \
                      mean_ms, min_ms, max_ms, ##__VA_ARGS__);              \
    } while (0)

#endif /* H_CLF_CA0705D0_992B_4D1A_99DF_D3310FDFF827 */
