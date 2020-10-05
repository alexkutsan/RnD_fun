#include "rpc/impl/remove_node_request.h"
#include <iostream>


namespace rpc {

RemoveNodeRequest::RemoveNodeRequest(net::Client &client, const std::__cxx11::string &ip, const utils::Hash &hash):
    client_(client) {

}

void RemoveNodeRequest::Run() {
    std::cout << "RemoveNodeRequest" << std::endl;
    client_.AsyncSend("RemoveNodeRequest Thanks");
}

}
