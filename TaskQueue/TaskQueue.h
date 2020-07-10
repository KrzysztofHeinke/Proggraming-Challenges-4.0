#include <string>
#include <vector>
#include <iostream>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

using namespace boost::interprocess;
typedef allocator<int, managed_shared_memory::segment_manager>  ShmemAllocator;
typedef std::vector<int, ShmemAllocator> ShmVector;

struct historyEntry
{   
    std::string printEntry();
    int number;
    int exitNumber;
    std::string logFile;
    std::string startTime;
    std::string endTime;
    std::string time;
    std::string command;
    std::string date;
    std::string state;
};

class TaskQueue
{
private:
    
public:
    void saveOutputToFile(std::string Logname);
    std::vector <historyEntry> history;
    std::vector <historyEntry> queued;
    std::vector <historyEntry> finished;
    void lock();
    void unlock();
    TaskQueue();
    int startTask(std::string Task, historyEntry &entry);
    void historyEntryCreate(std::string Task);
    ~TaskQueue();
};


