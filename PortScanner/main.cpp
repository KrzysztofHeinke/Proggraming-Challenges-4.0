#include <iostream>
#include <string>
#include "PortScanner.hpp"
#include <unistd.h>

using namespace std;

int main()
{
    unsigned short maxNumberOfPorts= -1; //means 65535
    std::string ipAddress = "127.0.0.1";
    for(int i = 0; i < maxNumberOfPorts;i++)
    {
        PortScanner a(ipAddress, to_string(i));
        sleep(1);
        a.isOpen();

    }
    return 0;
}
