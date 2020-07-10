#include <netinet/in.h>
#include <unistd.h> 
#include <cstring>
#include <iostream>
#include "SingletonProcess.h"
#include <string>
#include <sys/ipc.h>
#include <sys/shm.h>

SingletonProcess::SingletonProcess(uint16_t port0)
  : socket_fd(-1), rc(1), port(port0)
    {
    }

SingletonProcess::~SingletonProcess()
{
    if (socket_fd != -1)
    {
      close(socket_fd);
      if(is_singleton)
      {
        shared_memory_object::remove("TaskQueueuShm");
        delete segment;
        delete alloc_inst;
      }
    }
    delete queue;
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
    queue = new TaskQueue;
    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        throw std::runtime_error(std::string("Could not create socket: ") +  strerror(errno));
    }
    else
    {   
      std::cout << "HEJKTA2" << std::endl;
      struct sockaddr_in name;
      name.sin_family = AF_INET;
      name.sin_port = htons (port);
      name.sin_addr.s_addr = htonl (INADDR_ANY);
      rc = bind (socket_fd, (struct sockaddr *) &name, sizeof (name));
    }
  }
  is_singleton = (socket_fd != -1 && rc == 0);
  if (is_singleton)
  {
    shared_memory_object::remove("TaskQueueuShm");
    std::cout << "Hejka" << std::endl;
    segment = new managed_shared_memory(create_only, "TaskQueueuShm", 65536);
    alloc_inst = new ShmemAllocator (segment->get_segment_manager());
    shared_memory_history = segment->construct<ShmVector>("SharedVector")(*alloc_inst);
    for (int i = 0; i < 10; ++i)
    {
      shared_memory_history->push_back(i);
    }
  }
  return is_singleton;
}
void SingletonProcess::connectToSocket(std::string task)
{
  struct sockaddr_in name;
  name.sin_family = AF_INET;
  name.sin_port = htons (port);
  name.sin_addr.s_addr = htonl (INADDR_ANY);
  rc = connect(socket_fd, (struct sockaddr *) &name, sizeof (name));
  std::cout << send(socket_fd, task.c_str() , strlen(task.c_str()) , 0 ) << std::endl;
}
std::string SingletonProcess::listenForTask()
{
  struct sockaddr_in name;
  name.sin_family = AF_INET;
  name.sin_port = htons (port);
  name.sin_addr.s_addr = htonl (INADDR_ANY);
  listen(socket_fd, 3);
  accept(socket_fd, (struct sockaddr *)&name, (socklen_t*)&name );
  char buffer[1024] = {0};
  std::string data;
  try
  {
    data = read( socket_fd , buffer, 1024); 
  }
  catch(const std::exception& e)
  {
    std::cout << "Nothing to read from socket" << std::endl;
  }
  return buffer;
}
