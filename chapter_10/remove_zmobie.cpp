#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>

void read_childproc(int sig)
{
    int status;
    pid_t id = waitpid(-1,&status,WNOHANG);
    if(WIFEXITED(status))
    {
        std::cout << "Removed proc id:" << id << std::endl;
        std::cout << "child send:" << WEXITSTATUS(status) << std::endl;
    }
}

int main()
{
    struct sigaction act = {};
    act.sa_handler = read_childproc;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(SIGCHLD,&act,0);
    pid_t pid = fork();
    if(pid == 0)
    {
        puts("Hi, i'm child process");
        // waitpid 调用可能不会立即识别到所有子进程退出的状态，尤其是当多个子进程同时退出时。
        // 因此两个子进程sleep时间不一样
        sleep(20);                   
        return 12;
    }
    else{
        std::cout << "child proc id:" << pid << std::endl;
        pid = fork();
        if(pid == 0)
        {
            puts("Hi! I'm child process");
            sleep(10);
            exit(24);
        }
        else{
            int i;
            std::cout << "child proc id:" << pid << std::endl;
            for(i = 0;i<5 ;i++)
            {
                puts("wait....");
                sleep(6);
            }
        }
        
    }
    return 0;
}