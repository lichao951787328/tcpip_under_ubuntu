#include <tcpip_port.h>
int main(int argc, char** argv){
    // 声明端口，ip地址+端口号
    tcpip_port po("192.168.2.1", 3333);
    // 初始化
    po.initial();
    // 连接服务器
    if (po.connect_server() != -1)
    {
        // 在已经连接的状态下不断接收数据
        while (po.is_connect())
        {
            po.receve_data();
            // 使用接收数据格式来解析buffer
            po.analysisBuf();
        }
    }
    po.close_port();
    return 0;
}