#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        std::cout << "Usage:" << argv[0] << "<ip> <port>\n";
        return -1;
    }
    int clnt_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (clnt_fd == -1)
    {
        std::cout << "socket error!\n";
        return -1;
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));

    if(connect(clnt_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) == -1)
    {
        std::cout << "connect error!\n";
        return -1;
    }


}