#include <iostream>
#include <unistd.h>
#include <stdio.h>

int main(int argc,char*argv[])
{
    pid_t pid = fork();

    if(pid == 0)
    {
        puts("Hi, I am a child process");
    }
    else{
        std::cout << "child process ID:" << pid << std::endl;
        sleep(30);
    }
}