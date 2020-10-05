#pragma once
#include "rpc/rpc.h"
#include "net/client.h"
#include "nodes/node_info.h"
#include "utils/hash.h"

namespace rpc {
class AddNodeRequest : public RPC {

public:
    AddNodeRequest(net::Client& client,
                   node::NodeInfo&& node_info,
                   const utils::Hash& hash);
    void Run();
private:
    net::Client& client_;
};


}  // namespace rpc
