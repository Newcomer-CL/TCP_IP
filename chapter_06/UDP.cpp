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


TCP客户端是在connect的时候自动分配ip和端口号，UDP客户端是在sendto的时候自动分配端口号和ip

TCP数据传输是不存在边界的，因此在数据传输过程中调用的I/O函数次数不具任何意义
但是UDP是具有数据边界的协议，传输过程中调用的I/O函数的次数非常重要。输入函数的调用次数与输出函数的调用次数完全一致，才能保证接收全部已经发送的数据。

UDP的sendto函数的传输过程大致可分为以下3部分：
   1.向UDP套接字注册目标IP和端口号
   2.传输数据
   3.删除UDP套接字中注册的目标地址信息
每次可以向不同的目标地址发送消息，这种未注册目标地址信息的套接字被称为未连接套接字，反之注册了目标地址的套接字称为连接connected套接字

UDP属于未连接套接字，但是当使用UDP不停的往同一个地址发消息，使用sendto重复上述三个阶段显然效率不高。
这时候将UDP套接字变成已连接套接字会提高效率，方法如下：

sock = socket(PFINET,SOCK_DGRAM,0);
strcut sockaddr_in serv_addr,clnt_addr;
memset(&serv_addr,0,sizeof(serv_addr));
serv_addr.port ...
...
...
connect(sock,(struct sockaddr*)&clnt_addr,sizeof(clnt_addr));
read(sock,buf,sizeof(buf));