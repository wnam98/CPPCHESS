#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include "Connector.hpp"
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(550, 550), "Chess");
    Texture tx1;
    tx1.loadFromFile("images/figures.png");
    Sprite s(tx1);
    bool move = false;
    float dx = 0, dy = 0;

    while(window.isOpen())
    {
        Vector2i pos = Mouse::getPosition(window);

        Event e;
        while(window.pollEvent(e))
        {
            if(e.type == Event::Closed) window.close();

            if(e.type == Event::MouseButtonPressed)
            {
                if (e.key.code == Mouse::Left)
                {
                    if (s.getGlobalBounds().contains(pos.x, pos.y))
                    {
                        move = true;
                        dx = pos.x - s.getPosition().x;
                        dy = pos.y - s.getPosition().y;
                    }
                }
            }

            if (e.type == Event::MouseButtonReleased)
            {
                if (e.key.code == Mouse::Left)
                {
                    move = false;
                }
            }
        }

        if(move) s.setPosition(pos.x - dx, pos.y - dy);
        window.clear();
        window.draw(s);
        window.display();
    }

    return 0;
}
