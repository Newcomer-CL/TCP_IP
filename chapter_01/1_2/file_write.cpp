#include <unistd.h>     // open 、close 、read、 write 头文件
#include <iostream>
#include <fcntl.h>      // open 第二个参数的头文件 

// 文件描述符           对象
//    0              标准输入
//    1              标准输出
//    2              标准错误

//每次打开一个新的文件，系统会按照从小到大顺序返还fd值
// 因为0、1、2已经被占用所以一般从3开始

//linux 可以通过cat /proc/sys/fs/file-max查看系统级的最大文件描述符数量
//  ulimit -n 查看用户级最大文件描述符数量

// 系统调用，打开文件
// int open(const char *pathname, int flags);
// 成功返回文件描述符，失败-1；
// const char *pathname   文件路径
// int flags   文件打开模式
//       打开模式                 含义
//       O_CREAT                 必要时创建文件
//       O_TRUNC                 删除全部现有数据
//       O_APPEND                维持现有数据，保存到其后面
//       O_RDONLY                只读打开
//       O_WRONLY                只写打开
//       O_RDWR                  读写打开


// int close(int fd);
// 成功时返回0，失败时返回-1
// fd 需要关闭的文件或套接字描述符

// ssize_t write(int fd, void *buf, size_t count);
// 成功返回写入的字节数，失败返回-1；
// fd 数据传输对象的文件描述符
// void *buf 需要传输的数据的地址
// size_t count需要传输的字节数



int main()
{
    char buf[] = "Let's go!\n";

    int fd = open("data.txt",O_CREAT|O_WRONLY|O_TRUNC);
    if(fd < 0)
    {
        std::cout << "open error!\n";
        return -1;
    }
    std::cout << "file descriptor:" << fd << std::endl;

    if(write(fd,buf,sizeof(buf))== -1)
    {
        std::cout << "write error!\n";
        return -1;
    }
    close(fd);
    return 0;
}