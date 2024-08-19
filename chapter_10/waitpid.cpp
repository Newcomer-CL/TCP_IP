#include <unistd.h>
#include <iostream>
#include <sys/wait.h>

int main()
{
    int status = 0;
    pid_t pid = fork();
    if(pid == 0)
    {
        sleep(15);
        return 24;
    }
    else{
        while(!waitpid(-1,&status,WNOHANG))
        {
            sleep(3);
            puts("Sleep 3sec");
        }
        if(WIFEXITED(status))
        {
            std::cout << "child send " << WEXITSTATUS(status) << std::endl;
        }
    }
    return 0;
}