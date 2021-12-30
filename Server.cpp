#include <thread>
#include <pthread.h>
#include <signal.h>
#include <chrono>
#include "Server.h"

Server::Server(int port)throw (const char*) {
}


void Server::start(ClientHandler& ch)throw(const char*){	
}

void Server::stop(){
    this->stopFlag = true;
    t->join(); // do not delete this!
}

Server::~Server() {
}

