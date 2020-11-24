#include <string>
#include <iostream>
#include "SingletonProcess.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/thread.hpp>
#include <memory>
using namespace boost::interprocess;

typedef allocator<historyEntry, managed_shared_memory::segment_manager>  ShmemAllocator;
typedef std::vector<historyEntry, ShmemAllocator> ShmVector;


int main(int argc, char * argv[])
{
   std::string data;
   SingletonProcess singleton(5555);
   if (!singleton())
   {
     std::string command;
     for (int i = 1; i < argc; i++)
     {
       command.append(argv[i]);
       command.append(" ");
     }
     if (command.length() == 0)
     {
       system("cat /tmp/TaskHistory.txt");
     }
     else
     {
       singleton.connectToSocket(command);
     }
     return 0;
   }
   while (true)
   {
     data = singleton.listenForTask();
     if ( data.length() == 3 && !data.find("-k"))
     {
       std::cout << "TaskQueue killed" << std::endl;
       return -1;
     }
     if (data.length() > 0)
     {     
       singleton.queue->historyEntryCreate(data);
     }
   }
   
   return 0;
}