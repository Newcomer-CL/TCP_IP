#include <iostream>
#include <unistd.h>

int main()
{
    int fds[2] = {};
    char str[]="Who are you?";
    char buf[36] = {};
    pipe(fds);
    pid_t pid = fork();
    if(pid == 0)
    {
        close(fds[0]);
        write(fds[1],str,sizeof(str));
    }
    else if(pid == -1)
    {
        std::cout << "fork error!\n";
        return -1;
    }
    else{
        close(fds[1]);
        read(fds[0],buf,sizeof(buf));
        puts(buf);
    }
    return 0;
}