#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int caculate(const char *buf,int length);


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
    char results[4] ={};
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
        int str_len = 0,recv_num = 0;
        while(recv_num < 4)
        {
            str_len = read(clnt_fd,&buf[recv_num],4-recv_num);
            if(str_len ==-1)
            {
                std::cout << "read error!\n";
                return -1;
            }
            recv_num += str_len;
        }
        int num = 0;
        memcpy(&num,buf,4);

        while(recv_num < 4+ num*4+1)
        {
            str_len = read(clnt_fd,&buf[recv_num], 4+ num*4+1-recv_num);
            if(str_len ==-1)
            {
                std::cout << "read error!\n";
                return -1;
            }
            recv_num += str_len;
        }
        int result = caculate(buf,4+ num*4+1);
        memcpy(results,&result,4);
        write(clnt_fd,results,4);
        close(clnt_fd);
    }
    close(serv_fd);
    return 0;
}


int caculate(const char *buf,int length)
{
    char c = buf[length-1];
    if(c == '+')
    {
        int num = 0,data = 0,first_data = 0;
        memcpy(&num,buf,4);
        memcpy(&first_data,buf+4,4);
        for(int i = 1; i< num ;i++)
        {
            memcpy(&data,buf+4*(i+1),4);
            first_data += data;
        }
        return first_data;
    }
    else if(c == '-')
    {
        int num = 0,data = 0,first_data = 0;
        memcpy(&num,buf,4);
        memcpy(&first_data,buf+4,4);
        for(int i = 1; i< num ;i++)
        {
            memcpy(&data,buf+4*(i+1),4);
            first_data -= data;
        }
        return first_data;
    }
    else if(c == '*')
    {
        int num = 0,data = 0,first_data = 0;
        memcpy(&num,buf,4);
        memcpy(&first_data,buf+4,4);
        for(int i = 1; i< num ;i++)
        {
            memcpy(&data,buf+4*(i+1),4);
            first_data *= data;
        }
        return first_data;
    }
    else if(c == '/')
    {
        int num = 0,data = 0,first_data = 0;
        memcpy(&num,buf,4);
        memcpy(&first_data,buf+4,4);
        for(int i = 1; i< num ;i++)
        {
            memcpy(&data,buf+4*(i+1),4);
            first_data /= data;
        }
        return first_data;
    }
    else{
        std::cout << "计算符输入错误，无法解析\n";
        return -1;
    }
}