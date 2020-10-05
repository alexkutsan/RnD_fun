#pragma once
#include <boost/asio.hpp>
#include "net/client.h"
#include "utils/timer.h"

namespace synca {
  class Dispatcher;
}

namespace net {
typedef boost::asio::ip::tcp tcp;

class ClientImpl : public Client {
public:

    ClientImpl(tcp::socket&& socket,
               synca::Dispatcher& dispatcher);
    ~ClientImpl();
    std::string AsyncReceive(const int timeout) override;

    void AsyncSend(const  std::string &data) override;

    void Close();
private:

    tcp::socket socket_;
    synca::Dispatcher& dispatcher_;
    utils::Timer timer_;
};

}
