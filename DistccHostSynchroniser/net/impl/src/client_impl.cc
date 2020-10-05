#include "net/impl/client_impl.h"

#include "Synca/dispatcher.h"

namespace net {
static unsigned long close_connection_timeout = 1000;
ClientImpl::ClientImpl(tcp::socket&& socket,
                       synca::Dispatcher& dispatcher):
    socket_(std::forward<tcp::socket>(socket)),
    dispatcher_(dispatcher),
    timer_(dispatcher, [this]{this->Close();},
    close_connection_timeout){

}

ClientImpl::~ClientImpl() {
    socket_.close();
}

std::string ClientImpl::AsyncReceive(const int timeout) {
    char buf[4096];
    dispatcher_.synca([&buf, this] {
        socket_.read_some(boost::asio::buffer(buf));
    });
    return std::string(buf);
}

void ClientImpl::AsyncSend(const  std::string &data) {
    dispatcher_.synca([data, this] {
        socket_.write_some(boost::asio::buffer(data));
    });
}

void ClientImpl::Close() {

}

}
