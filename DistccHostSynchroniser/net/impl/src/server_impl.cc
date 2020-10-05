#include "net/impl/server_impl.h"
#include "net/impl/client_impl.h"
#include "Synca/dispatcher.h"

namespace net {

ServerImpl::ServerImpl(synca::Dispatcher &dispatcher):io_service_(),
    acceptor_(io_service_, tcp::endpoint(tcp::v4(), 8123)),
    dispatcher_(dispatcher) {}

std::unique_ptr<Client> ServerImpl::AsyncAccept() {
    tcp::socket socket(io_service_);
    dispatcher_.synca([&socket, this] {
        acceptor_.accept(socket);
    });
    return std::make_unique<ClientImpl>(std::move(socket), dispatcher_);
}

}
