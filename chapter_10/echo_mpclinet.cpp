#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

void read_childproc(int sig);
void read_rounte(int sock,char* buf);
void write_rounte(int sock, char* buf);

int main(int argc, char*argv[])
{
    int sock_fd = socket(PF_INET,SOCK_STREAM,0);
    if(sock_fd == -1)
    {
        std::cout << "socket error!\n";
        return -1;
    }

    if(argc!=3)
    {
        std::cout << "Usage:" << argv[0] << "<addr> <ip> \n";
        return -1;
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));

    struct sigaction act;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    act.sa_handler = read_childproc;
    sigaction(SIGCHLD,&act,0);

    if(connect(sock_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
    {
        std::cout << "connect error!\n";
        return -1;
    }
    char buf[1024] = {};
    pid_t pid = fork();
    if(pid == 0)
    {
        write_rounte(sock_fd,buf);
    }
    else if(pid == -1)
    {
        std::cout << "fork error!\n";
        return -1;
    }
    else{
        read_rounte(sock_fd,buf);
    }
}

void read_childproc(int sig)
{
    int status = 0;
    pid_t pid = waitpid(-1,&status,WNOHANG);
    if(WIFEXITED(status))
    {
        std::cout << "Removed proc id:" << pid << std::endl;
        std::cout << "child send:" << WEXITSTATUS(status) << std::endl;
    }
    
}

void read_rounte(int sock,char* buf)
{
    while(1)
    {
        int str_len = read(sock,buf,1024);
        if(str_len <= 0 )
        {
            return ;
        }
        std::string str = std::string(buf,str_len);
        std::cout << "Message from server:" << str << std::endl;
    }
}

void write_rounte(int sock, char* buf)
{
    while(1)
    {
        memset(buf,0,sizeof(buf));
        fgets(buf,1024,stdin);
        if(!strcmp(buf,"q\n") || !strcmp(buf,"Q\n"))
        {
            shutdown(sock,SHUT_WR);
            return;
        }
        write(sock,buf,strlen(buf));
    }
}