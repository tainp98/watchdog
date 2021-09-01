#ifndef CLASS1_H
#define CLASS1_H
#include <MultiThreadWatchdog.h>
#include "Tracker.h"
class Class1
{
public:
    Class1();
    ~Class1();
    void run();
private:
    Tracker* tracker_ = nullptr;
    ObjectsMonitor objMonitor = ObjectsMonitor::Class2;
};

#endif // CLASS1_H
