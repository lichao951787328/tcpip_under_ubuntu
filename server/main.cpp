#include <tcpip_port.h>
int main(int argc, char *argv[])
{
    // 用端口号声明
    tcpip_port port(3333);
    // 初始化
    port.initial();
    // 接收客户端连接
    port.accept_client();
    Sen_Data sd;
    sd.vel = 0.1; sd.direct =0.0;
    // 在连接状态下不断发送数据
    while (port.is_connect())
    {
        port.sendData(sd);
    }
    // 关闭与客户端的连接
    port.close_client();
    // 关闭端口
    port.closetcpip();
    return 0;
}