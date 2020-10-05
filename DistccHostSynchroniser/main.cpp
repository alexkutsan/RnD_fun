#include <iostream>
#include <sstream>
#include <deque>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "dispatcher.h"
#include "net/impl/client_impl.h"
#include "net/impl/server_impl.h"
#include "rpc/impl/rpc_factory_impl.h"
#include "nodes/impl/node_db_impl.h"

class ClientProcessor {
public:
    ClientProcessor(synca::Dispatcher& io_dispatcher):
        node_db_("/tmp/file.txt"),
        rpc_factory_(),
        io_dispatcher_(io_dispatcher) {
    }

    void ProcessClient(std::unique_ptr<net::Client> client_ptr) {
        net::Client& client = *client_ptr;
        connected_clients_.push_back(std::move(client_ptr));
        io_dispatcher_.defer(std::move([&client, this]() {
            SyncProcessClient(client);
        }));
    }

private:
    void SyncProcessClient(net::Client& client) {
        while (true) {
            std::string data = client.AsyncReceive(0);
            auto rpc = rpc_factory_.createRPC(data, client);
            if(rpc) {
                rpc->Run();
            }
        }
    }

    node::NodeDBImpl node_db_;
    rpc::RPCFactoryImpl rpc_factory_;
    synca::Dispatcher& io_dispatcher_;
    synca::Dispatcher processing_dispatcher_;
    std::deque<net::ClientPtr> connected_clients_;
};

int main() {
    synca::Dispatcher io_dispatcher;
    ClientProcessor client_processor(io_dispatcher);

    io_dispatcher.defer([&io_dispatcher, &client_processor]{
        net::ServerImpl acceptor(io_dispatcher);
        while(true) {
            std::unique_ptr<net::Client> c = acceptor.AsyncAccept();
            client_processor.ProcessClient(std::move(c));
        }
    });

    io_dispatcher.Loop();
    return 0;
}

