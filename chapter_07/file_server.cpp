#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>


int main(int argc, char*argv[])
{
    if(argc!=2)
    {
        std::cout << "Usage:" << argv[0] << "<ip>\n";
        return -1;
    }

    int serv_fd = socket(PF_INET,SOCK_STREAM,0);
    if(serv_fd == -1)
    {
        std::cout << "socket error!\n";
        return -1;
    }
    struct sockaddr_in serv_addr,clnt_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    memset(&clnt_addr,0,sizeof(clnt_addr));
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) == -1)
    {
        std::cout << "bind error!\n";
        return -1;
    }

    if(listen(serv_fd,5) == -1)
    {
        std::cout << "listen error!\n";
        return -1;
    }

    socklen_t clnt_addr_size = sizeof(clnt_addr);
    int clnt_fd = accept(serv_fd,(struct sockaddr*)&clnt_addr,&clnt_addr_size);

    char buf[1024];
    FILE* fp = nullptr;

    fp = fopen("file_server.cpp","rb");

    while(1)
    {

    }






}