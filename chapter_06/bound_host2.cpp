#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main(int argc,char*argv[])
{
    int sock_fd = socket(PF_INET,SOCK_DGRAM,0);
    if(sock_fd == -1)
    {
        std::cout << "socket error!\n";
        return -1;
    }
    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);

    char buf[] = "hello";
    char buf2[] = "nihao";
    char buf23[] = "hi";

    sendto(sock_fd,buf,strlen(buf),0,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    sendto(sock_fd,buf2,strlen(buf2),0,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    sendto(sock_fd,buf23,strlen(buf23),0,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

    close(sock_fd);
    return 0;
}