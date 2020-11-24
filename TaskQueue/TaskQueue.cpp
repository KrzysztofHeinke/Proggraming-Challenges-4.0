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
#include <boost/thread.hpp>
#include <memory>

using namespace boost::interprocess;

void TaskQueue::printHistory()
{
    lock();
    managed_shared_memory segment(open_only, "TaskQueueuShm");
    std::unique_ptr<ShmVector*> myvector = std::make_unique<ShmVector*>(segment.find<ShmVector>("SharedVector").first);
    system("echo \"Task number, exit status, Log localization, date, command, status\" > /tmp/TaskHistory.txt");
    if (! (*myvector)->empty())
    {
      for ( ShmVector::const_iterator it = (*myvector)->begin(); it != (*myvector)->end(); ++it)
      {
        // #define DEBUG
        #ifdef DEBUG
        std::cout << (*it).number << " " << (*it).exitNumber << " " << *(*it).logFile << " " << *(*it).date << " " << *(*it).command << " " << *(*it).state << " " << std::endl;
        #endif
        system((("echo \"" + std::to_string((*it).number)) + " " + std::to_string((*it).exitNumber) + " " + *(*it).logFile + " " + *(*it).date + " " + *(*it).command + " " + *(*it).state + "\" >> /tmp/TaskHistory.txt" ).c_str());
      }
    }
    unlock();
}

historyEntry::historyEntry()
{
  std::shared_ptr<std::string> logFile = nullptr;
  std::shared_ptr<std::string> startTime = nullptr;
  std::shared_ptr<std::string> endTime = nullptr;
  std::shared_ptr<std::string> duration = nullptr;
  std::shared_ptr<std::string> command = nullptr;
  std::shared_ptr<std::string> date = nullptr;
  std::shared_ptr<std::string> state = nullptr;
}

historyEntry::~historyEntry()
{ 
  #ifdef DEBUG
  std::cout << "Zniszczono wpis" << std::endl;
  #endif
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
  std::shared_ptr<std::string> state_finished = std::make_shared<std::string>("finished");
  std::shared_ptr<std::string> state_running = std::make_shared<std::string>("running");
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
    printHistory();
    int return_value = system(Task.c_str());
    (*myvector)[entry.number].exitNumber = return_value;
    (*myvector)[entry.number].state = state_finished;
    myvector = nullptr;
    delete myvector;
    exit(return_value);
  }
  else
  {
    printHistory();
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
  entry.command = std::make_shared<std::string>(Task);
  entry.startTime = std::make_shared<std::string>(ss.str());
  entry.endTime = std::make_shared<std::string>("not finished");
  entry.duration = std::make_shared<std::string>("not finished");
  entry.state = std::make_shared<std::string>("queued");
  entry.date = std::make_shared<std::string>("");
  entry.logFile = std::make_shared<std::string>( "/tmp/" + logName + ".out");
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
