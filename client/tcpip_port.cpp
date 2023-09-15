#include <tcpip_port.h>

tcpip_port::tcpip_port(string add, u_int16_t port)
{
    ip_add = add;
    CLINPORT = port;
    CHECK(CLINPORT > 1023 && CLINPORT < 65536);
}

tcpip_port::~tcpip_port()
{
}

int tcpip_port::initial()
{
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
        return -1;
    }
}

int tcpip_port::connect_server()
{
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(CLINPORT);
    if( inet_pton(AF_INET, ip_add.c_str(), &servaddr.sin_addr) <= 0){
        printf("inet_pton error for %s\n",ip_add);
        return -1;
    }
    if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
        printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
        return -1;
    }
}

bool tcpip_port::is_connect()
{
    if (sockfd != -1)
    {
        return true;
    }
    else
        return false;
}

int tcpip_port::send_data(Sen_Data sd)
{
    if (is_connect())
    {
        if(send(sockfd , (char*)(&sd) , sizeof(Sen_Data) , 0) == -1){
			cout << "send data failed : send function error"<< endl;
			return -1;
		}
        else
        {
            cout << "< > has been sent successfully " << endl;
            return 0;
        }

    }
    else
    {
        cout << "send data failed :  sockfd is invalid" << endl;
        return -1;
    }
}

int tcpip_port::receve_data()
{
    if (is_connect())
    {
        return recv(sockfd, &recevBuf, sizeof(recevBuf), 0);
    }
    else
    {
        cout << "send data failed :  sockfd is invalid" << endl;
        return -1;
    }
}

void tcpip_port::analysisBuf()
{
    rec_data = *((Rec_Data*)recevBuf);
    cout<<"vel: "<<rec_data.vel<<endl;
    cout<<"direct: "<<rec_data.direct<<endl;
}

void tcpip_port::close_port()
{
    close(sockfd);
}
