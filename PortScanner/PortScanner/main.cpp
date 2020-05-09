#include <iostream>
#include <string>
#include "PortScanner.hpp"
#include <unistd.h>

using namespace std;

int main()
{
    unsigned short maxNumberOfPorts= -1; //means 65535

    cout << maxNumberOfPorts << endl;
    for(int i = 0; i < maxNumberOfPorts;i++)
    {
        cout << "Port number : " << i << endl;
        PortScanner a("127.0.0.1",to_string(i));
        sleep(1);
        a.isOpen();

    }
    return 0;
}
