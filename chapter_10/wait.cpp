#include <unistd.h>
#include <iostream>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    int status;
    pid_t pid = fork();

    if(pid == 0)
    {
        return 3;
    }
    else{
        std::cout << "child PID:" << pid << std::endl;
        pid = fork();
        if(pid == 0)
        {
            exit(7);
        }
        else{
            std::cout << "child PID: " << pid << std::endl;
            wait(&status);
            if(WIFEXITED(status))
            {
                std::cout << "child send one:" << WEXITSTATUS(status) << std::endl;
            }

            wait(&status);
            if(WIFEXITED(status))
            {
                std::cout << "child send two:" << WEXITSTATUS(status) << std::endl;
            }
            sleep(30);
        }
    }
}