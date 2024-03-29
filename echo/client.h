#pragma once

#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Client {
public:
    Client(string host, int port);
    ~Client();

    void run();

private:
    virtual void create();
    virtual void close_socket();
    void echo();
    bool send_request(string);
    bool get_response();
    bool generate_request(string & request); 
    void handle_response(string & response);
    bool check_equal(double value_one, double value_two);

    string host_;
    int port_;
    int server_;
    int buflen_;
    char* buf_;
    double speed_needed;
    double last_speed;
    double current_boost;
    double max_boost;
    double min_boost;
    int status;
};
