#include <netdb.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <iostream>

int main(int argc, char* argv[])
{
    if(argc!=2)
    {
        std::cout << "Usage:" << argv[0] << "<addr>\n";
        return -1;
    }
    struct hostent *host = nullptr;
    host = gethostbyname(argv[1]);
    if(host == nullptr)
    {
        std::cout << "gethostbyname error!\n";
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