#pragma once
#include "rpc/rpc.h"
#include "net/client.h"
#include "utils/hash.h"

namespace rpc {
class OutOfDateNotification : public RPC {

public:
    OutOfDateNotification(net::Client& client,
                          const utils::Hash& hash);
    void Run();
private:
    net::Client& client_;
};
}
