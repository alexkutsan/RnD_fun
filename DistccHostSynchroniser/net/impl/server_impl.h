#pragma once
#include <boost/asio.hpp>
#include "net/server.h"

namespace synca {
class Dispatcher;
}

namespace net {
typedef boost::asio::ip::tcp tcp;
class ServerImpl : public Server {

public:
    explicit ServerImpl(synca::Dispatcher& dispatcher);
    std::unique_ptr<Client>  AsyncAccept() override;

    boost::asio::io_service io_service_;
    tcp::acceptor acceptor_;
    synca::Dispatcher& dispatcher_;

};


}
