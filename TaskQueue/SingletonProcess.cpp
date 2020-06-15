#include <netinet/in.h>
#include <unistd.h> 
#include <cstring>
#include <iostream>
#include "SingletonProcess.h"
#include <string>

SingletonProcess::SingletonProcess(uint16_t port0)
  : socket_fd(-1), rc(1), port(port0)
    {
    }

    SingletonProcess::~SingletonProcess()
    {
        if (socket_fd != -1)
        {
            close(socket_fd);
        }
    }

    std::string SingletonProcess::GetLockFileName()
    {
        return "port " + std::to_string(port);
    }
    bool SingletonProcess::operator()()
    {
        if (socket_fd == -1 || rc)
        {
            socket_fd = -1;
            rc = 1;

            if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
            {
                throw std::runtime_error(std::string("Could not create socket: ") +  strerror(errno));
            }
            else
            {
                struct sockaddr_in name;
                name.sin_family = AF_INET;
                name.sin_port = htons (port);
                name.sin_addr.s_addr = htonl (INADDR_ANY);
                rc = bind (socket_fd, (struct sockaddr *) &name, sizeof (name));
            }
        }
        return (socket_fd != -1 && rc == 0);
    }
    void SingletonProcess::connectToSocket(std::string task)
    {
      struct sockaddr_in name;
      name.sin_family = AF_INET;
      name.sin_port = htons (port);
      name.sin_addr.s_addr = htonl (INADDR_ANY);
      rc = connect(socket_fd, (struct sockaddr *) &name, sizeof (name));
      send(socket_fd, task.c_str() , strlen(task.c_str()) , 0 );
      std::cout << "HELLO FROM SOCKET" << task << std::endl;
    }
    std::string SingletonProcess::listenForTask()
    {
      struct sockaddr_in name;
      name.sin_family = AF_INET;
      name.sin_port = htons (port);
      name.sin_addr.s_addr = htonl (INADDR_ANY);
      listen(socket_fd, 3);
      int new_socket = accept(socket_fd, (struct sockaddr *)&name, (socklen_t*)&name );
      char buffer[1024] = {0};
      std::string data;
      try
      {
        data = read( new_socket , buffer, 1024); 
      }
      catch(const std::exception& e)
      {
        data = "";
      }
      
      return buffer;
    }