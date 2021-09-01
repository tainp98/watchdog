#include <iostream>
#include <thread>
#include <chrono>
#include "MultiThreadWatchdog.h"
#include "Class1.h"
#include "Class2.h"

int main() {
    // Initialize with 3sec expire time and max 10 threads.
    Class1 class1;
//    Class2 class2;
    std::cout << "main thread id = " << std::this_thread::get_id() << std::endl;
    // Kick 5 times and stop.
    std::thread t1(&Class1::run, &class1);
//    std::thread t2(&Class2::run, &class2);

    t1.join();
//    t2.join();
    std::cout << "after join\n";
    MultiThreadWatchdog::deleteWdg();
    return 0;
}
