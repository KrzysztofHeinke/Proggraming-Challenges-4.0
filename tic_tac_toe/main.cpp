#include <iostream>
#include <iterator>
#include <memory>
#include <utility>
#include <vector>
#include <algorithm>
#include "Board.hpp"

int main()
{
//    VideoHandling video(800,600);
    Player one('o');
    Player two('x');
    Board board;
//    video.drawCross(133,100);
 //swapfile   video.drawCircle(399,300);
    while(true)
    {
        board.putSignAtPosition(one);
        board.putSignAtPosition(two);
    }
    return 0;
}

