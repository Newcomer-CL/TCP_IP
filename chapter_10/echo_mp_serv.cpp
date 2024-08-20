#include <sys/socket.h>         //socket 头文件
#include <arpa/inet.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

void read_childproc(int sig)
{
    pid_t pid = 0;
    int status = 0;
    pid = waitpid(-1,&status,WNOHANG);
    std::cout << "remove proc id:" << pid << std::endl;
}

int main(int argc, char* argv[])
{
    int socket_fd = socket(AF_INET,SOCK_STREAM,0);
    if(socket_fd == -1)
    {
        std::cout << "socket create error!\n";
        return -1;
    }

    struct sockaddr_in serv_addr;       //头文件为<arpa/inet.h>
    struct sockaddr_in clnt_addr;

    char message[] = "hello world!";
    if(argc != 2)
    {
        std::cout << "Usage:" << argv[0] << " <port>\n";
        return -1;
    }

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if(bind(socket_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) == -1)
    {
        std::cout << "bind error!\n";
        return -1;
    }

    if(listen(socket_fd,5) == -1)
    {
        std::cout << "listen error!\n";
        return -1;
    }

    int pid = 0, str_len = 0;
    char buf[1024] = {};
    struct sigaction act = {};
    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGCHLD,&act,0);
    while(1)
    {
        socklen_t clnt_len = sizeof(clnt_addr);
        int clnt_fd = accept(socket_fd,(struct sockaddr*)&clnt_addr,&clnt_len);
        if(clnt_fd == -1)
        {
// 为什么accpet返回值是-1，却要continue。
// 当accept返回-1时，通常表示在等待接受连接时发生了错误，
//这可能是由于网络中断、连接重置或者其他一些问题导致的。
//在这种情况下，执行continue操作是为了跳过当前循环，继续等待下一个连接请求，
//而不是因为客户端连接失败而终止整个程序的执行。这样可以确保服务器程序在出现连接错误时能够继续正常运行，
//等待其他客户端的连接请求。
            continue;
        }
        else{
            std::cout << "new clinet connect!\n";
        }
        pid = fork();
        if(pid == 0)
        {
            close(socket_fd);
            while((str_len = read(clnt_fd,buf,sizeof(buf))) != 0)
            {
                write(clnt_fd,buf,str_len);
            }
            close(clnt_fd);
            std::cout << "clinet disconnect!\n";
            return 0;
        }
        else if(pid == -1)
        {
            std::cout << "fork error!\n";
            return -1;
        }
        else{
            close(clnt_fd);
        }
    }
    

    close(socket_fd);
    return 0;
}