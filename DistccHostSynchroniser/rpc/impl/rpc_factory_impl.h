#pragma once
#include "rpc/rpc_factory.h"
#include "rpc/impl/add_node_request.h"
#include "rpc/impl/remove_node_request.h"
#include "rpc/impl/out_of_date_notification.h"

namespace rpc {
class RPCFactoryImpl : public RPCFactory {
public:
    std::unique_ptr<RPC> createRPC(const std::string &data,
                                   net::Client& client);
};

}  // namespace rpc
