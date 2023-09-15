#ifndef _TCPIP_PORT_H_
#define _TCPIP_PORT_H_
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>  
#include <unistd.h> 
#include <vector>

struct Rec_Data
{
    double x;
    double y;
};

struct Sen_Data
{
    double vel;
    double direct;
};



class tcpip_port
{
private:
    u_int16_t SERVPORT;
    int sock_fd,client_fd;
    int sin_size;
    struct sockaddr_in my_addr;
    struct sockaddr_in remote_addr;
    char recevBuf[200];
    char recvFlag = '\0';
public:
    Rec_Data rec_data;
    tcpip_port(u_int16_t port);
    ~tcpip_port();
    int initial();
    
    int accept_client();
    int recvChar();
    int recvData();
    void analysisBuf();
    int sendData(Sen_Data sd);
    void close_client();
    void closetcpip();
    // char getRecvFlag();
    void resetRecvFlag();
    inline bool is_connect()
    {
        return sock_fd!= -1;
    }
};

#endif