#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <random>
#include <chrono>
#include <sstream>
#include <stdio.h>
#include <fcntl.h>
#include <fstream>
#include <sys/stat.h>
#include "TaskQueue.h"

using namespace boost::interprocess;

historyEntry::historyEntry()
{
  std::string *logFile = nullptr;
  std::string *startTime = nullptr;
  std::string *endTime = nullptr;
  std::string *duration = nullptr;
  std::string *command = nullptr;
  std::string *date = nullptr;
  std::string *state = nullptr;
}

historyEntry::~historyEntry()
{
  delete logFile;
  delete startTime;
  delete endTime;
  delete duration;
  delete command;
  delete date;
  delete state;
}

void TaskQueue::saveOutputToFile(std::string LogName)
{
  std::ofstream outfile;
  outfile.open(LogName);
}

int TaskQueue::startTask(std::string Task, historyEntry &entry)
{
  #ifdef DEBUG
  std::cout << "My process id = " << getpid() << std::endl;
  #endif
  std::string *state_finished = new std::string("finished");
  std::string *state_running = new std::string("running");
  pid_t pid = fork();

  if ( pid == -1 )
  {
    std::cout << "Error in fork";
  }
  else if ( pid == 0 )
  {               
    #ifdef DEBUG                   
    std::cout << "Child process: My process id = " << getpid() << std::endl;
    std::cout << "Child process: Value returned by fork() = " << pid << std::endl;
    #endif
    Task = Task + " > " + *entry.logFile;
    managed_shared_memory segment(open_only, "TaskQueueuShm");
    ShmVector *myvector = segment.find<ShmVector>("SharedVector").first;
    while( true )
    {
      if ( myvector->size() == 1)
      {
        break;
      }
      if ( *(*myvector)[entry.number - 1].state == "finished")
      {
        break;
      }
    }
  
    (*myvector)[entry.number].state = state_running;
    //Task running
    int return_value = system(Task.c_str());
    (*myvector)[entry.number].exitNumber = return_value;
    (*myvector)[entry.number].state = state_finished;
    exit(return_value);
  }
  else
  {
    #ifdef DEBUG
    std::cout << "Parent process. My process id = " << getpid() << std::endl;
    std::cout << "Parent process. Value returned by fork() = " << pid << std::endl;
    #endif
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
  entry.number = history.size();
  entry.command = new std::string(Task);
  entry.startTime = new std::string(ss.str());
  entry.endTime = new std::string("not finished");
  entry.duration = new std::string("not finished");
  entry.state = new std::string("queued");
  entry.date = new std::string("");
  entry.logFile = new std::string( "/tmp/" + logName + ".out");
  history.push_back(entry);
  
  managed_shared_memory segment(open_only, "TaskQueueuShm");
  ShmVector *myvector = segment.find<ShmVector>("SharedVector").first;
  myvector->push_back(entry);
  startTask(Task, entry);
}

TaskQueue::~TaskQueue()
{
  for (auto it = history.begin(); it != history.end(); ++it)
  {
    it->~historyEntry();
  }
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
