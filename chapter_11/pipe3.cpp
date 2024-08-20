#include <iostream>
#include <unistd.h>

int main()
{
    int fds1[2] = {}, fds2[2] = {};
    char str[] = "Who are you";
    char str2[] = "Thank you for your message";
    char buf[48] = {};
    pipe(fds1);
    pipe(fds2);
    pid_t pid = fork();
    if(pid == 0)
    {
        write(fds1[1],str,sizeof(str));
        read(fds2[0],buf,sizeof(buf));
        std::cout << "Child proc output:" << buf << std::endl;
    }
    else if(pid == -1)
    {
        std::cout << "fork error!\n";
        return -1;
    }
    else{
        write(fds2[1],str2,sizeof(str2));
        read(fds1[0],buf,sizeof(buf));
        std::cout << "Parents proc output:" << buf << std::endl;
    }

}