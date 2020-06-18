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
    void saveOutputToFile(std::string Logname);
    std::vector <historyEntry> history;
    TaskQueue();
    int startTask(std::string Task, std::string logName);
    void historyEntryCreate(std::string Task);
    ~TaskQueue();
};


