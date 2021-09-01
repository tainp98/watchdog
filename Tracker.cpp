#include "Tracker.h"
Tracker::Tracker()
{
    wdg_ = MultiThreadWatchdog::getWdg(0.1,10);
}

void Tracker::execute()
{
    update();
}

void Tracker::init()
{
    wdg_->setTrackerObject(this);
}

void Tracker::setSuspending()
{
    suspending_ = true;
}

bool Tracker::getSuspending()
{
    return  suspending_;
}

void Tracker::update()
{
    std::cout << "Start update...\n";
    std::cout << "thread run Tracker = " << std::this_thread::get_id() << std::endl;
    while (true) {
        wdg_->Kick(objMonitor_, 0.5);
        int count = 0;
        while (true && !suspending_) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            if(count == 4)
                break;
            count++;
        }

        if(suspending_){
            std::cout << "Tracker timeout !!!\n";
            suspending_ = false;
            break;
        }
        wdg_->Done(objMonitor_);
        std::cout << "Work Done!\n";
    }


}
