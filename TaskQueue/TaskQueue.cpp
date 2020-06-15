#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <random>
#include "TaskQueue.h"
#include <chrono>

int TaskQueue::startTask(std::string Task)
{
        
  pid_t pid;
  std::cout << "My process id = " << getpid() << std::endl;
  pid = fork();
    
  if ( pid == -1 )
  {
      std::cout << "Error in fork";
  }
  else if ( pid == 0 )
  {
    std::cout << "Child process: My process id = " << getpid() << std::endl;
    std::cout << "Child process: Value returned by fork() = " << pid << std::endl;
    int return_value = system(Task.c_str());
    if ( return_value != 0 )
    {
      exit(return_value);
    }
  
    return return_value;
  }
  else
  {
    std::cout << "Parent process. My process id = " << getpid() << std::endl;
    std::cout << "Parent process. Value returned by fork() = " << pid << std::endl;
  }
  if (wait(NULL) == -1)
  {
    std::cout << "Error in fork";
  }
   
 
  return 0;
}

TaskQueue::TaskQueue()
{
    srand(time(NULL));
}
void TaskQueue::historyEntryCreate(std::string Task)
{
   historyEntry entry;
   constexpr int logLetterAmount = 8;
   char letters[] = {'a','b','c','d','e','f',
   'g','h','i','j','k','l','m','n','o','p','q',
   'r','s','t','u','v','w','x','y','z'};

    std::string logName;

    for (int i = 0; i < logLetterAmount; i++)
    {
        logName.append(std::string(1, letters[rand() % (sizeof(letters)/sizeof(char))]));
    }
    entry.number = history.size() + 1;
    entry.command = Task;
    //entry.startTime = std::chrono::system_clock::now();
    startTask(Task);
    std::cout << logName << std::endl;
}

TaskQueue::~TaskQueue()
{
}