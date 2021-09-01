#ifndef MULTITHREADWATCHDOG_H
#define MULTITHREADWATCHDOG_H
#include <iostream>
#include <unordered_map>
#include <list>
#include <mutex>
#include <atomic>
#include <thread>
#include <exception>

enum class ObjectsMonitor : unsigned char{
    Tracker,
    Class2,
};

class Tracker;
class MultiThreadWatchdog
{
public:
    using ThreadId_t = std::thread::id;
    using Time_t = std::chrono::time_point<std::chrono::system_clock>;
public:
    ~MultiThreadWatchdog();
    bool Kick(const ObjectsMonitor &id, double timeMS = 100);
    bool Done(const ObjectsMonitor &id);
    bool IsExpired(ObjectsMonitor &expiredId);
    auto GetNextExpireTime();
    static MultiThreadWatchdog* getWdg(double interval, size_t maxNumThreads);
    static void deleteWdg();
    void setTrackerObject(Tracker* tracker);
private:
    MultiThreadWatchdog(double interval, size_t maxNumThreads);
    void monitorThread();
private:
    size_t maxNumThread_ = 0;
    size_t currentNumThreads_ = 0;
    std::list<std::pair<ObjectsMonitor, Time_t>> list_;
    std::unordered_map<ObjectsMonitor, std::list<std::pair<ObjectsMonitor, Time_t>>::iterator> hashMap_;
    std::chrono::duration<double> interval_;
    std::thread monitorThread_;
    std::atomic<bool> monitorThreadEnable_{true};
    static MultiThreadWatchdog* wdg_;
    static std::mutex mutex_;
    Tracker* tracker_ = nullptr;
};
#endif // MULTITHREADWATCHDOG_H
