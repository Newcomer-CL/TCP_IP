#include <netdb.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <iostream>
#include <string.h>

int main(int argc, char* argv[])
{
    if(argc!=2)
    {
        std::cout << "Usage:" << argv[0] << "<addr>\n";
        return -1;
    }
    struct hostent *host = nullptr;
    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    host = gethostbyaddr(reinterpret_cast<const char*>(&addr.sin_addr),4,AF_INET);
    if(host == nullptr)
    {
        std::cout << "gethostbyaddr error!\n";
        if (h_errno == HOST_NOT_FOUND) {
            std::cout << "The specified host is unknown." << std::endl;
        } else if (h_errno == NO_DATA) {
            std::cout << "The requested name is valid but does not have an IP address." << std::endl;
        } else if (h_errno == NO_RECOVERY) {
            std::cout << "A non-recoverable name server error occurred." << std::endl;
        } else if (h_errno == TRY_AGAIN) {
            std::cout << "A temporary error occurred on an authoritative name server. Try again later." << std::endl;
        }
        return -1;
    }

    for(int i = 0;host->h_aliases[i];i++)
    {
        std::cout << "Aliases " << i+1 << ":" << host->h_aliases[i] << std::endl;
    }

    std::cout << "Address type:" << host->h_addrtype << std::endl;

    for(int i = 0;host->h_addr_list[i];i++)
    {
        // host->h_addr_list[i]指向字符串指针数组
        // 该数组中的元素实际指向的是in_addr结构体变量地址而非字符串。
        std::cout << "IP addr " << i+1 << ":" << inet_ntoa(*(struct in_addr*)host->h_addr_list[i]) << std::endl;
    }
    return 0;
}