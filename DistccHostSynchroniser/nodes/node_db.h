#pragma once
#include <string>
#include <vector>

#include "nodes/node_info.h"

namespace node {

enum class ResultCode {
    SUCCESS,
    IGNORED,
    REJECTED
};

class NodeDB {
public:
    virtual void AddNode(const NodeInfo&& node_info) = 0;

    virtual void RemoveNode(const NodeInfo& node_info) = 0;
    virtual void RemoveNode(const std::string& node_ip) = 0;

    virtual std::vector<NodeInfo> GetNodeList() = 0;
    virtual void Sync() = 0;
};

}
