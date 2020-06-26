#include <string>
#include <vector>
#include <iostream>

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
    
    TaskQueue();
    int startTask(std::string Task, std::string logName);
    void historyEntryCreate(std::string Task);
    ~TaskQueue();
};


