#ifndef TASK_H
#define TASK_H

#include <boost/coroutine/all.hpp>
#include <functional>

namespace co = boost::coroutines;


class Dispatcher;

class Task {
public:
    Task(Dispatcher& dsprchr);

    Task(std::function<void()> func, Dispatcher& dsprchr);

    void cooperative(co::coroutine<void>::push_type& sink);


    Dispatcher& dispatcher_;
    std::function<void()> func_;
    co::coroutine<void>::pull_type source_;
    co::coroutine<void>::push_type* sink_;
};
typedef std::unique_ptr<Task> TaskPtr;






#endif // TASK_H
