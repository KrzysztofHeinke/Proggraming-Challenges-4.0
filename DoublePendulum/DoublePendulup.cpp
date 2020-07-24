#include <iostream>
#include <SFML/Graphics.hpp>
#include <unistd.h>
int main()
{
    int circleRadius = 50;
    sf::RenderWindow window(sf::VideoMode(200, 200), "DoublePendulum");
    sf::CircleShape shape(circleRadius);
    shape.setPosition(sf::Vector2f(100,100));
    shape.setFillColor(sf::Color::Green);
    int i = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        ++i;
        sleep(1);
        shape.setPosition(sf::Vector2f(i,100));
        window.clear();
        window.draw(shape);
        window.display();
    }
}
