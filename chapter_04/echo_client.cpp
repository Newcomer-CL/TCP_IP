#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main(int argc,char*argv[])
{
    if(argc != 3)
    {
        std::cout << "Usage:" << argv[0] << "<ip> <port>\n";
    }
    int clnt_fd = socket(PF_INET,SOCK_STREAM,0);
    if(clnt_fd == -1)
    {
        std::cout << "socket error!\n";
        return -1;
    }
    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);

    socklen_t len = sizeof(serv_addr);

    if(connect(clnt_fd,(struct sockaddr*)&serv_addr,len)==-1)
    {
        std::cout << "connect error!\n";
        return -1;
    }
    char buf[1024] = {};
    while(1)
    {
        fputs("Input message(Q to quit):",stdout);
        fgets(buf,1024,stdin);
        if(!strcmp(buf,"q\n") || !strcmp(buf,"Q/n"))
        {
            break;
        }
        write(clnt_fd,buf,strlen(buf));
        int str_len = read(clnt_fd,buf,1023);
        buf[str_len] = 0;
        std::cout << "message from server:" <<buf << std::endl;
    }
    close(clnt_fd);
    return 0;
}

// 客户端存在的问题：
//  回声客户端希望达到的效果是每次我们从客户端发1个字符串给服务端，服务端会传一样的字符串给客户端
//  但是面向连接的套接字不存在数据边界，即套接字内部有个缓存，客户端可能多次write，但服务端只1次read,或者服务端可能多次write，客户端只read一次
//  基于面向连接套接字无数据边界特性，上述代码理论上存在相应问题