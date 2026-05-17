/****************************************************************************************
**
**                       Copyright (c) SURGERII. All rights reserved
**
*****************************************************************************************
**
**                       Description: vision_timer.cpp
**
** @author longfei.wang@surgerii.com
** @date   2024.
*****************************************************************************************/
#include <vision/common/vision_timer.h>

namespace vision {
namespace timer {

SteadyTimePoint getCurrentTimePoint() { return SteadyClock::now(); }

float durationBetween(const SteadyTimePoint& t_start, const SteadyTimePoint& t_end) {
    auto micro_sec = std::chrono::duration_cast<Microseconds>(t_end - t_start).count();
    return 1.f * micro_sec / 1000.f;
}

float durationBetween(const SystemTimePoint& t_start, const SystemTimePoint& t_end) {
    auto micro_sec = std::chrono::duration_cast<Microseconds>(t_end - t_start).count();
    return 1.f * micro_sec / 1000.f;
}

float durationSince(const SteadyTimePoint& start_time_point) {
    auto now = SteadyClock::now();
    return durationBetween(start_time_point, now);
}

float durationSince(const SystemTimePoint& start_time_point) {
    auto now = SystemClock::now();
    return durationBetween(start_time_point, now);
}

std::string getCurrentDateStr() {
    time_t timep;
    time(&timep);
    char tmp[ 64 ];
    strftime(tmp, sizeof(tmp), "%Y%m%d", localtime(&timep));

    return std::string(tmp);
}

std::string getCurrentMinuteStr() {
    time_t timep;
    time(&timep);
    char tmp[ 64 ];
    strftime(tmp, sizeof(tmp), "%Y%m%d_%H%M", localtime(&timep));

    return std::string(tmp);
}

std::string getCurrentTimeStr() {
    time_t timep;
    time(&timep);
    char tmp[ 64 ];
    strftime(tmp, sizeof(tmp), "%Y%m%d_%H%M%S", localtime(&timep));

    auto     now = SystemClock::now();
    uint64_t cms = std::chrono::duration_cast<Milliseconds>(now.time_since_epoch()).count()
                    - std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count() * 1000;
    char strms[ 32 ];
    sprintf(strms, "_%03ld", cms);

    return std::string(tmp) + strms;
}

}  // namespace mtimer
}  // namespace vision
