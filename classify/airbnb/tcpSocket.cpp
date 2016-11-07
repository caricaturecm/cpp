//
// Created by ChenMin on 11/5/16.
//

/*
 * 题目是这样的，在一个server上有一个汽车的simulator，要求楼主用一个socket连过去，
 * 然后可以call两个API：getStatus()可以得到当前的速度和加速度，setStatus(加速度)可以修改汽车加速度。
 * 对于每一个加速度，这辆汽车会不断加速最终达到一个稳定速度。问题是要写一个wrapper function让汽车的速度稳定在29mph。
 * 楼主花了十几分钟才理解清楚题目，又花了五分钟学习怎么连socket。最后code是写完了，但是输出不正确。时间不够了就没有继续。
 * 跟面试官过了程序，他觉得算法没问题，也没找到不输出的原因。
这个我也花了好一阵才搞明白。面试官的意思是对于一个恒定的加速度，最终速度会收敛到一个稳定值，考虑地面阻力，风阻等等。。。
 他那个系统也是这么模拟的。这里可以把加速度理解成踩油门的力道，力道越大，最终的稳定速度越高。


题目里没给时间作为参数，但是因为写code的时候就是要不停地去query server来得到当前速度，所以还是有时间的概念的。
 比如两个query之间必须加一点延时，不然server会处理不过来。


对。。。读出来的数据都是实时的。而且set了加速度以后，server上读回来的速度是逐渐递增的，需要一段时间才能稳定，
 这段时间都需要等着，不停地通过socket去query。

考察的算法应该就类似于search in an array with unknown size。
 首先不断增加加速度，知道某个加速度对应的稳定速度大于等于29.然后再二分搜索。这个算法他是认可的
 *
 * */

/*#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <float.h>
#include <cmath>

using namespace std;


class Client {
public:
    Client(double tspeed) {
        targetSpeed = tspeed;
    }

    void run() {
        connectServer();
        getThrottle();
    }

    void connectServer() {
        int port = 3000;
        string host = "localhost";

        // use DNS to get IP address
        struct hostent *hostEntry;
        hostEntry = gethostbyname(host.c_str());
        if (!hostEntry) {
            cout << "No such host name: " << host << endl;
            exit(-1);
        }

        // setup socket address structure
        struct sockaddr_in server_addr;
        memset(&server_addr,0,sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        memcpy(&server_addr.sin_addr, hostEntry->h_addr_list[0], hostEntry->h_length);

        // create socket
        server = socket(PF_INET,SOCK_STREAM,0);
        if (server < 0) {
            perror("socket");
            exit(-1);
        }

        // connect to server
        if (connect(server,(const struct sockaddr *)&server_addr,sizeof(server_addr)) < 0) {
            perror("connect");
            exit(-1);
        } else {
            cout<<"connect successful."<<endl;
        }
    }

    void getThrottle() {
        status = -1;
        curThrottle = 500.0;
        minThrottle = 0.0;
        maxThrottle = DBL_MAX;
        preSpeed = -1;


        int buflen = 1024;
        char* buf = new char[buflen+1];

        while (status != 1) {
            usleep(1000000);
            string req = generateRequest();
            cout<<"send request:"<<req<<endl;
            req = req + "\n";
            // write the data to the server
            send(server, req.c_str(), req.length(), 0);

            // read the response
            memset(buf,0,buflen);
            if(req.find("STATUS") != string::npos){
                recv(server,buf,buflen,0);

                string response(buf);
                handleResponse(response);
            }
        }
        close(server);
    }

    string generateRequest() {
        string req = "";
        if (status == -1) {
            req = "THROTTLE " + to_string(curThrottle);
            status = 0;
        } else if (status == 0) {//send status
            req = "STATUS";
        }
        return req;
    }

    void handleResponse(string& response) {
        cout<<"handle response:"<<response<<endl;
        int pos = response.find_first_of(' ');
        double speed = stod(response.substr(0, pos));
//        double throttle = stod(response.substr(pos + 1));

        cout<<"preSpeed:"<<preSpeed<<",speed:"<<speed<<endl;

        if (isEqual(preSpeed, -1.0)) {
            preSpeed = speed;
        } else if (!isEqual(speed, preSpeed)) {
            preSpeed = speed;
        } else {
            cout<<"is stable, speed:"<<speed<<",throttle:"<<curThrottle<<endl;
            if (isEqual(speed, targetSpeed)) {
                status = 1;
                cout<<"throttle is:"<<curThrottle<<endl;
            } else {
                preSpeed = -1.0;
                status = -1;

                if (speed > targetSpeed) {
                    cout<<"throttle "<<curThrottle<<" is too large."<<endl;
                    maxThrottle = curThrottle;
                    curThrottle = minThrottle / 2.0 + maxThrottle / 2.0;
                } else {//speed < targetSpeed
                    minThrottle = curThrottle;
                    cout<<"throttle "<<curThrottle<<" is too small."<<endl;
                    if (isEqual(maxThrottle, DBL_MAX)) {
                        curThrottle = 2.0 * curThrottle;
                    } else {
                        curThrottle = minThrottle / 2.0 + maxThrottle / 2.0;
                    }

                }
            }
        }
    }

    bool isEqual(double a, double b) {
        if (fabs(a - b) < 0.0001) {
            return true;
        }
        return false;
    }

    void setTargetSpeed(double speed) {
        targetSpeed = speed;
    }
private:
    int server;
    double targetSpeed;
    double curThrottle, minThrottle, maxThrottle, preSpeed;
    int status;
};

int
main(int argc, char **argv)
{
    double speed = 12346.87532128;
    Client client(speed);

    client.run();
}*/


