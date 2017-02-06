#include "task.h"
#include "dispatcher.h"
using namespace std::placeholders;
Task::Task(Dispatcher &dsprchr):func_([]{}),
    dispatcher_(dsprchr), source_{std::bind(&Task::cooperative, this, _1)}
{
//    std::cout << "Task empty constructor call" << std::endl;
}


Task::Task(std::function<void ()> func, Dispatcher &dsprchr):
    func_(func) ,
    dispatcher_(dsprchr),
    source_{std::bind(&Task::cooperative, this, _1)}
{
//    std::cout << "Task constructor call" << std::endl;
}

void Task::cooperative(co::coroutine<void>::push_type &sink) {
//    std::cout << "cooperative starts" << std::endl;
    sink_ = &sink;
    sink();
//    std::cout << "cooperative before func call" << std::endl;
    func_();
//    std::cout << "cooperative after func call" << std::endl;
}
