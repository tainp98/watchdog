#ifndef CLASS2_H
#define CLASS2_H
#include "MultiThreadWatchdog.h"

class Class2
{
public:
    Class2();
    ~Class2();
    void run();
private:
    MultiThreadWatchdog *wdg_;
};

#endif // CLASS2_H
