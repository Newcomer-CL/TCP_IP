#include <iostream>
#include <arpa/inet.h>

int main()
{
    std::string addr1 = "1.2.3.4";
    std::string addr2 = "1.2.3.256";

    unsigned long conv_addr = inet_addr(addr1.c_str());
    if(conv_addr == INADDR_NONE)
    {
        std::cout << "Error occured!\n";
        return -1;
    }
    else{
        std::cout<< std::hex << "Net ordered interger addr1:" << conv_addr << std::endl;
    }

    conv_addr = inet_addr(addr2.c_str());
        if(conv_addr == INADDR_NONE)
    {
        std::cout << "Error occured!\n";
        return -1;
    }
    else{
        std::cout << "Net ordered interger addr2:" << conv_addr << std::endl;
    }
    return 0;
}