#include "./tiny_logger.h"
#include <thread>

void testWriteLogThread(int id) {
    int count = 0;
    while(true) {
        ++count;
        TINY_LOG("Thread %d writes %d times log information.", id, count);
        std::this_thread::sleep_for(std::chrono::milliseconds(4));
    }
}

int main(int argc, char* argv[]) {
    std::thread thread1 = std::thread(&testWriteLogThread, 1);
    thread1.detach();

    std::thread thread2 = std::thread(&testWriteLogThread, 2);
    thread2.detach();

    int count = 0;
    while(++count < 101) {
        TINY_LOG("Main thread writes %d times log information.", count);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }

    return 0;
}
