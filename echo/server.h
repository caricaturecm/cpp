#pragma once

#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <string>

using namespace std;

class Server {
public:
    Server(int port);
    ~Server();

    void run();
    
private:
    void create();
    void close_socket();
    void serve();
    void handle(int);
    void get_status(string & response);
    void set_boost(double boost);
    string get_request(int);
    bool send_response(int, string);

    int port_;
    int server_;
    int buflen_;
    long timestamp;
    double initial_speed;
    double boost;
    char* buf_;
    double max_speed;
};
