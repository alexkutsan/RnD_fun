#pragma once
#include "nodes/node_db.h"
namespace node {

class NodeDBImpl : public NodeDB {
public:
    NodeDBImpl(const std::string& hosts_file);

   // NodeDB interface
    void AddNode(const NodeInfo &&node_info) override;
    void RemoveNode(const NodeInfo& node_info) override;
    void RemoveNode(const std::string& node_ip) override;
    std::vector<NodeInfo> GetNodeList()override ;
    void Sync() override;
private:
   const std::string hosts_file_;
   std::vector<NodeInfo> nodes_;
};

}  // namespace node
