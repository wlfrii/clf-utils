#ifndef H_WLF_C05FD2D7_2A71_45B0_977A_8A521C5A0D80
#define H_WLF_C05FD2D7_2A71_45B0_977A_8A521C5A0D80
#include <chrono>
#include <ctime>
#include <string>

namespace vision {
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
 * @brief Get the current date string in YYYYmmdd format.
 */
std::string getCurrentDateStr();

/**
 * @brief Get the current time string in YYYYmmdd_HHMM format.
 */
std::string getCurrentMinuteStr();

/**
 * @brief Get the current time string in YYYYmmdd_HHMMSS_CCC format.
 */
std::string getCurrentTimeStr();

}  // namespace mtimer
}  // namespace vision

/**
 * @brief A macro for counting function time comsumption.
 * \param FUNC  The function to be timed
 * \param DURATION  The time duration tolerance
 * \param FMT, ...  The message to be printed if the time comsumption greater
 *                  than the DURATION
 */
#define MMATH_TIMER_COUNT_VOID_FUNC_TIME(FUNC, DURATION, FMT, ...)  \
    do {                                                            \
        auto start = vision::mtimer::getCurrentTimePoint();         \
        FUNC;                                                       \
        float ms = vision::mtimer::durationSince(start);            \
        if (ms > DURATION) {                                        \
            printf("[%.4f ms] elapsed:\t " FMT, ms, ##__VA_ARGS__); \
        }                                                           \
    } while (0)

/**
 * @brief A macro for counting function time comsumption.
 * \param FUNC  The function to be timed
 * \param DURATION  The time duration tolerance
 * \param RET  The returned value from FUNC
 * \param FMT, ...  The message to be printed if the time comsumption greater
 *                  than the DURATION
 */
#define MMATH_TIMER_COUNT_NONVOID_FUNC_TIME(FUNC, DURATION, RET, FMT, ...) \
    do {                                                                   \
        auto start = vision::mtimer::getCurrentTimePoint();                \
        RET        = FUNC;                                                 \
        float ms   = vision::mtimer::durationSince(start);                 \
        if (ms > DURATION) {                                               \
            printf("[%.4f ms] elapsed:\t " FMT, ms, ##__VA_ARGS__);        \
        }                                                                  \
    } while (0)

#endif /* H_WLF_C05FD2D7_2A71_45B0_977A_8A521C5A0D80 */
