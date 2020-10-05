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
    usleep(100000);
    return IoResult("data");
}

synca::Dispatcher& dispatcher() {
    static synca::Dispatcher d;
    return d;
}

template <typename F>
void Synca(F func) {
    dispatcher().yeld(std::move(func));
}

void BuisnessCode() {
    static int x = 0;
    x++;
    IoResult res;
    std::cout << "before io "  << x << std::endl;

    Synca([&res]() {
        res = do_io();
    });

    std::cout << res <<std::endl;
    std::cout << "After IO " << x << std::endl;
}

int main() {

}
