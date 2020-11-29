#include "VideoHandler.hpp"
#include <iostream>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "ThickLine.hpp"

VideoHandling::VideoHandling(int wHeight, int wWitdh): window_height(wHeight), window_witdh(wWitdh)
{
    applicationWindow = std::make_unique<sf::RenderWindow>(sf::VideoMode( window_height, window_witdh, 32), "Tic_tac_toe");
    drawBoard();
}
void VideoHandling::drawBoard()
{
    sf::RectangleShape vertical_one;
    vertical_one.setSize(sf::Vector2f(5,600));
    vertical_one.setPosition(266,0);
    sf::RectangleShape vertical_two;
    vertical_two.setSize(sf::Vector2f(5,600));
    vertical_two.setPosition(532,0);

    sf::RectangleShape horizontal_one;
    horizontal_one.setSize(sf::Vector2f(800, 5));
    horizontal_one.setPosition(0,200);
    sf::RectangleShape horizontal_two;
    horizontal_two.setSize(sf::Vector2f(800,5));
    horizontal_two.setPosition(0,400);
    applicationWindow->draw(vertical_one);
    applicationWindow->draw(vertical_two);
    applicationWindow->draw(horizontal_one);
    applicationWindow->draw(horizontal_two);
    applicationWindow->display();
}
void VideoHandling::drawPlayerTurn(char sign)
{
    sf::Font font;
    font.loadFromFile("./arial.ttf");
    sf::Text text;
    text.setFont(font);
    std::string text_to_display = "TURN ";
    text_to_display += sign;
    text_to_display += " player";
    text.setString(text_to_display);
    text.setPosition(400, 605);
    text.setCharacterSize(24);
    applicationWindow->draw(text);
}
void VideoHandling::drawPoints(int x, int o)
{
    sf::Font font;
    font.loadFromFile("./arial.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString("O player score: " + std::to_string(o) + " \nX player score: " + std::to_string(x));
    text.setPosition(0, 605);
    text.setCharacterSize(24);
    applicationWindow->draw(text);
}
void VideoHandling::drawCross(int x, int y)
{
    sf::Vector2f vec = coordinates[x][y];
    sf::LineShape lineOne(sf::Vector2f(vec.x - 100, vec.y - 80), sf::Vector2f(vec.x + 100, vec.y + 80));
    sf::LineShape lineTwo(sf::Vector2f(vec.x - 100, vec.y + 80), sf::Vector2f(vec.x + 100, vec.y - 80));
    lineOne.setThickness(5.0);
    lineTwo.setThickness(5.0);
    applicationWindow->draw(lineOne);
    applicationWindow->draw(lineTwo);
    drawPlayerTurn('x');
}
void VideoHandling::drawCircle(int x, int y)
{
    sf::Vector2f vec = coordinates[x][y];
    float radius = 90;
    sf::CircleShape circle(radius);
    circle.setPosition(sf::Vector2f(vec.x - 88, vec.y - 88));
    applicationWindow->draw(circle);
    drawPlayerTurn('o');
}

sf::Vector2f VideoHandling::get_coordinates(int x, int y)
{
    return coordinates[x][y];
}
void VideoHandling::cleanBoard()
{
    applicationWindow->clear();
    drawBoard();
}

void VideoHandling::drawWiningBackslash()
{
    sf::LineShape winingSlash(sf::Vector2f(0,0), sf::Vector2f(800,600));
    winingSlash.setThickness(5.0);
    winingSlash.setFillColor(sf::Color::Red);
    applicationWindow->draw(winingSlash);
}
void VideoHandling::drawWiningForwardslash()
{
    sf::LineShape winingSlash(sf::Vector2f(0,600),sf::Vector2f(800,0));
    winingSlash.setThickness(5.0);
    winingSlash.setFillColor(sf::Color::Red);
    applicationWindow->draw(winingSlash);
}
void VideoHandling::drawWiningHorizontal(int whichLine)
{
    sf::Vector2f vector_x;
    sf::Vector2f vector_y;
    if (whichLine == 0)
    {
        vector_x = sf::Vector2f(50,100);
        vector_y = sf::Vector2f(750,100);
    }
    else if (whichLine == 1)
    {
        vector_x = sf::Vector2f(50,300);
        vector_y = sf::Vector2f(750,300);
    }
    else if (whichLine == 2)
    {
        vector_x = sf::Vector2f(50,500);
        vector_y = sf::Vector2f(750,500);
    }
    sf::LineShape winingLine(vector_x, vector_y);
    winingLine.setFillColor(sf::Color::Red);
    winingLine.setThickness(5.0);
    applicationWindow->draw(winingLine);
}
void VideoHandling::drawWiningVertical(int whichLine)
{
    sf::Vector2f vector_x;
    sf::Vector2f vector_y;
    if (whichLine == 0)
    {
        vector_x = sf::Vector2f(133,0);
        vector_y = sf::Vector2f(133,600);
    }
    else if (whichLine == 1)
    {
        vector_x = sf::Vector2f(399,0);
        vector_y = sf::Vector2f(399,600);
    }
    else if (whichLine == 2)
    {
        vector_x = sf::Vector2f(665,0);
        vector_y = sf::Vector2f(665,600);
    }
    sf::LineShape winingLine(vector_x, vector_y);
    winingLine.setFillColor(sf::Color::Red);
    winingLine.setThickness(5.0);
    applicationWindow->draw(winingLine);
}
void VideoHandling::display()
{
    applicationWindow->display();
}
