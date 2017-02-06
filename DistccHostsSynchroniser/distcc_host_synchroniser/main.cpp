#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "dispatcher.h"

int main() {
    using boost::asio::ip::tcp;
    boost::asio::io_service io_service;
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 8123));

    Dispatcher io_dispatcher;
    for (;;) {
         tcp::socket socket(io_service);
         acceptor.accept(socket);
         char buf[4096];
         socket.read_some(boost::asio::buffer(buf));
         std::cout << buf << std::endl;
         char resp[] = "Hello";
         socket.write_some(boost::asio::buffer(resp));
    }

    return 0;
}

