#include <boost/coroutine/all.hpp>
#include <functional>
#include <iostream>
#include <tuple>
#include <unistd.h>
#include <thread>
#include <queue>
#include <assert.h>
#include "task.h"
#include "dispatcher.h"

typedef std::string IoResult;
IoResult do_io() {
    usleep(1000000);
    return IoResult("data");
}


Dispatcher& dispatcher() {
    static Dispatcher d;
    return d;
}

template <typename F, typename C>
void async(F func, C callback) {
    std::thread([func, cb(std::move(callback))]() mutable {
        func();
        cb();
    }).detach();
}


template <typename F>
void synca(F func) {
    dispatcher().yeld(std::move(func));
}

void BuisnessCode() {
    static int x = 0;
    x++;
    IoResult res;
    std::cout << "before io "  << x << std::endl;

    synca([&res]() {
        res = do_io();
    });

    std::cout << res <<std::endl;
    std::cout << "After IO " << x << std::endl;
}

int main() {
    dispatcher().shedule(BuisnessCode);
    dispatcher().shedule(BuisnessCode);
    dispatcher().shedule(BuisnessCode);
    dispatcher().shedule(BuisnessCode);
    dispatcher().shedule(BuisnessCode);
    dispatcher().shedule(BuisnessCode);
    dispatcher().shedule(BuisnessCode);
    dispatcher().shedule(BuisnessCode);
    dispatcher().shedule(BuisnessCode);
    dispatcher().shedule(BuisnessCode);
    dispatcher().shedule(BuisnessCode);
    dispatcher().shedule(BuisnessCode);
    dispatcher().shedule(BuisnessCode);
    dispatcher().shedule(BuisnessCode);
    dispatcher().shedule(BuisnessCode);
    dispatcher().Loop();
}
