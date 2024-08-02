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
    struct sockaddr_in serv_addr,clnt_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[1]));
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sock_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))== -1)
    {
        std::cout << "bind error!\n";
        return -1;
    }
    char buf[1024] ={};
    socklen_t sizes = sizeof(clnt_addr);
    for(int i = 0; i< 3;i++)
    {
        sleep(5);
        recvfrom(sock_fd,buf,sizeof(buf),0,(struct sockaddr*)&clnt_addr,&sizes);
        std::cout << "Message " << i << ":" << buf << std::endl;
        memset(buf,0,sizeof(buf));
    }
    close(sock_fd);
    return 0;
}