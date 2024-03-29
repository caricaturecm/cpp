#include "server.h"
#include <string>
#include <unistd.h>
#include <sys/time.h>
#include <iostream>

Server::Server(int port) {
    // setup variables
    port_ = port;
    buflen_ = 1024;
    buf_ = new char[buflen_+1];
    initial_speed = 0.0;
    timestamp = 0;
    boost = 0.0;
}

Server::~Server() {
    delete buf_;
}

void
Server::run() {
    // create and run the server
    create();
    serve();
}

void
Server::set_boost(double new_boost){
    boost = new_boost;
    struct timeval tp;
    gettimeofday(&tp, NULL);
    timestamp = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    std::cout << "store time stamp: " << timestamp << std::endl;
    initial_speed = 0.0;
    max_speed = boost * 2.0;
}

void
Server::get_status(string & response){  
    struct timeval tp;
    gettimeofday(&tp, NULL);
    long current = tp.tv_sec * 1000 + tp.tv_usec / 1000; 
    std::cout << "current time stamp is: " << current << std::endl;
    double current_speed = (current - timestamp) / 1000 * boost;
    if(current_speed > max_speed){
        current_speed = max_speed;
    }
    response = "";
    response = std::to_string(current_speed) + " " + std::to_string(boost) + "\n";
    std::cout << "current response: " << response << endl;
}

void
Server::create() {
    struct sockaddr_in server_addr;

    // setup socket address structure
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // create socket
    server_ = socket(PF_INET,SOCK_STREAM,0);
    if (!server_) {
        perror("socket");
        exit(-1);
    }

    // set socket to immediately reuse port when the application closes
    int reuse = 1;
    if (setsockopt(server_, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        perror("setsockopt");
        exit(-1);
    }

    // call bind to associate the socket with our local address and
    // port
    if (bind(server_,(const struct sockaddr *)&server_addr,sizeof(server_addr)) < 0) {
        perror("bind");
        exit(-1);
    }

    // convert the socket to listen for incoming connections
    if (listen(server_,SOMAXCONN) < 0) {
        perror("listen");
        exit(-1);
    }
}

void
Server::close_socket() {
    close(server_);
}

void
Server::serve() {
    // setup client
    int client;
    struct sockaddr_in client_addr;
    socklen_t clientlen = sizeof(client_addr);

      // accept clients
    while ((client = accept(server_,(struct sockaddr *)&client_addr,&clientlen)) > 0) {

        handle(client);
    }
    close_socket();
}

void
Server::handle(int client) {
    // loop to handle all requests
    while (1) {
        // get a request
        string request = get_request(client);
        string response = request;
        // break if client is done or an error occurred
        if (request.find("THROTTLE") != std::string::npos){
            cout << "received request: " << request << endl;
            string value = request.substr(8, request.length()-8);
            std::string::size_type sz;
            double new_boost = std::stod(value, &sz);
            set_boost(new_boost);
        }else if(request.find("STATUS") != std::string::npos){
            cout << "received request: " << request << endl;
            get_status(response); 
            if (request.empty())
                break;
            // send response
            cout << "send response" << endl;
            bool success = send_response(client, response);
            // break if an error occurred
            if (not success)
                break;
        }
    }
    close(client);
}

string
Server::get_request(int client) {
    string request = "";
    // read until we get a newline
    while (request.find("\n") == string::npos) {
        int nread = recv(client,buf_,1024,0);
        if (nread < 0) {
            if (errno == EINTR)
                // the socket call was interrupted -- try again
                continue;
            else
                // an error occurred, so break out
                return "";
        } else if (nread == 0) {
            // the socket is closed
            return "";
        }
        // be sure to use append in case we have binary data
        request.append(buf_,nread);
    }
    // a better server would cut off anything after the newline and
    // save it in a cache
    return request;
}

bool
Server::send_response(int client, string response) {
    // prepare to send response
    const char* ptr = response.c_str();
    int nleft = response.length();
    int nwritten;
    // loop to be sure it is all sent
    while (nleft) {
        if ((nwritten = send(client, ptr, nleft, 0)) < 0) {
            if (errno == EINTR) {
                // the socket call was interrupted -- try again
                continue;
            } else {
                // an error occurred, so break out
                perror("write");
                return false;
            }
        } else if (nwritten == 0) {
            // the socket is closed
            return false;
        }
        nleft -= nwritten;
        ptr += nwritten;
    }
    return true;
}
