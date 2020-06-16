#include <string>
#include <vector>
#include <iostream>

struct historyEntry
{   
    void printEntry();
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
    std::vector <historyEntry> history;
    TaskQueue();
    int startTask(std::string Task, int taskNumber);
    void historyEntryCreate(std::string Task);
    ~TaskQueue();
};


