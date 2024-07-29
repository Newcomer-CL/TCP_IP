#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    if(argc!=2)
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

    struct sockaddr_in serv_addr,clnt_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_port = htons(atoi(argv[1]));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(serv_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) == -1)
    {
        std::cout << "bind error!\n";
        return -1;
    }

    if(listen(serv_fd,5) == -1)
    {
        std::cout << "listen error !\n";
        return -1;
    }

    memset(&clnt_addr,0,sizeof(clnt_addr));
    socklen_t clnt_size = sizeof(clnt_addr);
    char buf[1024] = {};
    for(int i = 0;i< 5;i++)                           
    {
        int clnt_fd = accept(serv_fd,(struct sockaddr*)&clnt_addr,&clnt_size);  // 依次向5个客户端提供服务
        if(clnt_fd == -1)
        {
            std::cout << "accpet error!\n";
            return -1;
        }
        else{
            std::cout << "connect clinet:" << clnt_fd << std::endl;
        }
        int str_len = 0;
        while(((str_len = read(clnt_fd,buf,1024)) > 0 ))
        {
            write(clnt_fd,buf,str_len);
        }
        close(clnt_fd);
    }
    close(serv_fd);
    return 0;
}