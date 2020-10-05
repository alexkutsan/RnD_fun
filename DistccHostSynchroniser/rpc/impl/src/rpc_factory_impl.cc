#include "rpc/impl/rpc_factory_impl.h"
#include "rpc/impl/add_node_request.h"
#include "rpc/impl/out_of_date_notification.h"
#include "rpc/impl/remove_node_request.h"
#include "utils/hash.h"
#include "rpc_protocol_generated.h"
#include <map>
namespace rpc {

std::unique_ptr<RPC> CreateRequest(const Protocol::RPC& rpc,
                                   net::Client& client) {
    assert(rpc.rpc_type() == Protocol::RPCType_Request);
        utils::Hash hash;
    switch (rpc.func_id()) {
    case Protocol::FunctionId_AddNodeId: {
        node::NodeInfo ni;
        return std::make_unique<AddNodeRequest>(client,
                                                std::move(ni),
                                                hash);
        break;
    }
    case Protocol::FunctionId_RemoveNodeId: {
        std::string ip;
        return std::make_unique<RemoveNodeRequest>(client,ip, hash);
        break;
    }
    }
}

std::unique_ptr<RPC>
RPCFactoryImpl::createRPC(const std::string &data,
                          net::Client& client) {

    // parce binary data to RPC
    const Protocol::RPC* rpc = Protocol::GetRPC(data.c_str());

    //    char c = data.at(0);
    //    switch (c) {
    //    case 'a': {
    //        node::NodeInfo ni;
    //        return std::make_unique<AddNodeRequest>(client,
    //                                                std::move(ni),
    //                                                hash);
    //    }
    //    case 'r': {
    //        std::string ip;
    //        return std::make_unique<RemoveNodeRequest>(client,ip, hash);
    //    }
    //    case 'u': {
    //        return std::make_unique<OutOfDateNotification>(client, hash);
    //    }
    //    default:
    //        break;
    //    }
}

}  // namespace
