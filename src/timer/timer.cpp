/**
 *  @file   timer.cpp
 *  @brief  Commonly used function interfaces such as timing and timestamp printing.
 *  @author Longfei Wang
 *  @date   2019.12
 *
 *  Copyright (c) 2019-now Longfei Wang
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
#include <clf/utils/timer.h>

namespace clf {
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

std::string getCurrentClockStr() {
    time_t timep;
    time(&timep);
    char tmp[ 64 ];
    strftime(tmp, sizeof(tmp), "%H%M%S", localtime(&timep));

    auto     now = SystemClock::now();
    uint64_t cms = std::chrono::duration_cast<Milliseconds>(now.time_since_epoch()).count()
                    - std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count() * 1000;
    char strms[ 32 ];
    sprintf(strms, ":%03ld", cms);

    return std::string(tmp) + strms;
}

}  // namespace timer
}  // namespace clf
