#include <unistd.h>
#include <iostream>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage:" << argv[0] << " <file>\n";
        return -1;
    }
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        std::cout << "open" << argv[1] << "failed!\n";
        return -1;
    }

    int fd2 = open("file_copy.txt", O_CREAT | O_WRONLY | O_TRUNC);
    if (fd2 < 0)
    {
        std::cout << "open file_copy.txt failed!\n";
        return -1;
    }

    char buf[24] = {};
    int len = 0;
    while ((len = read(fd, buf, sizeof(buf))) > 0)
    {
        // 判断读到多少就写入多少，第三个参数不要直接用sizeof(buf)
        // 这样可以确保最后一次不会写入多余字节
        if (write(fd2, buf, len) != len)
        {
            std::cout << "write error!\n";
            return -1;
        }
    }
    if (len < 0)
    {
        std::cout << "read error!\n";
        return -1;
    }
    close(fd);
    close(fd2);
    return 0;
}