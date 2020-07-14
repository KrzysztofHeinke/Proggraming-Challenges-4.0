#include <string>
#include <iostream>
#include <mutex>
#include "SingletonProcess.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <boost/interprocess/managed_shared_memory.hpp>

using namespace boost::interprocess;

typedef allocator<historyEntry, managed_shared_memory::segment_manager>  ShmemAllocator;
typedef std::vector<historyEntry, ShmemAllocator> ShmVector;

void printHistory(SingletonProcess &singleton)
{
  system("echo \"Task number, exit status, Log localization, date, command, status\" > /tmp/TaskHistory.txt");
  for ( auto it = singleton.shared_memory_history->begin(); it != singleton.shared_memory_history->end(); ++it)
  {
    std::cout << (*it).number << " " << (*it).exitNumber << " " << *(*it).logFile << " " << *(*it).date << " " << *(*it).command << " " << *(*it).state << " " << std::endl;
    system((("echo \"" + std::to_string((*it).number)) + " " + std::to_string((*it).exitNumber) + " " + *(*it).logFile + " " + *(*it).date + " " + *(*it).command + " " + *(*it).state + "\" >> /tmp/TaskHistory.txt" ).c_str());
  }
}

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
      singleton.connectToSocket(command);
      
      return 0;
    }
    
    while (true)
    {
      data = singleton.listenForTask();
      if ( data.length() <= 1)
      {
        printHistory(singleton);
      }
      if ( data.length() == 3 && !data.find("-k"))
      {
        std::cout << "TaskQueue killed" << std::endl;
        return -1;
      }
      if (data.length() > 0)
      {     
        singleton.queue->historyEntryCreate(data);
        printHistory(singleton);
      }
    }
    
    return 0;
}

