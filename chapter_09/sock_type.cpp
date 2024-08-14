#include <stdio.h>
#include <sys/socket.h>
#include <iostream>

int main(int argc,char* argv[])
{
    int tcp_sock = 0,udp_sock = 0;
    int sock_type = 0;
    socklen_t optlen = sizeof(sock_type);
    tcp_sock = socket(PF_INET,SOCK_STREAM,0);
    udp_sock = socket(PF_INET,SOCK_DGRAM,0);
    if(tcp_sock == -1)
    {
        std::cout << "TCP socket error!\n";
        return -1;
    }

    int state = getsockopt(tcp_sock,SOL_SOCKET,SO_TYPE,(void*)&sock_type,&optlen);
    if(state)
    {
        std::cout << "TCP getsockopt error!\n";
        return -1;
    }
    std::cout << "TCP socket type:" << sock_type << std::endl;

    state = getsockopt(udp_sock,SOL_SOCKET,SO_TYPE,(void*)&sock_type,&optlen);
    if(state)
    {
        std::cout << "UDP getsockopt error!\n";
        return -1;
    }
    std::cout << "UDP socket type:" << sock_type << std::endl;
}