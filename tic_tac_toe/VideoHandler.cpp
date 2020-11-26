#include "VideoHandler.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
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
void VideoHandling::drawCross(int x, int y)
{
    sf::Vector2f vec = coordinates[x][y];
    sf::LineShape lineOne(sf::Vector2f(vec.x - 100, vec.y - 80), sf::Vector2f(vec.x + 100, vec.y + 80));
    sf::LineShape lineTwo(sf::Vector2f(vec.x - 100, vec.y + 80), sf::Vector2f(vec.x + 100, vec.y - 80));
    lineOne.setThickness(5.0);
    lineTwo.setThickness(5.0);
    applicationWindow->draw(lineOne);
    applicationWindow->draw(lineTwo);
    applicationWindow->display();
}
void VideoHandling::drawCircle(int x, int y)
{
    sf::Vector2f vec = coordinates[x][y];
    float radius = 90;
    sf::CircleShape circle(radius);
    circle.setPosition(sf::Vector2f(vec.x - 88, vec.y - 88));
    applicationWindow->draw(circle);
    applicationWindow->display();
}

sf::Vector2f VideoHandling::get_coordinates(int x, int y)
{
    return coordinates[x][y];
}

void VideoHandling::display()
{
    applicationWindow->display();
}
