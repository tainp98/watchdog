#include "Class2.h"

Class2::Class2()
{
    wdg_ = MultiThreadWatchdog::getWdg(3, 10);
}

Class2::~Class2()
{
}

void Class2::run()
{
    std::cout << "class2 thread id = " << std::this_thread::get_id() << std::endl;
    int i = 5;
    while(true) {
        if(i > 0) {
            wdg_->Kick(ObjectsMonitor::Class2);
            --i;
        } else {
//            wdg_->Done();
        }

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
