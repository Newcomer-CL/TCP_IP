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
    int fds[2] = {};
    pipe(fds);
    int pid = 0, str_len = 0;
    char buf[1024] = {};
    struct sigaction act = {};
    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGCHLD,&act,0);
    pid = fork();
    if(pid == 0)
    {
        close(fds[1]);
        close(socket_fd);
        FILE*fp = nullptr;
        fp = fopen("echomsg.txt","wt");
        char mesgbuf[1024] = {};
        int str_len = 0;
        while((str_len = read(fds[0],mesgbuf,sizeof(mesgbuf)))>0)
        {
            std::cout << mesgbuf << std::endl;
            fwrite((void*)mesgbuf,1,str_len,fp);
        }
        fclose(fp);
        close(fds[0]);
        return 0;
    }
    while(1)
    {
        socklen_t clnt_len = sizeof(clnt_addr);
        int clnt_fd = accept(socket_fd,(struct sockaddr*)&clnt_addr,&clnt_len);
        if(clnt_fd == -1)
        {
            continue;
        }
        else{
            std::cout << "new clinet connect!\n";
        }
        pid = fork();
        if(pid == 0)
        {
            close(socket_fd);
            close(fds[0]);
            while((str_len = read(clnt_fd,buf,sizeof(buf))) != 0)
            {
                write(clnt_fd,buf,str_len);
                write(fds[1],buf,str_len);
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
            close(fds[0]);
            close(fds[1]);
            close(clnt_fd);
        }
    }
    

    close(socket_fd);
    return 0;
}