#include "pch.h"
#include "HelloWorldGRPCServer.h"

#include "grpcs/helloworld.grpc.pb.h"

#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

std::thread t1;
void RunServer();

std::unique_ptr<Server> server;

class HelloWorldServerImpl : public helloworld::Greeter::Service {

    ::grpc::Status SayHello(::grpc::ServerContext* context, const ::helloworld::HelloRequest* request, ::helloworld::HelloReply* response) {
        std::string reqVal = request->name();
        std::cout << "SayHello name:" << reqVal << std::endl;
        response->set_message("Hi from Server");
        return ::grpc::Status::OK;
    }
};


GRPCSERVERLEARNEXPORT_API void helloworld_start()
{
    std::cout << "SERVER: helloworld_start called.\n";
    //return GRPCSERVERLEARNEXPORT_API void();
    t1 = std::move(std::thread(RunServer));
    std::cout << "SERVER: helloworld_start Exiting\n";
}

GRPCSERVERLEARNEXPORT_API void helloworld_stop()
{
    std::cout << "SERVER: helloworld_stop called.  Shutting down server, then Joining.\n";
    server->Shutdown();
    server.reset();
    t1.join();
    
    std::cout << "SERVER: helloworld_stop thread join complete. Exiting\n";


    
}



void RunServer() {
    std::string server_address("0.0.0.0:50051");
    HelloWorldServerImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    server = std::move(std::unique_ptr<Server> (builder.BuildAndStart()));
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
    std::cout << "SERVER: RunServer exiting\n";
}