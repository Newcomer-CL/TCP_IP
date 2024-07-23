#include <sys/socket.h>         //socket 头文件
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include <unistd.h>

// 客户端socket两个流程

// int socket(int domain, int type, int protocol);
// 成功时返回文件描述符，失败时返回-1

// int connect(int sockfd, const struct sockaddr *addr,socklen_t addrlen);
// 成功时返回0，失败时返回-1

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        std::cout << "Usage:" << argv[0] << " <IP> <port>\n";
        return -1;
    }
    int clnt_fd = socket(AF_INET,SOCK_STREAM,0);
    if(clnt_fd == -1)
    {
        std::cout << "socket create error!\n";
        return -1;
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_port = htons(atoi(argv[2]));
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_family = AF_INET;

    if(connect(clnt_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) == -1)
    {
        std::cout << "connect error!\n";
        return -1;
    }

    char buf[1024] = {};
    int len = read(clnt_fd,buf,sizeof(buf)-1);
    if(len < 0 )
    {
        std::cout << "read error!\n";
        return -1;
    }
    std::cout << "get message from server:" << buf << std::endl;
    close(clnt_fd);
    return 0;
}