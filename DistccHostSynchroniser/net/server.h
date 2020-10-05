#pragma once
#include <string>
#include "net/client.h"
#include <memory>

namespace net {
class Server {
public:
    // TODO: Use error code check
    virtual std::unique_ptr<Client> AsyncAccept() = 0;
};

}
