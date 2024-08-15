#include <iostream>
#include <unistd.h>

int gval = 10;
int main(int argc,char*argv[])
{
    pid_t pid = 0;
    int lval = 20;
    gval++, lval+=5;
    pid = fork();
    if(pid == 0) //子进程
    {
        gval+=2;
        lval+=2;
    } 
    else if(pid>0)  //父进程
    {
        gval-=2;
        lval-=2;
    }
    else{
        std::cout << "fork error!\n";
    }
    
    if(pid == 0)
    {
        std::cout << "gval:" << gval<< " " << "lval:" << lval << std::endl;
    }
    else if(pid>0)
    {
        std::cout << "gval:" << gval<< " " << "lval:" << lval << std::endl;
    }
    return 0;
}