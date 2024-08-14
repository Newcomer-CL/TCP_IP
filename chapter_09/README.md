### 套接字的多种选项

#### 9.1套接字可选项和I/O缓冲大小

##### 套接字多种可选项

​		套接字可选项和I/O缓存，我们之前写的程序都是创建好套接字后直接使用的，此时通过默认的套接字特性进行通信，但是套接字存在可选项去设置的。

![image-20240814180540893](C:\Users\Wangjn\AppData\Roaming\Typora\typora-user-images\image-20240814180540893.png)



##### getsockopt & setsockopt

​		我们可以对套接字可选项进行读取（Get）和设置（Set）



读取套接字可选项函数：

\#include <sys/socket.h>



int getsockopt(int sockfd, int level, int optname,

​           void *optval, socklen_t *optlen);

成功返回0，失败返回-1。

sockfd    用于查看选项套接字的文件描述符

level    要查看的可选项的协议层

optname   要查看的可选项名

optval    保存查看结果的缓冲地址值

optlen    像第四个参数optval传递的缓冲大小



设置（更改）套接字可选项函数：

\#include <sys/socket.h>



int getsockopt(int sockfd, int level, int optname,

​           void *optval, socklen_t *optlen);

成功返回0，失败返回-1。

sock     用于更改可选项的套接字描述符

level    要更改的可选项协议层

optname   要更改的可选项名

optval    保存要更改的选项信息的缓冲地址值

optlen    向第四个参数optval传递的可选项信息的字节数



#### 9.2 SO_REUSEADDR

​		之前的程序中，客户端与服务端相互交互，每次都是客户端发完消息后，客户端先请求断开连接，所以没有发生特别的情况。重新运行服务器也没有什么问题。

​		但是如果在服务端与客户端已经建立连接的状态下，强制关闭服务器，那么服务端重新运行将会产生问题。

​		如果使用同一端口号将输出 "bind() error" 消息，并且无法再次运行.但在这种情况下，再过大约3min即可重新运行服务器端。


##### Time-wait状态

<img src="C:\Users\Wangjn\AppData\Roaming\Typora\typora-user-images\image-20240813110150194.png" alt="image-20240813110150194" style="zoom:50%;"   />



​		假设主机A是服务器端，A向B发送FIN消息，故可以想象成服务器端在控制台输入CTRL+C。但问题是，套接字经过四次握手后并非立即消除，而是要经过一段时间的Time-wait状态。当然，只有先断开连接的（先发送FIN消息的）主机才经过Time-wait状态。套接字处于Time-wait过程时，相应的端口是正在使用的状态。因此，就像之前验证过的，bind函数调用过程会报错。

​		客户端先发送FIN消息，客户端也有Time-wait状态，但无需考虑客户端的Time-wait状态。因为客户端的套接字的端口号、IP都是在调用connect函数时由系统自动分配的。客户端每次运行程序都会动态分配端口号。

​		综上，主要的问题是因为存在Time-wait机制导致服务端的端口号没有被释放，再次启动服务端的程序（使用的同一端口号）就会发生bind error。

​		为什么会有Time-wait状态呢？假设主机A向主机B发送ACK消息（SEQ 5001、ACK 7052）后立即消除套接字。但最后这条ACK消息在传输过程中丢失，未能传给主机B。主机B会认为自己之前发送的FIN消息未能抵达主机A，继而试图重传。但此时主机A已是完全终止，因此主机B将一直无法收到主机A最后传来的ACK消息。如果主机A处于Time-wait状态，那么主机B重传FIN消息后，主机A会向主机B重传最后的ACK消息，主机B也可以正常结束。



##### 地址再分配

​		Time-wait看似重要但不一定讨人喜欢。假设系统发生故障从而紧急停止，这时需要快速重启服务器以提供服务，但因处于Time-wait状态而必须等待几分钟。

​		解决方法就是在套接字的可选项中更改SO_REUSEADDR的状态。适当调整参数，可将Time-wait状态下的套接字端口号重新分配给新的套接字。SO_REUSEADDR的默认值为0（假），这就意味着无法重新分配Time-wait状态下的套接字端口号。因此将这个值改为1（真）即可。具体代码如下：

```c++
#include <sys/socket.h>

int serv_fd = socket(PF_INET,SOCK_STREAM,0);
int option = 0,strlen = 0;
socklen_t optlen = 0;
optlen = sizeof(option);
option = TRUE;
setsockopt(serv_fd,SOL_SOCKET,SO_REUSEADDR,(void*)&option,optlen)
```



#### TCP_NODELAY	

##### Nagle算法

​		为了防止因数据包过多而发生网络过载，Nagle算法在1984年诞生了。它应用于TCP层，非常简单。

![image-20240813121939945](C:\Users\Wangjn\AppData\Roaming\Typora\typora-user-images\image-20240813121939945.png)



​		如上图所示，只有收到前一数据的ACK消息时，Nagle算法才发送下一数据。

​		TCP套接字默认使用Nagle算法交换数据，因此最大限度的进行缓冲，直到接收到ACK。

​		一般情况下，不适用Nagle算法可以提高传输速度。但如果无条件放弃使用Nagle算法，就会增加过多的网络流量，反而会影响传输速度。



##### 禁用Nagle算法

​		“大文件数据”应禁用Nagle算法。换言之，如果有必要，就禁用Nagle算法。

​		禁用的方法非常简单。只需要将套接字选项TCP_NODELAY改为1（真）即可。

```c++
int opt_val = 1;
setsockopt(sock,IPPROTO_TCP,TCP_NODELAY,(void*)&opt_val,sizeof(opt_val));
```

​	

