#ifndef DISPATCHER_H
#define DISPATCHER_H
#include  "task.h"
#include <queue>
#include <iostream>
#include <memory>
#include <condition_variable>

namespace co = boost::coroutines;

class Dispatcher
{
public:
    Dispatcher():
        current_task_(std::make_unique<Task>(*this)),
        shutdown_(false) {

    }

    template <class F>
    void shedule(F func) {
        TaskPtr t = std::make_unique<Task>(func, *this);
        sheldue(t);
    }

    void sheldue(TaskPtr& t) {
        assert(t);
        std::unique_lock<std::mutex> lock(m);
        tasks_.push(std::move(t));
        std::cout << "Sheldue new task" << std::endl;
        cond_var_.notify_one();
    }

    template<class F>
    void yeld(F f) {
        std::cout << "yelding !!!" << std::endl;
        TaskPtr t = std::move(current_task_);
        assert(t);
        assert(t->sink_);
        co::coroutine<void>::push_type& sink = *(t->sink_);
        auto callback = [this, task = std::move(t)] () mutable {
            sheldue(task);
        };
        async(f, std::move(callback));
        if (sink) {
            sink();
        }
    }

    void ExitLoop();

    void Loop();
    TaskPtr current_task_;
    std::queue<TaskPtr> tasks_;
    std::mutex m;
    std::condition_variable cond_var_;
    bool shutdown_;
private:
    void SetupCurrentTask();
    void WaitShelueOrShutdown();
};



#endif // DISPATCHER_H
