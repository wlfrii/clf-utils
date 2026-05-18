#define CLF_LOG_TO_FILE
#include <clf/utils/log.h>
#include <clf/utils/timer.h>
#include <thread>

void testWriteLogThread(int id) {
    int count = 0;
    while(true) {
        ++count;
        CLF_LOG_DEBUG("Thread %d writes %d times log information.", id, count);
        std::this_thread::sleep_for(std::chrono::milliseconds(4));
    }
}

int main(int argc, char* argv[]) {
    // Test timer string function.
    printf("Time str: %s\n", clf::timer::currentTimeStr(clf::timer::Format::YYYYmmdd).c_str());
    printf("Time str: %s\n", clf::timer::currentTimeStr(clf::timer::Format::YYYY_mm_dd).c_str());
    printf("Time str: %s\n", clf::timer::currentTimeStr(clf::timer::Format::YYYYmmdd_HHMM).c_str());
    printf("Time str: %s\n", clf::timer::currentTimeStr(clf::timer::Format::YYYYmmdd_HHMMSS).c_str());
    printf("Time str: %s\n", clf::timer::currentTimeStr(clf::timer::Format::YYYYmmdd_HHMMSS_CCC).c_str());
    printf("Time str: %s\n", clf::timer::currentTimeStr(clf::timer::Format::YYYY_mm_dd_HH_MM_SS).c_str());
    printf("Time str: %s\n", clf::timer::currentTimeStr(clf::timer::Format::HHMMSS).c_str());
    printf("Time str: %s\n", clf::timer::currentTimeStr(clf::timer::Format::HHMMSS_CCC).c_str());
    printf("Time str: %s\n", clf::timer::currentTimeStr(clf::timer::Format::HH_MM_SS_CCC).c_str());

    // Test basic log function.
    CLF_LOG_FATAL("This is a fatal error.");
    CLF_LOG_ERROR("This is a error.");
    CLF_LOG_WARNING("This is a warning.");
    CLF_LOG_DEBUG("This is a debug.");
    CLF_LOG_TRACE("This is a trace.");


    // Test multi-thread.
    std::thread thread1 = std::thread(&testWriteLogThread, 1);
    thread1.detach();

    std::thread thread2 = std::thread(&testWriteLogThread, 2);
    thread2.detach();

    int count = 0;
    while(++count < 101) {
        CLF_LOG_DEBUG("Main thread writes %d times log information.", count);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }

    return 0;
}
