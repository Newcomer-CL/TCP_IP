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
    int recv_len = 0, str_len = 0, send_len = 0;
    while(1)
    {
        fputs("Input message(Q to quit):",stdout);
        fgets(buf,1024,stdin);
        if(!strcmp(buf,"q\n") || !strcmp(buf,"Q\n"))
        {
            break;
        }
        send_len = write(clnt_fd,buf,strlen(buf));
        while(recv_len < send_len)
        {
            str_len = read(clnt_fd,&buf[recv_len],send_len-recv_len);   //必须确保缓冲区大于send_len
            if(str_len == -1)
            {
                std::cout << "read error!\n";
                return -1;
            }
            recv_len += str_len;
        }
        
        buf[recv_len] = 0;
        std::cout << "message from server:" <<buf << std::endl;
        memset(&buf,0,sizeof(buf));
        recv_len = 0;
    }
    close(clnt_fd);
    return 0;
}

