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
    else{
        std::cout << "Connected...........\n";
    }
    char buf[1024] = {};
    char results[1024] = {};
    char c = ' ';
    int num = 0, count = 0,str_len = 0,recv_num = 0;
    std::cout << "Operand count: ";
    std::cin >> num;
    std::cin.get(c);                             // 接收缓冲区中的换行符
    memcpy(buf,&num,4);
    for(int i = 0;i<num;i++)
    {
        std::cout << "Operand " << i+1 << ":";
        std::cin >>count;
        memcpy(buf+4 + i*4,&count,4);
        std::cin.get(c);
    }
    std::cout << "Operator:";
    std::cin.get(c);                             //获取操作符
    memcpy(buf+4 + num*4,&c,1);
    std::cin.get(c);
    if(write(clnt_fd,buf,sizeof(buf))==-1)
    {
        std::cout << "write error!\n";
        return -1;
    }
    while(recv_num < 4)
    {
        str_len = read(clnt_fd,&results[recv_num],4-recv_num);
        if(str_len == -1)
        {
            std::cout << "read error!\n";
            return -1;
        }
        recv_num += str_len;
    }
    memcpy(&count,results,4);
    std::cout << "Operation result: " << count <<std::endl;
    close(clnt_fd);
    return 0;
}