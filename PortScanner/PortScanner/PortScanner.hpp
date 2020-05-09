#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

class PortScanner
{
    private:
        std::string port;
        std::string ipAddress;
        struct addrinfo addrInfo;
        struct addrinfo *result;
        int s, sfd;

    public:
        PortScanner(std::string ipAddress, std::string port);
        void isOpen();
        ~PortScanner();
};

