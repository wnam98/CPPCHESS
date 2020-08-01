#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include "Connector.hpp"
using namespace sf;

int size = 56;
Sprite f[32];

int board [8][8] =
        {-1, -2, -3, -4, -5, -3, -2, -1,
         -6, -6, -6, -6, -6, -6, -6, -6,
          0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0,
          6, 6, 6, 6, 6, 6, 6, 6,
          1, 2, 3, 4, 5, 3, 2, 1,};

void loadPosition()
{
    int k = 0;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            int n = board[i][j];
            if(!n) continue;
            int x = abs(n) - 1;
            int y = n > 0 ? 1 : 0;
            f[k].setTextureRect(IntRect(size * x, size * y, size, size));
            f[k].setPosition(size * j, size * i);
            k++;
        }
    }
}

int main()
{
    RenderWindow window(VideoMode(453, 453), "Chess");
    Texture tx1;
    Texture tx2;
    tx1.loadFromFile("images/figures.png");
    tx2.loadFromFile("images/board.png");

    Sprite s(tx1);
    Sprite sBoard(tx2);

    for(int i = 0; i < 32; i++) f[i].setTexture(tx1);

    loadPosition();

    bool move = false;
    float dx = 0, dy = 0;
    int n = 0;

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
                    for(int i = 0; i < 32; i++)
                    if (f[i].getGlobalBounds().contains(pos.x, pos.y))
                    {
                        move = true; n = i;
                        dx = pos.x - f[i].getPosition().x;
                        dy = pos.y - f[i].getPosition().y;
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

        if(move) f[n].setPosition(pos.x - dx, pos.y - dy);
        window.clear();
        window.draw(sBoard);
        for(int i = 0; i < 32; i++) window.draw(f[i]);
        window.display();
    }

    return 0;
}
