#ifndef TRACKER_H
#define TRACKER_H
#include <iostream>
#include "MultiThreadWatchdog.h"
class Tracker
{
public:
    Tracker();
    void execute();
    void init();
    void setSuspending();
    bool getSuspending();
private:
    void update();
    MultiThreadWatchdog* wdg_;
    ObjectsMonitor objMonitor_ = ObjectsMonitor::Tracker;
    bool suspending_{false};
};

#endif // TRACKER_H
