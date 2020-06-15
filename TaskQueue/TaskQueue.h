#include <string>
#include <vector>

struct historyEntry
{   
    int number;
    int exitNumber;
    std::string logFile;
    std::string startTime;
    std::string endTime;
    std::string time;
    std::string command;
    std::string date;

};

class TaskQueue
{
private:
    
public:
    std::vector <historyEntry> history;
    TaskQueue();
    int startTask(std::string Task);
    void historyEntryCreate(std::string Task);
    ~TaskQueue();
};


