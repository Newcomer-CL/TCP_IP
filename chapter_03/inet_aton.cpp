#include <iostream>
#include <arpa/inet.h>

int main()
{
    std::string addr = "127.232.124.79";
    struct sockaddr_in addr_inet;

    if(!inet_aton(addr.c_str(),&addr_inet.sin_addr))
    {
        std::cout << "Conversion error!\n";
    }
    else{
        std::cout<< std::hex << "Net ordered integer addr:" << addr_inet.sin_addr.s_addr <<std::endl;
    }
    return 0;
}