#include <netinet/in.h>
#include <unistd.h> 
#include <cstring>
#include <iostream>
#include "TaskQueue.h"
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

using namespace boost::interprocess;
typedef allocator<historyEntry, managed_shared_memory::segment_manager>  ShmemAllocator;
typedef std::vector<historyEntry, ShmemAllocator> ShmVector;


class SingletonProcess
{
public:
    std::unique_ptr<managed_shared_memory> segment;
    std::shared_ptr<const ShmemAllocator> alloc_inst;
    ShmVector* shared_memory_history;

    SingletonProcess(uint16_t port0);
    ~SingletonProcess();
    std::string GetLockFileName();
    void connectToSocket(std::string task);
    std::string listenForTask();
    bool operator()();
    
    std::unique_ptr<TaskQueue> queue;
private:
    bool is_singleton;
    int socket_fd = -1;
    int rc;
    uint16_t port;
};