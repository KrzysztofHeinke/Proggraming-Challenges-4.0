#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <random>
#include "TaskQueue.h"
#include <chrono>
#include <sstream>

int TaskQueue::startTask(std::string Task, int taskNumber)
{
  
  pid_t pid;
  std::cout << "My process id = " << getpid() << std::endl;
  // history[taskNumber].state = "running";
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
      history[taskNumber].exitNumber = return_value;
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
void randomLogName(std::string &logName)
{
    constexpr int logLetterAmount = 8;
    char letters[] = {'a','b','c','d','e','f',
    'g','h','i','j','k','l','m','n','o','p','q',
    'r','s','t','u','v','w','x','y','z'};

    for (int i = 0; i < logLetterAmount; i++)
    {
        logName.append(std::string(1, letters[rand() % (sizeof(letters)/sizeof(char))]));
    }

}
void TaskQueue::  historyEntryCreate(std::string Task)
{
    historyEntry entry;
    std::string logName;
    randomLogName(logName);

    std::stringstream ss;
    auto time = std::chrono::system_clock::now();
    auto time_ = std::chrono::system_clock::to_time_t(time);
    ss << time_ ;
    entry.number = history.size() + 1;
    entry.command = Task;
    entry.startTime = ss.str();
    entry.state = "queued";
    entry.logFile = "/tmp/" + logName + ".out";
    startTask(Task, entry.number);
    history.push_back(entry);
}

void historyEntry::printEntry()
{
    std::cout << this->number<< " " ;
    std::cout << this->exitNumber << " ";
    std::cout << this->logFile << " ";
    std::cout << this->startTime << " ";
    std::cout << this->endTime << " ";
    std::cout << this->time << " ";
    std::cout << this->command << " ";
    std::cout << this->date << " ";
    std::cout << this->state << " ";
    std::cout << std::endl;
}

TaskQueue::~TaskQueue()
{
}