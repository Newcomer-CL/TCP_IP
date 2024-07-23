#include <sys/socket.h>         //socket 头文件
#include <arpa/inet.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// 服务端套接字4个步骤
// int socket(int domain, int type, int protocol);
// 成功时返回文件描述符，失败时返回-1

// int bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen);
// 成功时返回0，失败时返回-1

// int listen(int sockfd, int backlog);
// 成功时返回0，失败时返回-1

// int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
// 成功时返回文件描述符，失败时返回-1
// 如果没有客户端连接，会阻塞在这个api，如果有客户端连接会返回



//该服务端不可以立即重新运行。想要重新运行需要更改之前的端口号
int main(int argc, char* argv[])
{
    int socket_fd = socket(AF_INET,SOCK_STREAM,0);
    if(socket_fd == -1)
    {
        std::cout << "socket create error!\n";
        return -1;
    }

    struct sockaddr_in serv_addr;       //头文件为<arpa/inet.h>
    struct sockaddr_in clnt_addr;

    char message[] = "hello world!";
    if(argc != 2)
    {
        std::cout << "Usage:" << argv[0] << " <port>\n";
        return -1;
    }

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if(bind(socket_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) == -1)
    {
        std::cout << "bind error!\n";
        return -1;
    }

    if(listen(socket_fd,5) == -1)
    {
        std::cout << "listen error!\n";
        return -1;
    }
    socklen_t clnt_len = sizeof(clnt_addr);

    int clnt_fd = accept(socket_fd,(struct sockaddr*)&clnt_addr,&clnt_len);
    if(clnt_fd == -1)
    {
        std::cout << "accept error!\n";
        return -1;
    }

    write(clnt_fd,message,sizeof(message));

    close(clnt_fd);
    close(socket_fd);
    return 0;
}