#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <float.h>
#include <cmath>
using namespace std;

class Client {
public:
    Client(double speed) {
        targetSpeed = speed;
    }

    void run() {
        connectServer();
        getThrottle();
    }

    void connectServer() {
        // setup default arguments
        int port = 3000;
        string host = "localhost";

        // use DNS to get IP address
        struct hostent *hostEntry;
        hostEntry = gethostbyname(host.c_str());
        if (!hostEntry) {
            cout << "No such host name: " << host << endl;
            exit(-1);
        }

        // setup socket address structure
        struct sockaddr_in server_addr;
        memset(&server_addr,0,sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        memcpy(&server_addr.sin_addr, hostEntry->h_addr_list[0], hostEntry->h_length);

        // create socket
        server = socket(PF_INET,SOCK_STREAM,0);
        if (server < 0) {
            perror("socket");
            exit(-1);
        }

        // connect to server
        if (connect(server,(const struct sockaddr *)&server_addr,sizeof(server_addr)) < 0) {
            perror("connect");
            exit(-1);
        }
    }

    void getThrottle() {
        status = -1;
        curThrottle = 500.0;
        minThrottle = 0.0;
        maxThrottle = DBL_MAX;
        preSpeed = -1.0;

        // allocate buffer
        int buflen = 1024;
        char* buf = new char[buflen+1];

        while (status != 1) {
            sleep(1);
            string req = generateRequest();
            req += "\n";
            cout<<"send request:"<<req<<endl;

            // write the data to the server
            send(server, req.c_str(), req.length(), 0);

            if (req.find("STATUS") != string::npos) {
                // read the response
                memset(buf,0,buflen);
                recv(server,buf,buflen,0);

                string response = string(buf);
                handleResponse(response);
            }
        }
        close(server);
    }

private:
    void handleResponse(string& response) {
        int pos = response.find_first_of(' ');
        double speed = stod(response.substr(0, pos));
        cout<<"speed:"<<speed<<",preSpeed:"<<preSpeed<<endl;

        if (isEqual(preSpeed, -1.0)) {
            preSpeed = speed;
        } else if (!isEqual(preSpeed, speed)) {
            preSpeed = speed;
        } else {
            cout<<"speed is stable, speed:"<<speed<<endl;
            if (isEqual(speed, targetSpeed)) {
                cout<<"find the throttle:" << curThrottle<<endl;
                status = 1;
            } else {
                preSpeed = -1.0;
                status = -1;

                if (speed > targetSpeed) {
                    cout<<"throttle :"<< curThrottle << ", is too large."<<endl;
                    maxThrottle = curThrottle;
                    curThrottle = minThrottle / 2.0 + maxThrottle / 2.0;
                } else {
                    cout<<"throttle :"<<curThrottle<<", is too small."<<endl;
                    minThrottle = curThrottle;
                    if (isEqual(maxThrottle, DBL_MAX)) {
                        curThrottle = 2.0 * curThrottle;
                    } else {
                        curThrottle = minThrottle / 2.0 + maxThrottle / 2.0;
                    }
                }
            }
        }
    }

    bool isEqual(double a, double b) {
        if (fabs(a - b) < 0.0001) {
            return true;
        }
        return false;
    }

    string generateRequest() {
        string req = "";
        if (status == -1) {
            req = "THROTTLE " + to_string(curThrottle);
            status = 0;
        } else if (status == 0) {
            req = "STATUS";
        }
        return req;
    }

    int status;
    double targetSpeed;
    double curThrottle, minThrottle, maxThrottle, preSpeed;
    int server;
};


int main() {
    double speed = 800.0;
    Client client(speed);
    client.run();
    return 0;
}


