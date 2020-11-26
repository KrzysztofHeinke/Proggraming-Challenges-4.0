#include <iostream>
#include <iterator>
#include <utility>
#include <vector>
#include <algorithm>
#include "Board.hpp"
#include "VideoHandler.hpp"

char Player::get_sign()
{
    return mSign;
}

void Board::putSignAtPosition(Player player)
{
    int x, y;
    while(true)
    {
        printBoard();
        std::cout << "Player " << player.get_sign() << " please provide coordinates" << std::endl;
        std::cin >> x;
        std::cin >> y; 
        if ( mBoard[x][y] == '-')
        {
            mBoard[x][y] = player.get_sign();
            if (player.get_sign() == 'x')
            {
                video.drawCross(x, y);
            }
            else if( player.get_sign() == 'o')
            {
                video.drawCircle(x,y);
            }
            if(checkIfSomeoneWon())
            {
                printBoard();
                cleanBoard();
            }
            break;
        }
        else
        {
            std::cout << "These cordinates are ocupied please try one more time" << std::endl;
        }
    }
}
void Board::printBoard()
{
    for (auto &x: mBoard)
    {
        for (auto &y: x)
            std::cout << y << " ";
        std::cout << std::endl;
    }
}
void Board::cleanBoard()
{
    for (auto &x: mBoard)
    {
        for (auto &y: x)
            y = '-';    
    }
}
char Board::checkThree(std::vector<char> pList)
{
    std::vector<char> checkVec(pList);
    if (std::count_if(checkVec.begin(), checkVec.end(), [](char i){ return i == 'o';}) == 3)
    {
        return 'o';
    }
    if(std::count_if(checkVec.begin(), checkVec.end(), [](char i){ return i == 'x';}) == 3)
    {
        return 'x';
    }
    return '-';
}

bool Board::checkRows()
{
    for ( auto &x: mBoard )
    {
        char result = checkThree(x);
        if( result == 'o' )
        {
           ++oScore;
           std::cout << "O player have won" << std::endl;
           std::cout << "O player have: " << oScore << " points X player have: " << xScore << std::endl;
           return true;
        }
        else if( result == 'x' )
        {
           ++xScore;
           std::cout << "X player have won" << std::endl;
           std::cout << "O player have: " << oScore << " points X player have: " << xScore << std::endl;
           return true;
        }
    }
    return false;
}
bool Board::checkCoulmuns()
{
    for (int i = 0; i <= 2; ++i)
    {
        char result = checkThree(std::vector<char> {mBoard[0][i], mBoard[1][i], mBoard[2][i]});
        if( result == 'o' )
        {
           ++oScore;
           std::cout << "O player have: " << oScore << " points X player have: " << xScore << std::endl;
           std::cout << "O player have won" << std::endl;
           return true;
        }
        else if( result == 'x' )
        {
           ++xScore;
           std::cout << "O player have: " << oScore << " points X player have: " << xScore << std::endl;
           std::cout << "X player have won" << std::endl;
           return true;
        }
    }
    return false;
}
bool Board::checkSlashes()
{
    char result_frowardSlash = checkThree(std::vector<char> {mBoard[0][0],mBoard[1][1],mBoard[2][2]});
    char result_backSlash = checkThree(std::vector<char> {mBoard[0][2],mBoard[1][1],mBoard[2][0]});
    if( result_backSlash == 'o' || result_frowardSlash == 'o')
    {
       ++oScore;
       std::cout << "O player have: " << oScore << "X player have: " << xScore << std::endl;
       std::cout << "O player have won" << std::endl;
       return true;
    }
    else if( result_backSlash == 'x' || result_backSlash == 'o' )
    {
       ++xScore;
       std::cout << "O player have: " << oScore << " points X player have: " << xScore << " points." << std::endl;
       std::cout << "X player have won" << std::endl;
       return true;
    }
    return false;
}
bool Board::checkIfTie()
{
    bool flag = false;
    for ( auto &x: mBoard )
        for ( auto &y : x )
        {
            if ( y == '-')
            {
                return false;
            }
        }
    std::cout << "TIE !" << std::endl;
    return true;
}
bool Board::checkIfSomeoneWon()
{
    return (checkRows() || checkSlashes() || checkCoulmuns() || checkIfTie());
}

