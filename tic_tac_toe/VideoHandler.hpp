#ifndef VIDEO_HANLING_HPP
#define VIDEO_HANLING_HPP

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
#include <algorithm>
#include "ThickLine.hpp"
class VideoHandling
{
    int window_height;
    int window_witdh;
    std::vector<std::vector<sf::Vector2f>> coordinates
    { 
       {sf::Vector2f{133,100}, sf::Vector2f{399,100}, sf::Vector2f{665,100}},
       {sf::Vector2f{133,300}, sf::Vector2f{399,300}, sf::Vector2f{665,300}},
       {sf::Vector2f{133,500}, sf::Vector2f{399,500}, sf::Vector2f{665,500}}
    };
    std::unique_ptr<sf::RenderWindow> applicationWindow;
    public:
    VideoHandling(int wHeight, int wWitdh);
    void drawBoard();
    void drawCross(int x, int y);
    void drawCircle(int x, int y);
    sf::Vector2f get_coordinates(int x, int y);
    void display();
    void cleanBoard();
    std::unique_ptr<sf::RenderWindow> &get_window()
    {
        return applicationWindow;
    }
    ~VideoHandling()
    {}
};
#endif
