#include <SFML/System/Err.hpp>
#include <SFML/Window/Event.hpp>
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
void get_coordinates_from_from_mouse_click(int &y, int &x, sf::Event event)
{
    std::cout << "X: " << event.mouseButton.x << " " << "Y: " << event.mouseButton.y << std::endl;
    if (event.mouseButton.x > 0 && event.mouseButton.x < 266) { x = 0; }
    if (event.mouseButton.x > 266 && event.mouseButton.x < 532) { x = 1; }
    if (event.mouseButton.x > 532) { x = 2; }
    if (event.mouseButton.y > 0  && event.mouseButton.y < 200) { y = 0; }
    if (event.mouseButton.y > 200 && event.mouseButton.y < 400) { y = 1; }
    if (event.mouseButton.y > 400) { y = 2; } 
}
void Board::putSignAtPosition(Player player)
{
    int x, y;
    sf::Event event;
    while(true)
    {
        printBoard();
        std::cout << "Player " << player.get_sign() << " please provide coordinates" << std::endl;
        while(video.get_window()->waitEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                exit(0);
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                get_coordinates_from_from_mouse_click(x, y, event);
                break;
            }
        }
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
                video.cleanBoard();
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
    else if( result_backSlash == 'x' || result_frowardSlash == 'x' )
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

