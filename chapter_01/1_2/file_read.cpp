#include <unistd.h>
#include <fcntl.h>
#include <iostream>


// ssize_t read(int fd, void *buf, size_t count);
// 成功返回写入的字节数，失败返回-1；
// fd 数据传输对象的文件描述符
// void *buf 需要接收的数据的地址
// size_t count需要接收的字节数

int main()
{
    int fd = open("data.txt",O_RDONLY);
    if(fd < 0)
    {
        std::cout << "open error!\n";
        return -1;
    }
    char buf [1024] = {};
    int len = read(fd,buf,sizeof(buf));
    if(len < 0 )
    {
        std::cout << "read error!\n";
        return -1;
    }
    std::cout << "read message:" << buf << std::endl;
    close(fd);
    return 0;
}