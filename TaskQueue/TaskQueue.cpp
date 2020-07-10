#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <random>
#include "TaskQueue.h"
#include <chrono>
#include <sstream>
#include <stdio.h>
#include <fcntl.h>
#include <fstream>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>

using namespace boost::interprocess;

void TaskQueue::saveOutputToFile(std::string LogName)
{
  std::ofstream outfile;
  outfile.open(LogName);
}

int TaskQueue::startTask(std::string Task, historyEntry &entry)
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

    Task = Task + " > " + entry.logFile;
    int return_value = system(Task.c_str());
    managed_shared_memory segment(open_only, "TaskQueueuShm");
    ShmVector *myvector = segment.find<ShmVector>("SharedVector").first;
    for (auto it = myvector->begin(); it != myvector->end(); it++)
    {
      // std::cout << *it << std::endl;
      ++(*it);
    }
    segment.destroy<ShmVector>("MyVector");
    exit(return_value);
  }
  else
  {
    std::cout << "Parent process. My process id = " << getpid() << std::endl;
    std::cout << "Parent process. Value returned by fork() = " << pid << std::endl;
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
void TaskQueue::historyEntryCreate(std::string Task)
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
    history.push_back(entry);
    startTask(Task, entry);
}


std::string historyEntry::printEntry()
{
  return (std::to_string(this->number) + " " + std::to_string(this->exitNumber) + " " + this->logFile + " " + 
  this->startTime + " " + this->endTime + " " + this->time + " " + 
  this->command + " " + this->date + " " + this->state );
  
}


TaskQueue::~TaskQueue()
{
}
void TaskQueue::lock()
{
  while (mkdir("/tmp/LockTaskQueue",  S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1)
  {
    usleep(50);
  }
}
void TaskQueue::unlock()
{
  rmdir("/tmp/LockTaskQueue");
}
