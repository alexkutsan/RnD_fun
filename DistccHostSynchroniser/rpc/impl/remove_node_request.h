#pragma once
#include "rpc/rpc.h"
#include "net/client.h"
#include "utils/hash.h"

namespace rpc {
class RemoveNodeRequest : public RPC {

public:
    RemoveNodeRequest(net::Client& client,
                           const std::string& ip,
                           const utils::Hash& hash);
    void Run();
private:
    net::Client& client_;
};
}  // namepace rpc
