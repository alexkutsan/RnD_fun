#ifndef LOCAL_NODE_DB_H
#define LOCAL_NODE_DB_H
#include <fstream>
#include <assert.h>
#include <vector>

#include "nodes/node_info.h"
#include "utils/error_or.h"

namespace local_node_db {

enum Error {
    NodeNotExist,
    IOError
};

class LocalNodeDB {
public:

    virtual bool AddNode(const node::NodeInfo& node_info);
    virtual bool RemoveNode(const std::string& node_ip);
    virtual utils::ErrorOr<Error, node::NodeInfo> GetNodeInfo(const std::string& node_ip);

};

}

#endif // LOCAL_NODE_DB_H

