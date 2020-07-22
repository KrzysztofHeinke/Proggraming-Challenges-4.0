#include <iostream>
#include <vector>

int main()
{
    std::vector<int> naturales;
    for (int i = 0; i < 1000; ++i)
    {
        if (i % 3 == 0 || i % 5 == 0)
        {
            naturales.push_back(i);
        }
    }
    int result = 0;
    for ( auto it = naturales.begin(); it != naturales.end(); ++it)
    {
        result += *it;
    }
    std::cout << result << std::endl;
    return 0;
}
