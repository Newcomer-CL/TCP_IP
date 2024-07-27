// 3.1 分配给套接字的IP地址与端口号
// IP(Internet Protocol),是为收发网络数据而分配给计算机的值。
// IP地址分为两类 IPv4、IPv6，一般使用IPv4（4字节地址族），IPv6（16字节地址族）是为了应对IP地址耗尽问题提出的新标准
// IPv4标准的4字节IP地址分为网络地址与主机（指计算机）地址，且分为A、B、C、D、E等类型
// A类      1字节   1字节   1字节   1字节   (第一个字节表示网络ID,后三个字节表示主机ID)
//         网络ID          主机ID
// B类      1字节   1字节   1字节   1字节   (前两个字节表示网络ID,后二个字节表示主机ID)
//             网络ID          主机ID
// C类      1字节   1字节   1字节   1字节   (前三个字节表示网络ID,后一个字节表示主机ID)
//                 网络ID          主机ID
// D类      1字节   1字节   1字节   1字节   
//                     多播IP地址
// 多播IP地址是一种IPv4或IPv6地址，用于将数据包同时发送到一个组中的多个目标设备。
// 在IPv4中，多播地址属于特定的地址范围（224.0.0.0到239.255.255.255），并不是所有的4字节地址都是多播地址。
// 多播地址的特点是其特定的地址范围和用途，通常用于需要将数据同时发送给多个设备的应用场景，如视频流、音频流的分发等。

// 网络地址是为了区分网络而设置的一部分IP地址
// 假设向WWW.SEMI.COM公司传数据，先浏览4字节IP地址的网络地址，把数据传输到SEMI.COM的网络，
// SEMI.COM网络（构成网络的路由器）接到数据后，在浏览主机地址，并将数据发送给目标计算机

// “向相应网络传输数据”实际上是向构成网络的路由器（Router）或交换机（Switch）传递数据，
// 接收数据的路由器或者交换机根据数据中的主机地址向目标主机传递数据

// 只需通过IP地址的第一个字节即可判断网络地址占用的字节数，因为我们根据IP地址的边界区分网络地址
// A类地址的首字节范围：0-127
// B类地址的首字节范围：128-191
// C类地址的首字节范围：192-223

// 第一个字节是8位，为什么A类地址的首字节范围是0-127，2的7次方呢？
// 是因为A类地址的首位是以0开始的，即A类地址范围是0XXXXXXX(X可表示的值为0或1)
//      B类地址的首位是以10开始的，即B类地址范围是10XXXXXX(X可表示的值为0或1)
//      C类地址的首位是以110开始的，即C类地址范围是110XXXXX(X可表示的值为0或1)

// 端口号是在同一操作系统中为了区分不同套接字而设置的
// 如：此时你正在用电脑学习，你既打开了vscode、又打开了pdf阅读器，
// 此时从网络来了一个消息，操作系统怎么区分是发给vscode，还是发给pdf阅读器
// 是的，通过端口号，端口号一般由16为构成，可分配范围为0-65535，但0-1023是知名端口号，一般分配特定程序
// 端口号不可以重复，但是TCP与UDP套接字不会共用端口号，所以允许重复

// 3.2 地址信息的表示
#include <arpa/inet.h>

struct sockaddr_in serv_addr;
// struct sockaddr_in
//   {
//     __SOCKADDR_COMMON (sin_);
//     in_port_t sin_port;			/* Port number.  */
//     struct in_addr sin_addr;		/* Internet address.  */

//     /* Pad to size of `struct sockaddr'.  */
//     unsigned char sin_zero[sizeof (struct sockaddr)
// 			   - __SOCKADDR_COMMON_SIZE
// 			   - sizeof (in_port_t)
// 			   - sizeof (struct in_addr)];
//   };

// sockaddr_in.sin_family         表示地址族
// sockaddr_in.sin_port           表示16位端口号，它是以网络字节序保存
// sockaddr_in.sin_addr.s_addr    表示32位ip地址，也是以网络字节序保存

struct sockaddr ser_addr;
// struct sockaddr
//   {
//     __SOCKADDR_COMMON (sa_);	/* Common data: address family and length.  */
//     char sa_data[14];		/* Address data.  */
//   };

// bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen);
// 为什么在网络编程中bind函数传递的是sockaddr *，而我们每次都是用sockaddr_in结构体强转
// 因为sockaddr.sa_data保存的信息需要包含ip地址和端口号剩余填0，比较麻烦

// 3.3网络字节序与地址变换
// cpu向内存保存、解析数据有两种方式：
// 大端字节序（Big Endian）:高位字节存放到低位地址
// 小端字节序（Little Endian）：高位字节存放到高位地址

// intel cpu（主机字节序）采用的小端字节序
// 网络字节序 统一为大端字节序

// 字节序转换常用的api：
// unsigned short htons(unsigned short)
// unsigned short ntohs(unsigned short)
// unsigned short htonl(unsigned long)
// unsigned short ntohl(unsigned long)
// h代表host（主机）、n代表net（网络）、s代表short（2个字节）（sockaddr_in.port端口号占两字节）、l代表long（4个字节）（sockaddr_in ip地址占四字节）

// 3.4 网络地址的初始化与分配
// sockaddr_in中保存地址信息的成员为32位整数型，因此需要将IP地址转成32位整型数据,inet_addr函数提供这个功能

// #include <arpa/inet.h>

// in_addr inet_addr(const char *string)
// 成功返回32位大端序整形，失败返回INADDR_NONE

// inet_aton函数 与 inet_addr函数功能完全相同

// #include <arpa/inet.h>

// int inet_aton(const char* string, struct in_addr*addr)
// const char* string    需要转换的ip地址值
// struct in_addr*addr   保存转换结果的in_addr地址


// inet_ntoa函数与inet_aton、inet_addr函数功能相反

// #include <arpa/inet.h>
// char* inet_ntoa(struct in_addr adr);
// 成功返回转换的字符串地址，失败返回-1


// INADDR_ANY 自动获取计算机ip地址

// 127.0.0.1  回送地址（loopback address）,指计算机自身ip地址
