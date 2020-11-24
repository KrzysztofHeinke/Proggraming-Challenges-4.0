#include <iostream>
#include <iterator>
#include <utility>
#include <vector>
#include <algorithm>
#include "Board.hpp"

int main()
{
    Player one('o');
    Player two('x');
    Board board;
    int x, y;
    while(true)
    {
        board.putSignAtPosition(one);
        board.putSignAtPosition(two);
    }
    return 0;
}

