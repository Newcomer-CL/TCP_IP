UDP提供的是不可靠的数据传输服务，但UDP比TCP简洁
流量控制是区分UDP与TCP的最重要标志
TCP比UDP满的主要原因是：
   1.手法数据前后进行的连接设置及清除过程
   2.收发数据过程中为保证可靠性而添加的流控制

UDP中的服务端和客户端没有连接，也就是说不必调用listen、accept函数
在UDP中，不管是服务器还是客户端都只需要一个套接字


UDP套接字不会保持连接状态，因此每次传输数据都需要添加目标地址信息
基于UDP的数据I/O函数：

#include <sys/socket.h>

ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
                      const struct sockaddr *dest_addr, socklen_t addrlen);
成功时返回传输的字节数，失败时返回-1。
sockfd      用于传输的文件描述符
buf         保存待传输数据的缓冲地址值
len         待传输数据长度
flags       可选项参数
dest_addr   存有目标地址信息的sockaddr结构体变量值
addrlen     dest_addr变量的长度



#include <sys/socket.h>

ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
                        struct sockaddr *src_addr, socklen_t *addrlen);
成功时返回接收的字节数，失败时返回-1。
sockfd      用于接收的文件描述符
buf         保存待接收数据的缓冲地址值
len         可接收的最大字节数
flags       可选项参数
dest_addr   存有发送端地址信息的sockaddr结构体变量值
addrlen     dest_addr变量的长度