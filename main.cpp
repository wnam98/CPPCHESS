#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include "Connector.hpp"
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(453, 453), "Chess");
    Texture tx1;
    tx1.loadFromFile("images/figures.png");
    Sprite s(tx1);

    while(window.isOpen())
    {
        Event e;
        while(window.pollEvent(e))
        {
            if(e.type == Event::Closed) window.close();
        }
        window.clear();
        window.draw(s);
        window.display();
    }

    return 0;
}
