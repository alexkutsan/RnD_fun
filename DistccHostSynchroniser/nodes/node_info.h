#ifndef CLIENTINFO_H
#define CLIENTINFO_H
#include <string>
namespace node {

class NodeInfo {
public:
    NodeInfo();
    std::string name_;
    std::string ip_;
    std::string os_info_;
    std::string env_;
};

}
#endif // CLIENTINFO_H
