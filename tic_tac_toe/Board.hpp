#include <SFML/Window/Event.hpp>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>
#include <algorithm>
#include "VideoHandler.hpp"

class Player
{
    char mSign;
    public:
    Player(char sign): mSign(sign){}
    char get_sign();
};

class Board
{
    std::vector <std::vector<char>> mBoard {{'-','-','-'},{'-','-','-'},{'-','-','-'}};
    int oScore {0};
    int xScore {0};
    VideoHandling video{800,800};
    public:
    void putSignAtPosition(Player player);
    void printBoard();
    void cleanBoard();
    char checkThree(std::vector<char> pList);
    bool checkRows();
    bool checkCoulmuns();
    bool checkSlashes();
    bool checkIfTie();
    bool checkIfSomeoneWon();

};

