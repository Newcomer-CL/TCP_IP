#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <arpa/inet.h>
#include <string.h>

// int socket(int domain, int type, int protocol);
// return value：
        // 成功返回文件描述符，失败返回-1

// domain 套接字中使用的协议族信息
//    名称             协议族
//   PF_INET          IPv4互联网协议族
//   PF_INET6         IPv6互联网协议族
//   PF_LOCAL         本地通信的UNIX协议族
//   PF_PACKET        底层套接字的协议族
//   PF_IPX           IPX Novell协议族

// type 套接字数据传输类型信息
// 1.面向连接的套接字（SOCK_STREAM）,其特征如下：
//    1).传输过程中数据不会消失
//    2).按序传输数据
//    3).传输的数据不存在数据边界
//    4).套接字必须一一对应
// 所谓无边界是指：传输数据的计算机通过3次调用write函数一共传递了100个字节，
// 但接受数据的计算机仅通过一次read函数调用就接受了100个字节。
// 收发数据的套接字内部有缓存（buffer），简言之就是字节数组。通过套接字传输的数据将保存到该数组。
// 因此收到数据不需要立马read，可以等数据填满缓冲区在全部读取，也可以分多次读取

// 2.面向消息的套接字（SOCK_DGRAM），其特征如下：
//      1).强调快速传输而非传输顺序
//      2).传输的数据可能丢失也可能损坏
//      3).传输的数据有数据边界（传输数据的计算机发一次，接收数据的计算机就要接收一次）
//      4).限制每次传输的数据大小

// protocol 计算机间通信使用的协议信息（该参数决定最终采用的协议）
// 一般protocol只需要填0就行，因为一般前两个参数就决定了最终使用的协议
// 如：第一个参数是PF_INET,第二个参数是SOCK_STREAM,满足以上条件的协议只有IPPROTO_TCP,所以一般填0
// 但是当前两个参数不够用时（不能决定最终协议），第三个参数就要填写明确的协议


// 客户端主要流程socket、connect依序调用这两个api
// connetc 后两个参数用来配置需要连接的服务器ip信息

//TCP面向连接
//UDP面向消息

int main(int argc, char*argv[])
{
    if(argc != 3)
    {
        std::cout << "Usage: " << argv[0] << " <ip> <port>\n";
        return -1;
    }

    int serv_fd = socket(PF_INET,SOCK_STREAM,0);
    if(serv_fd==-1)
    {
        std::cout << "socket error!\n";
        return -1;
    }
    
    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    socklen_t sizes = sizeof(serv_addr);

    if(connect(serv_fd,(struct sockaddr*)&serv_addr,sizes)==-1)
    {
        std::cout << "connect error!\n";
        return -1;
    }

    char buf[1024] = {};
    int start = 0;
    int read_len = 0;
    while(read_len = read(serv_fd,&buf[start],1))
    {
        if(read_len < 0)
        {
            std::cout << "read error!\n";
            return -1;
        }
        start++;
    }
    std::cout << "get message from server:" << buf << std::endl;
    std::cout << "fun read real calls count:" << start << std::endl;
    close(serv_fd);
    return 0;
}