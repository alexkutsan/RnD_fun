#pragma once
#include <memory>
#include "rpc/rpc.h"
namespace net {
    class Client;
}

namespace rpc {
class RPCFactory {
 public:
    virtual std::unique_ptr<RPC> createRPC(const std::string& data,
                                           net::Client& client) = 0;

};
}
