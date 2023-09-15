#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>
#include <glog/logging.h>
#include <iostream>
using namespace std;
struct Rec_Data
{
    double vel;
    double direct;
};

struct Sen_Data
{
    double x, y;
};

class tcpip_port
{
private:
    string ip_add;
    u_int16_t CLINPORT;
    int sockfd = -1;
    int len;
    struct sockaddr_in  servaddr;
    char recevBuf[200];
public:
    Rec_Data rec_data;
    tcpip_port(string add, u_int16_t port);
    ~tcpip_port();
    int initial();
    int connect_server();
    int send_data(Sen_Data sd);
    int receve_data();
    bool is_connect();
    void analysisBuf();
    void close_port();
};
