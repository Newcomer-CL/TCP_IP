DNS(Domain Name System, 域名系统)
DNS是对IP地址和域名进行相互转化的系统，其核心是DNS服务器。

域名是赋予服务器端的虚拟地址，而非实际地址。

客户端可以通过ip地址或者域名访问目的地址，如：
通过ip地址222.122.195.5或者域名www.naver.com都可以访问naver主页。

DNS是如何将域名转换为ip地址呢？
    所有的计算机中都记录着默认DNS服务器地址，就是通过这个默认DNS服务器获取该域名对应的IP地址信息。
    如果默认的DNS服务器地址无法解析主机询问的域名IP地址，会向上级DNS服务器询问。
    通过这种方式逐级向上传递信息，到达顶级DNS服务器--根服务器时，他知道向哪个DNS服务器询问。

为什么要使用域名:
    因为IP地址发生变更的概率比域名更换的概率要高，所以利用IP地址编写程序并非上策，
    一旦注册域名可能永久不变，因此利用域名更好一些

利用域名获取ip地址
#include <netdb.h>

struct hostent *gethostbyname(const char *name);
成功返回hostnet结构体地址，失败返回NULL指针

/* Description of data base entry for a single host.  */
struct hostent
{
  char *h_name;			/* Official name of host.  */   // 官方域名
  char **h_aliases;		/* Alias list.  */              //可以通过多个域名访问同一主页，查询其他域名
  int h_addrtype;		/* Host address type.  */       // 地址族 IPv4/IPv6
  int h_length;			/* Length of address.  */       //IP地址长度 IPv4，4字节，IPv6，16字节
  char **h_addr_list;		/* List of addresses from name server.  */   //通过此变量以整数形式保存域名对应的IP地址
#ifdef __USE_MISC
# define	h_addr	h_addr_list[0] /* Address, for backward compatibility.*/
#endif
};


利用IP地址获取域名

#include <netdb.h>

struct hostent *gethostbyaddr(const void *addr,
                                     socklen_t len, int type);
成功返回hostent结构体变量值，失败返回NULL指针。
addr   含有IP地址信息的in_addr结构体指针
len    像第一个参数传递的地址信息的字节数，IPv4为4，IPv6为16.
family 传递地址族信息，IPv4时为AF_INET，IPv6为AF_INET6
