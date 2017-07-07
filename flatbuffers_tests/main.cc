#include "rpc_protocol_generated.h"
#include <iostream>
#include <vector> 

std::vector<uint8_t> createNode() {
	flatbuffers::FlatBufferBuilder builder(1024);
	auto name  = builder.CreateString("Some name");
	auto ip  = builder.CreateString("162.168.1.1");
	auto os  = builder.CreateString("Ubuntu version");
	auto env  = builder.CreateString("compiler");
        auto node = Protocol::CreateNode(builder, name, ip, os, env);
	builder.Finish(node);
	uint8_t* data= builder.GetBufferPointer();
	std::vector<uint8_t> data_vec(builder.GetSize());
	data_vec.assign(data, data + builder.GetSize());	
	return data_vec;
}


const Protocol::Node& getNode(std::vector<uint8_t>&  data) {
	uint8_t* d = &(data[0]);
	const Protocol::Node* node = Protocol::GetNode(d);
	return *node;  
}


int main() {
	std::vector<uint8_t> data = createNode();	

        const Protocol::Node& n(getNode(data));
	std::cout << n.name()->str() << std::endl;
	std::cout << n.ip()->str() << std::endl;
	std::cout << n.os_info()->str() << std::endl;
	std::cout << n.env()->str() << std::endl;
	// std::cout << ip <<std::endl;
}
