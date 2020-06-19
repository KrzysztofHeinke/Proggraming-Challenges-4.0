#include <string>
#include <iostream>
#include "SingletonProcess.h"
void printHistory(SingletonProcess &singleton)
{
  system("echo \"Task number, exit status, Log localization, date, command, status\" > /tmp/TaskHistory.txt");
  for (auto it = singleton.queue->history.begin(); it != singleton.queue->history.end(); ++it)
  {
    system(("echo \"" + it->printEntry() + "\" >> /tmp/TaskHistory.txt").c_str());
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
      sleep(1);
      data = singleton.listenForTask();
      if (data.length() > 0)
      {
        std::cout << data << std::endl;
        singleton.queue->historyEntryCreate(data);
        printHistory(singleton);
      }
      else if ( data.length() == 0 )
      {
        printHistory(singleton);
      }
      
    }
    
    return 0;
}

