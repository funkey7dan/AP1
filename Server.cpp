#include <thread>
#include <pthread.h>
#include <signal.h>
#include <chrono>
#include "Server.h"

Server::Server(int port)throw (const char*) {
    this->stopFlag = false;
    clientLimit = 3;
    fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd<0)
        throw "Socket creation failed.";
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);
    if(bind(fd,(struct sockaddr*)&server , sizeof(server))<0)
        throw "bind failed.";
    if(listen(fd,clientLimit)<0)
        throw "listen failure";

}


void Server::start(ClientHandler& ch)throw(const char*){

    t = new thread([&ch,this](){
        while(!stopFlag){
            socklen_t clientSize = sizeof(client);
            int aClient = accept(fd,(struct sockaddr*)&client,&clientSize);
            if(aClient<0)
                throw "Failed listening";
            // cout << "before handle" << endl;
            ch.handle(aClient);
            close(aClient);
            this_thread::sleep_for(chrono::milliseconds(10));
        }
        close(fd);
    });
}


void Server::stop(){
    this->stopFlag = true;
    t->join(); // do not delete this!
}

Server::~Server() {
}

