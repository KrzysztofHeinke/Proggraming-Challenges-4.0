#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "SingletonProcess.h"

using namespace std;
int startTask(std::string task)
{
        
  pid_t pid;
  cout << "My process id = " << getpid() << endl;
  pid = fork();
    
  if ( pid == -1 )
  {
      cout << "Error in fork";
  }
  else if ( pid == 0 )
  {
    cout << "Child process: My process id = " << getpid() << endl;
    cout << "Child process: Value returned by fork() = " << pid << endl;
    int return_value = system(task.c_str());
    if ( return_value != 0 )
    {
      exit(return_value);
    }
  
    return return_value;
  }
  else
  {
    cout << "Parent process. My process id = " << getpid() << endl;
    cout << "Parent process. Value returned by fork() = " << pid << endl;
  }
  if (wait(NULL) == -1)
  {
    cout << "Error in fork";
  }
   
 
 return 0;
}

int main(int argc, char * argv[])
{
    std::string data;
    SingletonProcess singleton(5555);
    if (!singleton())
    {
      cerr << "process running already. See " << singleton.GetLockFileName() << endl;
      singleton.connectToSocket("HELLO");
      return 1;
    }
   
    while (true)
    {
      sleep(1);
      data = singleton.listenForTask();
      if (data.length() > 0)
      {
        std::cout << data << std::endl;
      }
      
    }
    
    return 0;
}

