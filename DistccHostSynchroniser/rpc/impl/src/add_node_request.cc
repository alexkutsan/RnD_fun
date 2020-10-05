#include "rpc/impl/add_node_request.h"
#include <iostream>


namespace rpc {
AddNodeRequest::AddNodeRequest(net::Client &client, node::NodeInfo &&node_info,
                               const utils::Hash &hash):
    client_(client){

}

void AddNodeRequest::Run() {
    std::cout << "AddNodeRequest" << std::endl;
    client_.AsyncSend("AddNodeRequest Thanks");
}

}
