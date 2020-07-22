#include <iostream>
#include <vector>

int main()
{
    
    int i = 0;
    int j = 1;
    int tmp = 0;
    int result = 0;
    while(true)
    {
        tmp = i;
        i += j;
        j = tmp;
        if ( i >= 4000000)
        {
            break;
        }
        if ( i % 2 == 0)
        {
            result += i;
        }
    }
    std::cout << result << std::endl;
    return 0;
}
