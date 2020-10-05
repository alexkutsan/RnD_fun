#include "nodes/impl/node_db_impl.h"

node::NodeDBImpl::NodeDBImpl(const std::string &hosts_file):
    hosts_file_(hosts_file) {

}

void node::NodeDBImpl::AddNode(const node::NodeInfo &&node_info) {
    nodes_.push_back(node_info);
}

void node::NodeDBImpl::RemoveNode(const node::NodeInfo& node_info) {

}

void node::NodeDBImpl::RemoveNode(const std::string &node_ip) {

}

std::vector<node::NodeInfo> node::NodeDBImpl::GetNodeList() {
    return std::vector<node::NodeInfo>();
}

void node::NodeDBImpl::Sync() {

}
