#include <string>
#include <vector>
#include <iostream>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <memory>
struct historyEntry
{   
    historyEntry();
    int number;
    int exitNumber;

    std::string *logFile;
    std::string *startTime;
    std::string *endTime;
    std::string *duration;
    std::string *command;
    std::string *date;
    std::string *state;
    ~historyEntry();
};

using namespace boost::interprocess;
typedef allocator<historyEntry, managed_shared_memory::segment_manager>  ShmemAllocator;
typedef std::vector<historyEntry, ShmemAllocator> ShmVector;

class TaskQueue
{
private:
    
public:
    void saveOutputToFile(std::string Logname);
    std::vector <historyEntry> history;
    void lock();
    void unlock();
    TaskQueue();
    int startTask(std::string Task, historyEntry &entry);
    void historyEntryCreate(std::string Task);
    ~TaskQueue();
};