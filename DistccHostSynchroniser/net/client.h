#pragma once
#include <string>
#include <memory>

namespace net {
class Client {
public:
    // TODO: Use error code check
    virtual void AsyncSend(const std::string& data) = 0;

    // TODO: Use ErrorOr
    virtual std::string AsyncReceive(const int timeout) = 0;
};
typedef std::unique_ptr<Client> ClientPtr;
}  //namespace net
