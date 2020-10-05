#include "rpc/impl/out_of_date_notification.h"
#include <iostream>

namespace rpc {

OutOfDateNotification::OutOfDateNotification(net::Client &client,
                                             const utils::Hash &hash):
    client_(client) {

}

void OutOfDateNotification::Run() {
    std::cout << "OutOfDateNotification" << std::endl;

}

}
