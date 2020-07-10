#include <string>
#include <iostream>
#include <mutex>
#include "SingletonProcess.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <boost/interprocess/managed_shared_memory.hpp>

using namespace boost::interprocess;

void printHistory(SingletonProcess &singleton)
{
  system("echo \"Task number, exit status, Log localization, date, command, status\" > /tmp/TaskHistory.txt");
  for (auto it = singleton.queue->history.begin(); it != singleton.queue->history.end(); ++it)
  {
    if ((singleton.queue->history.size()) != 0)
    {
      system(("echo \"" + it->printEntry() + "\" >> /tmp/TaskHistory.txt").c_str());
      std::cout << it->printEntry() << std::endl;
    }
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
      if (data.length() > 0)
      {     
        singleton.queue->historyEntryCreate(data);
        printHistory(singleton);
        for ( auto it = singleton.shared_memory_history->begin(); it != singleton.shared_memory_history->end(); ++it)
        {
          std::cout << *it << std::endl;
        }
      }
      else if ( data.length() == 0 )
      {
        // printHistory(singleton);
      }
      
    }
    
    return 0;
}

