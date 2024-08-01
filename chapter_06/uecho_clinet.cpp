#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include <unistd.h>

int main(int argc, char* argv[])
{
    if(argc!=3)
    {
        std::cout << "Usage:" << argv[0] << "<ip> <port>!\n";
        return -1;
    }
    int sock_fd = socket(PF_INET,SOCK_DGRAM,0);
    if(sock_fd==-1)
    {
        std::cout << "socket error!\n";
        return -1;
    }
    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    char buf[1024] = {};
    char message[1024] = {};
    while(1)
    {
        std::cout << "write message(print q to quit):";
        std::cin >> buf;
        if(!strcmp(buf,"q") || !strcmp(buf,"Q"))
        {
            break;
        }
        sendto(sock_fd,buf,strlen(buf),0,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
        socklen_t sizes = sizeof(serv_addr);
        recvfrom(sock_fd,message,sizeof(message),0,(struct sockaddr*)&serv_addr,&sizes);
        std::cout << "get message:" << message << std::endl;
        memset(buf,0,sizeof(buf));
        memset(message,0,sizeof(message));
    }
    close(sock_fd);
    return 0;
}