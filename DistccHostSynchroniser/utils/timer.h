#ifndef TIMER_H
#define TIMER_H
#include "Synca/dispatcher.h"
#include <functional>
#include <thread>
namespace utils {

class Timer {
public:
    Timer (synca::Dispatcher& dispatcher,
           std::function<void()>&& callback,
           unsigned long timeout_ms):
        dispatcher_(dispatcher),
        callback_(std::move(callback)),
        timeout_ms_(timeout_ms) {

    }

    void Reset(unsigned long timeout_ms_) {

    }


    void Stop() {

    }

private:
    std::thread thread_;
    std::condition_variable cv_;
    std::mutex m_;
    std::function<void()> callback_;
    unsigned long timeout_ms_;
    synca::Dispatcher& dispatcher_;
};

}
#endif // TIMER_H

