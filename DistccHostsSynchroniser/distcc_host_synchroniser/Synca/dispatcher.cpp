#include "dispatcher.h"


void Dispatcher::ExitLoop() {
    shutdown_ = true;
    cond_var_.notify_one();
}

void Dispatcher::SetupCurrentTask() {
    std::unique_lock<std::mutex> lock(m);
    assert(!tasks_.empty());
    current_task_ = std::move(tasks_.front());
    tasks_.pop();
}

void Dispatcher::WaitShelueOrShutdown()
{
    std::unique_lock<std::mutex> lock(m);
    if (tasks_.empty()) {
        std::cout << "Tasks are empty waition push or shutdown" << std::endl;
        cond_var_.wait(lock);
    }
}

void Dispatcher::Loop()  {

    while (!shutdown_) {
        SetupCurrentTask();
        assert(current_task_);
        current_task_->source_();
        WaitShelueOrShutdown();
    }

    while(!tasks_.empty()) {

    }
    std::cout << "Processed all tasks" << std::endl;
}

