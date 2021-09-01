#include "Class1.h"

Class1::Class1()
{
    tracker_ = new Tracker();
}

Class1::~Class1()
{
}

void Class1::run()
{
    tracker_->init();
    std::cout << "class1 thread id = " << std::this_thread::get_id() << std::endl;
    while (true) {
        tracker_->execute();
    }

    std::cout << "End execute !!!\n";

}
