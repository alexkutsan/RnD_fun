#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "dispatcher.h"

typedef boost::asio::ip::tcp tcp;
class SocketAcceptor {
public:
    explicit SocketAcceptor(Dispatcher& dispatcher):
        io_service_(),
        acceptor_(io_service_, tcp::endpoint(tcp::v4(), 8123)),
        dispatcher_(dispatcher) {

    }

    tcp::socket AsyncAccept() {
        tcp::socket socket(io_service_);
        dispatcher_.synca([&socket, this] {
            acceptor_.accept(socket);
        });
        return socket;
    }

    boost::asio::io_service io_service_;
    tcp::acceptor acceptor_;
    Dispatcher& dispatcher_;
};

class AsyncSocket {
public:

    AsyncSocket(tcp::socket&& socket, Dispatcher& dispatcher):
        socket_(std::forward<tcp::socket>(socket)),
        dispatcher_(dispatcher) {
    }

    std::string AsyncRead() {
        char buf[4096];
        dispatcher_.synca([&buf, this] {
            socket_.read_some(boost::asio::buffer(buf));
        });

        return std::string(buf);
    }

    void AsyncWrite(const std::string& buf) {
        dispatcher_.synca([buf, this] {
            socket_.write_some(boost::asio::buffer(buf));
        });
    }

    tcp::socket socket_;
    Dispatcher& dispatcher_;
};

void ProcessClient(Dispatcher& dispatcher) {

}

int main() {
    Dispatcher io_dispatcher;
    io_dispatcher.defer([&io_dispatcher]{
        std::cout << "Hi" << std::endl;
        SocketAcceptor acceptor(io_dispatcher);
        while(true) {
            tcp::socket socket = acceptor.AsyncAccept();
            AsyncSocket s(std::move(socket), io_dispatcher);
            std::string data = s.AsyncRead();
            s.AsyncWrite(data);
        }
    });

    io_dispatcher.Loop();

    //    using boost::asio::ip::tcp;
    //    boost::asio::io_service io_service;
    //    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 8123));

    //    for (;;) {
    //         tcp::socket socket(io_service);
    //         io_dispatcher.sheldue([&socket, &acceptor] {
    //             acceptor.accept(socket);
    //         });
    //         char buf[4096];
    //         socket.read_some(boost::asio::buffer(buf));
    //         std::cout << buf << std::endl;
    //         char resp[] = "Hello";
    //         socket.write_some(boost::asio::buffer(resp));
    //    }
    return 0;
}

