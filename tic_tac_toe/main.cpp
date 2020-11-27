#include <SFML/Window/Event.hpp>
#include <iostream>
#include <iterator>
#include <memory>
#include <utility>
#include <vector>
#include <algorithm>
#include "Board.hpp"
int main()
{
    Player one('o');
    Player two('x');
    Board board;
    while(true)
    {
        board.putSignAtPosition(one);
        board.putSignAtPosition(two);
    }
    return 0;
}

