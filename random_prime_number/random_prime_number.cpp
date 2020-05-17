#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

bool is_prime(int digit)
{
    if (digit < 2)
    {
        return false;
    }
    for (int i = 2; i*i <= digit; i++)
    {
        if (digit % i == 0)
        {
            return false;
        }
    }
    return true;
}

int big_random_prime()
{
    // srand((int)time(0));
    int prime;
    do
    {
        prime = rand() % 10000000000 + 1000000000 ;

    }while( ! is_prime(prime));
    return prime;
}

