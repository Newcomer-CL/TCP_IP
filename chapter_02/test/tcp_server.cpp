#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>


int main(int argc, char* argv[])
{
    if(argc!= 2)
    {
        std::cout << "Usage:" << argv[0] << " <port>\n";
        return -1;
    }
    int serv_fd = socket(PF_INET,SOCK_STREAM,0);
    if(serv_fd == -1)
    {
        std::cout << "socket error!\n";
        return -1;
    }

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;

    memset(&clnt_addr,0,sizeof(clnt_addr));
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
    {
        std::cout << "bind error!\n";
        return -1;
    }

    if(listen(serv_fd,5)==-1)
    {
        std::cout << "listen error!\n";
        return -1;
    }

    socklen_t sizes = sizeof(clnt_addr);
    int clnt_fd = accept(serv_fd,(struct sockaddr*)&clnt_addr,&sizes);
    if(clnt_fd == -1)
    {
        std::cout << "accept error!\n";
        return -1;
    }

    char buf[] = "hello world";

    for(int i = 0;i<sizeof(buf);i++)
    {
        write(clnt_fd,&buf[i],1);
    }
    
    close(serv_fd);
    close(clnt_fd);
    return 0;

}