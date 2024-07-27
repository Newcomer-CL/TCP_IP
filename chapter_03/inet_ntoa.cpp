#include <iostream>
#include <arpa/inet.h>
#include <string.h>

int main()
{
    struct sockaddr_in addr1,addr2;
    char *str_ptr;
    char str_arr[20];

    addr1.sin_addr.s_addr = htonl(0x1020304);
    addr2.sin_addr.s_addr = htonl(0x1010101);
    str_ptr = inet_ntoa(addr1.sin_addr);
    strcpy(str_arr,str_ptr);

    std::cout << "Dotted-Decimal notation1:" << str_ptr << std::endl;

    inet_ntoa(addr2.sin_addr);
    std::cout << "Dotted-Decimal notation2:" << str_ptr << std::endl;
    std::cout << "Dotted-Decimal notation3:" << str_arr << std::endl;
    return 0;
}