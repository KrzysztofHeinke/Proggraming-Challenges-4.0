#include <string>
#include <iostream>
#include "SingletonProcess.h"


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
      singleton.connectToSocket(command);
      return 1;
    }
   
    while (true)
    {
      sleep(1);
      data = singleton.listenForTask();
      if (data.length() > 0)
      {
        std::cout << data << std::endl;
        singleton.queue->historyEntryCreate(data);
      }
      else if ( data.length() == 0 )
      {
        std::cout << "size of queue " << singleton.queue->history.size() << std::endl;
        for (auto it = singleton.queue->history.begin(); it != singleton.queue->history.end(); ++it)
        {
          it->printEntry();
        }
      }
      
    }
    
    return 0;
}

