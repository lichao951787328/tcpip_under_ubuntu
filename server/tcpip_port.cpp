#include <tcpip_port.h>
#include <iostream>
#include <mutex>
// #define SERVPORT 3333
#define BACKLOG 10
using namespace std;
#include <vector>

// extern int sock_fd,client_fd;
// extern std::mutex m_tcpip;
tcpip_port::tcpip_port(u_int16_t port)
{
    SERVPORT = port;
}

tcpip_port::~tcpip_port()
{
    close_client();
    closetcpip();
}

int tcpip_port::initial()
{
    {
        // unique_lock<mutex> g(m_tcpip, std::defer_lock);
        // g.lock();
        if((sock_fd = socket(AF_INET, SOCK_STREAM/* |SOCK_NONBLOCK */, 0)) == -1) {
                perror("socket construct error");
                exit(1);
                return -1;
        }
        // g.unlock();
    }
    
    int flag = 1;
	if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag)) < 0)
	{
		printf("socket setsockopt error=%d(%s)!!!\n", errno, strerror(errno));
		exit(1);
	}


    my_addr.sin_family=AF_INET;
    my_addr.sin_port=htons(SERVPORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(my_addr.sin_zero),8);
    if(bind(sock_fd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
        perror("bind error");
        exit(1);
        return -1;
    }
    if(listen(sock_fd, BACKLOG) == -1) {
        perror("listen error");
        exit(1);
        return -1;
    }
    // int timeout = 50;
    
    // setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
    sin_size = sizeof(struct sockaddr_in);
    printf("initial port finish...\n");
    return 0;
}

int tcpip_port::accept_client()
{
    // unique_lock<mutex> g(m_tcpip, std::defer_lock);
    // g.lock();
    if((client_fd = accept(sock_fd, (struct sockaddr *)&remote_addr, (socklen_t *)&sin_size)) == -1) {
        perror("accept error");
        exit(1);
        return -1;
    }
    // g.unlock();
    printf("received a connection from %s\n", inet_ntoa(remote_addr.sin_addr));
    return 0;
}

int tcpip_port::recvChar()
{
    return recv(client_fd, &recvFlag, sizeof(recvFlag), 0);
}

int tcpip_port::recvData()
{
    cout<<"enter recve data "<<endl;
    cout<<"recevBUf size "<<sizeof(recevBuf)<<endl;
    int tmp = recv(client_fd, &recevBuf, sizeof(recevBuf), 0);
    cout<<"recevBUf size "<<sizeof(recevBuf)<<endl;
    return tmp; 
}

void tcpip_port::analysisBuf()
{
    rec_data = *((Rec_Data*)recevBuf);
    cout<<"x: "<<rec_data.x<<endl;
    cout<<"y "<<rec_data.y<<endl;
}

int tcpip_port::sendData(Sen_Data sd)
{
    return send(client_fd, (char*)(&sd), sizeof(Sen_Data), 0);
}

void tcpip_port::close_client()
{
    cout<<"close client"<<endl;
    close(client_fd);

}

void tcpip_port::closetcpip()
{
    cout<<"CLOSE TCPIP PORT..."<<endl;
    close(sock_fd);
}

// char tcpip_port::getRecvFlag()
// {
//     // return recvFlag;
//     return com_data.flag;
// }

void tcpip_port::resetRecvFlag()
{
    recvFlag = '\0';
}
