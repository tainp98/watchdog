#include "MultiThreadWatchdog.h"
#include "Tracker.h"
MultiThreadWatchdog* MultiThreadWatchdog::wdg_ = nullptr;
std::mutex MultiThreadWatchdog::mutex_;
MultiThreadWatchdog::MultiThreadWatchdog(double interval, size_t maxNumThreads)
    : maxNumThread_(maxNumThreads), interval_(interval)
{
    monitorThread_ = std::thread(&MultiThreadWatchdog::monitorThread, this);
}

bool MultiThreadWatchdog::Kick(const ObjectsMonitor &id, double timeMS)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (hashMap_.count(id))
    {
        // Erase the current item.
        list_.erase(hashMap_[id]);
        hashMap_.erase(id);
        --currentNumThreads_;
    }
    else if (currentNumThreads_ == maxNumThread_)
    {
        // Cannot add item.
        return false;
    }
    // Insert new item to front.
    using namespace std::chrono;
    auto expireTime = system_clock::now();
    expireTime += duration_cast<milliseconds>(duration<double>(timeMS));
    list_.emplace_front(std::make_pair(id, expireTime));
    hashMap_[id] = list_.begin();
    ++currentNumThreads_;
    return true;
}

bool MultiThreadWatchdog::Done(const ObjectsMonitor &id)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (hashMap_.count(id))
    {
        // Erase current item.
        list_.erase(hashMap_[id]);
        hashMap_.erase(id);
        --currentNumThreads_;
        return true;
    }
    return false;
}

bool MultiThreadWatchdog::IsExpired(ObjectsMonitor &expiredId)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (list_.size() && list_.back().second < std::chrono::system_clock::now())
    {
        expiredId = list_.back().first;
        return true;
    }
    return false;
}

auto MultiThreadWatchdog::GetNextExpireTime()
{
    std::lock_guard<std::mutex> lock(mutex_);
    using namespace std::chrono;
    auto expireTime = system_clock::now();
    expireTime += duration_cast<milliseconds>(interval_);
    return list_.size() ? list_.back().second : expireTime;
}

MultiThreadWatchdog::~MultiThreadWatchdog()
{
    monitorThreadEnable_ = false;
    monitorThread_.join();
    std::cout << "finish delete watchdog\n";
}

MultiThreadWatchdog *MultiThreadWatchdog::getWdg(double interval, size_t maxNumThreads)
{
    std::lock_guard<std::mutex> locker(MultiThreadWatchdog::mutex_);
    if(wdg_ == nullptr)
    {
        wdg_ = new MultiThreadWatchdog(interval, maxNumThreads);
    }
    return wdg_;
}

void MultiThreadWatchdog::deleteWdg()
{
    std::lock_guard<std::mutex> locker(MultiThreadWatchdog::mutex_);
    if(wdg_ != nullptr)
    {
        delete wdg_;
        wdg_ = nullptr;
    }
}

void MultiThreadWatchdog::setTrackerObject(Tracker *tracker)
{
    tracker_ = tracker;
}

void MultiThreadWatchdog::monitorThread()
{
    while (monitorThreadEnable_)
    {
        ObjectsMonitor expiredId{};
        if (IsExpired(expiredId))
        {
            if(expiredId == ObjectsMonitor::Tracker){
                std::cout << "Tracker is expired | continue...\n";
                list_.erase(hashMap_[expiredId]);
                hashMap_.erase(expiredId);
                --currentNumThreads_;
                tracker_->setSuspending();
            }
            else if(expiredId == ObjectsMonitor::Class2){
                std::cout << "Class2 is expired | terminate.. \n";
                std::terminate();
            }
            continue;
        }
        // Kick the WatchDog.
        std::cout << "Kicked System!" << std::endl;
        // Nothing has expired.
        std::this_thread::sleep_until(GetNextExpireTime());
    }
}
