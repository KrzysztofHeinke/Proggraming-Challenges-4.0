#include <iostream>
#include <sys/socket.h>
#include "PortScanner.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

PortScanner::PortScanner(std::string ipAddress, std::string port)
{
    this->ipAddress = ipAddress;
    this->port = port;
    this->addrInfo.ai_family = AF_UNSPEC;
    this->addrInfo.ai_socktype = SOCK_DGRAM;
    this->addrInfo.ai_flags = 0;
    this->addrInfo.ai_protocol = 0;
    this->s = getaddrinfo(this->ipAddress.c_str(), this->port.c_str(), &this->addrInfo, &this->result);
    this->sfd = socket(this->result->ai_family,this->result->ai_socktype,this->result->ai_protocol);
}
void PortScanner::isOpen()
{
    if (connect(this->sfd, this->result->ai_addr, this->result->ai_addrlen) != -1)
    {
        std::cout << "Open port -> " << this->port << std::endl;
//        getsockname(sfd,this->result->ai_addr,&this->result->ai_addrlen);
    }
    else
    {
        std::cout << "Failed connect to port -> " << this->port << std::endl;
    }
}
PortScanner::~PortScanner()
{
    freeaddrinfo(this->result);
}
