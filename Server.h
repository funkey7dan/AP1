/*
 * Server.h
 *
 *  Created on: Dec 13, 2020
 *      Author: Eli
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <unistd.h>
#include <sys/socket.h>
#include <pthread.h>
#include <thread>
#include <netinet/in.h>
#include "commands.h"
#include "CLI.h"

using namespace std;
// edit your ClientHandler interface here:
class ClientHandler {
public:
    virtual void handle(int clientID) = 0;
};


// you can add helper classes here and implement on the cpp file
/**
 * socket io class
 */
class SocketIO : public DefaultIO {
public:
    int sockNum;
    SocketIO(int sock):sockNum(sock){}
    string read() override {
        string retString = "";
        char c = '0';
        // read char by char
        // TODO: think of better way to do this - too much sys calls.
        recv(this->sockNum, &c, 1 /* char size*/, 0);
        while (c != '\n') {
            retString += c;
            recv(this->sockNum, &c, 1 /* char size*/, 0);
        }
        return retString;
    }

    void write(string text) override {
        char const *c = text.c_str(); // to bytes
        send(this->sockNum, c, text.size(), 0);
    }

    void write(float f) override {
        send(this->sockNum, &f, sizeof(float), 0);
    }

    void read(float *f) override {
        char buffer[1024];
        int bytes_received = recv(this->sockNum, buffer, 100, 0);
        *f = atof(buffer);
    }
};

// edit your AnomalyDetectionHandler class here
class AnomalyDetectionHandler:public ClientHandler{
	public:
    virtual void handle(int clientID){
        SocketIO dio(clientID);
        CLI cli(&dio);
        cli.start();
    }
};


// implement on Server.cpp
class Server {
	thread* t; // the thread to run the start() method in
    int clientLimit;

	// you may add data members

public:
	Server(int port) throw (const char*);
	virtual ~Server();
	void start(ClientHandler& ch)throw(const char*);
	void stop();
};

#endif /* SERVER_H_ */
