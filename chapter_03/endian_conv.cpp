#include <iostream>
#include <arpa/inet.h>

int main()
{
    unsigned short host_port = 0x1234;
    unsigned short net_port = {};
    unsigned long host_addr = 0x12345678;
    unsigned long net_addr = {};

    net_port = htons(host_port);
    net_addr = htonl(host_addr);

    std::cout << "Host ordered port:" << host_port << std::endl;
    std::cout << "Net ordered port:" << net_port << std::endl;
    std::cout << "Host ordered address:" << host_addr << std::endl;
    std::cout << "Net ordered address:" << net_addr << std::endl;
    return 0;
}