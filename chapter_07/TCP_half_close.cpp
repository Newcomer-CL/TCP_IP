close 函数意味着完全断开，完全断开后既不能发送数据，也不能接收数据。
A、B之间基于TCP进行通信，A数据传输完了关闭了socket文件描述符，B还没发完的数据就接收不到了。
针对上述问题，“关闭部分数据交换使用的流”（half-close）应运而生。
断开部分流是指，关闭流的一半，不能接收，只能发送，或者只能接收，不能发送。

shutdown函数：

#include <sys/socket.h>

int shutdown(int sock, int howto);
成功返回0，失败返回-1；
sock    需要断开的套接字描述符
howto   传递断开方式信息
        SHUT_RD(断开输入流)
        SHUT_WR（断开输出流）
        SHUT_RDWR（同时断开读写）

断开输出流时会给对方主机传输EOF