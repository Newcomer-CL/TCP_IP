#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

//服务端主要流程socket、bind、listen、accept这4个api按序调用
// bind需要绑定该服务器的ip信息
// accept返回文件描述符，用于与之连接的客户端通信，并且accpet这个api的后两个参数用来获取与之链接的客户端的信息

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

    write(clnt_fd,buf,sizeof(buf));
    close(serv_fd);
    close(clnt_fd);
    return 0;

}