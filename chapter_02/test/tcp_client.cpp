#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <arpa/inet.h>
#include <string.h>


int main(int argc, char*argv[])
{
    if(argc != 3)
    {
        std::cout << "Usage: " << argv[0] << " <ip> <port>\n";
        return -1;
    }

    int serv_fd = socket(PF_INET,SOCK_STREAM,0);
    if(serv_fd==-1)
    {
        std::cout << "socket error!\n";
        return -1;
    }
    
    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    socklen_t sizes = sizeof(serv_addr);

    if(connect(serv_fd,(struct sockaddr*)&serv_addr,sizes)==-1)
    {
        std::cout << "connect error!\n";
        return -1;
    }

    char buf[1024] = {};
    for(int i = 0;i<3000;i++)
    {
        std::cout << "Wait time " << i << std::endl;
    }
    if(read(serv_fd,buf,sizeof(buf))== -1)
    {
        std::cout << "read error!\n";
        return -1;
    }

    std::cout << "get message from server:" << buf << std::endl;
    close(serv_fd);
    return 0;
}