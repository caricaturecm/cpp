#include "client.h"
#include <float.h>
#include <iostream>
#include <unistd.h>
#include <cmath>

Client::Client(string host, int port) {
    // setup variables
    host_ = host;
    port_ = port;
    buflen_ = 1024;
    buf_ = new char[buflen_+1];
}

Client::~Client() {
}

void Client::run() {
    // connect to the server and run echo program
    create();
    echo();
}

void
Client::create() {
    struct sockaddr_in server_addr;

    // use DNS to get IP address
    struct hostent *hostEntry;
    hostEntry = gethostbyname(host_.c_str());
    if (!hostEntry) {
        cout << "No such host name: " << host_ << endl;
        exit(-1);
    }

    // setup socket address structure
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_);
    memcpy(&server_addr.sin_addr, hostEntry->h_addr_list[0], hostEntry->h_length);

    // create socket
    server_ = socket(PF_INET,SOCK_STREAM,0);
    if (!server_) {
        perror("socket");
        exit(-1);
    }

    // connect to server
    if (connect(server_,(const struct sockaddr *)&server_addr,sizeof(server_addr)) < 0) {
        perror("connect");
        exit(-1);
    }
}

void
Client::close_socket() {
    close(server_);
}

void
Client::echo() {
    string line;
    // loop to handle user interface
    cout << "Please input the speed you want: " << endl;
    getline(cin,line);
    std::string::size_type sz;
    speed_needed = std::stod(line, &sz);
    cout << "speed need is: " << speed_needed << endl;
    cout << "start to throttle" << endl;
    min_boost = 0.0;
    max_boost = DBL_MAX;
    current_boost = 500.0; 
    string request = "";
    status = -1;
    while(status != 1){
        // append a newline
        usleep(1000000);
        if(generate_request(request)){
            cout << "min equal to max" << endl;
            break; 
        }
        request += "\n";
        // send request
        cout << "send request: "<< request << endl;
        bool success = send_request(request);
        // break if an error occurred
        if (not success)
            break;
        // get a response
        if(request.find("THROTTLE") == std::string::npos){
            success = get_response();
            // break if an error occurred
            if (not success)
                break;
        }else{
            status = 0;
        }
        //cout << "status is: " << status << endl;
    }
    cout << "found the throttle: " << current_boost << endl;
    close_socket();
}

bool
Client::generate_request(string & request){
    if(status == -1){
        if(check_equal(min_boost, max_boost)){
            cout << "check min and max when generate_request" << endl;
            return true;
        }
        if(check_equal(max_boost, DBL_MAX)){
            min_boost = current_boost;
            current_boost = current_boost * 2;
        }else{
            current_boost = min_boost/2 + max_boost/2;
        }
        request = "THROTTLE " + std::to_string(current_boost);
    }else if(status == 0){
        request = "STATUS";
    }
    return false;
}

bool
Client::send_request(string request) {
    // prepare to send request
    const char* ptr = request.c_str();
    int nleft = request.length();
    int nwritten;
    // loop to be sure it is all sent
    while (nleft) {
        if ((nwritten = send(server_, ptr, nleft, 0)) < 0) {
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

bool
Client::get_response() {
    string response = "";
    // read until we get a newline
    while (response.find("\n") == string::npos) {
        int nread = recv(server_,buf_,1024,0);
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
        response.append(buf_,nread);
    }
    // a better client would cut off anything after the newline and
    // save it in a cache
    cout << response;
    handle_response(response);
    return true;
}

bool
Client::check_equal(double value_one, double value_two){
    //cout << "value one: " << value_one << endl;
    //cout << "value two: " << value_two << endl;
    return (std::abs(value_one-value_two) <= 0.001);
}

void
Client::handle_response(string & response){
    size_t pos = response.find(" ");
    string speed = response.substr(0, pos);
    cout << "get speed: " << speed << endl;
    std::string::size_type sz;
    double new_speed = std::stod(speed, &sz);
    if(check_equal(new_speed, last_speed)){
        cout << "speed is stable" << endl;
        if(check_equal(new_speed, speed_needed)){
            cout << "speed " << new_speed << " equal to " << speed_needed << endl;
            status = 1;
            return;
        }
        if(new_speed < speed_needed){
            cout << "speed is too slow" << endl;
            min_boost = current_boost;    
        }else{
            cout << "speed is too fast" << endl;
            max_boost = current_boost;
        }
        status = -1;
        last_speed = 0.0;
    }else{
        status = 0;
        last_speed = new_speed;
    }
}
