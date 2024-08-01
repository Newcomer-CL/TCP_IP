#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include <unistd.h>

int main(int argc, char*argv[])
{
    if(argc!=2)
    {
        std::cout << "Usage:" << argv[0] << "<port>!\n";
        return -1;
    }
    int sock_fd = socket(PF_INET,SOCK_DGRAM,0);
    struct sockaddr_in serv_addr,clnt_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    memset(&serv_addr,0,sizeof(clnt_addr));
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[1]));


    if(bind(sock_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))== -1)
    {
        std::cout << "bind error!\n";
        return -1;
    }
    char buf[1024] = {};
    socklen_t sizes= sizeof(clnt_addr);
    while(1)
    {

        int len = recvfrom(sock_fd,buf,sizeof(buf),0,(struct sockaddr*)&clnt_addr,&sizes);
        if(len == -1)
        {
            std::cout << "recvfrom error!\n";
            return -1;
        }
        sendto(sock_fd,buf,len,0,(struct sockaddr*)&clnt_addr,sizes);
    }
    close(sock_fd);
    return 0;
}