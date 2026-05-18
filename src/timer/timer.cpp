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
#include <iomanip>
#include <sstream>

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

std::string currentTimeStr(Format format) {
    auto now = std::chrono::system_clock::now();
    time_t t = std::chrono::system_clock::to_time_t(now);
    tm local_tm = *std::localtime(&t);

    auto ms = std::chrono::duration_cast<Milliseconds>(now.time_since_epoch()) % 1000;

    std::ostringstream oss;

    switch (format) {
        case Format::YYYYmmdd:
            oss << std::put_time(&local_tm, "%Y%m%d");
            break;
        case Format::YYYY_mm_dd:
            oss << std::put_time(&local_tm, "%Y-%m-%d");
            break;
        case Format::YYYYmmdd_HHMM:
            oss << std::put_time(&local_tm, "%Y%m%d_%H%M");
            break;
        case Format::YYYYmmdd_HHMMSS:
            oss << std::put_time(&local_tm, "%Y%m%d_%H%M%S");
            break;
        case Format::YYYYmmdd_HHMMSS_CCC:
            oss << std::put_time(&local_tm, "%Y%m%d_%H%M%S")
                << "_" << std::setw(3) << std::setfill('0') << ms.count();
            break;
        case Format::YYYY_mm_dd_HH_MM_SS:
            oss << std::put_time(&local_tm, "%Y-%m-%d-%H-%M-%S");
            break;
        case Format::HHMMSS:
            oss << std::put_time(&local_tm, "%H%M%S");
            break;
        case Format::HHMMSS_CCC:
            oss << std::put_time(&local_tm, "%H%M%S")
                << std::setw(3) << std::setfill('0') << ms.count();
            break;
        case Format::HH_MM_SS_CCC:
            oss << std::put_time(&local_tm, "%H:%M:%S")
                << "." << std::setw(3) << std::setfill('0') << ms.count();
            break;
    }

    return oss.str();
}

}  // namespace timer
}  // namespace clf
