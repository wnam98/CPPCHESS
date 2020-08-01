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

std::string toChessNote(Vector2f p)
{
    std::string s = "";
    s += char(p.x / size + 97);
    s += char(7 - p.y / size + 49);
    return s;
}

Vector2f toCoord(char a, char b)
{
    int x = int(a) - 97;
    int y = 7 - int(b) + 49;
    return Vector2f(x * size, y * size);
}

void Move(std::string str)
{
    Vector2f oldPos = toCoord(str[0], str[1]);
    Vector2f newPos = toCoord(str[2], str[3]);

    for(int i = 0; i < 32; i++)
        if(f[i].getPosition() == newPos) f[i].setPosition(-100, -100);

    for(int i = 0 ; i < 32; i++)
        if(f[i].getPosition() == oldPos) f[i].setPosition(newPos);
}

std::string position = "";

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

        for(int i = 0; i < position.length(); i += 5)
        {
            Move(position.substr(i, 4));
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
    Vector2f oldPos, newPos;
    std::string str;
    int n = 0;

    while(window.isOpen())
    {
        Vector2i pos = Mouse::getPosition(window);

        Event e;
        while(window.pollEvent(e))
        {
            if(e.type == Event::Closed) window.close();

            if(e.type == Event::KeyPressed)
            {
                if(e.key.code == Keyboard::BackSpace)
                    position.erase(position.length() - 6, 5); loadPosition();
            }


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
                        oldPos = f[i].getPosition();
                    }
                }
            }

            if (e.type == Event::MouseButtonReleased)
            {
                if (e.key.code == Mouse::Left)
                {
                    move = false;
                    Vector2f p = f[n].getPosition() + Vector2f(size/2, size/2);
                    newPos = Vector2f(size*int(p.x/size), size*int(p.y/size));
                    str = toChessNote(oldPos) + toChessNote(newPos);
                    Move(str); position += str + " ";
                    std::cout<<str<<std::endl;
                    f[n].setPosition(newPos);
                }
            }

            if(Keyboard::isKeyPressed(Keyboard::Space))
            {
                str = getNextMove(position);
                oldPos = toCoord(str[0], str[1]);
                newPos = toCoord(str[2], str[3]);

                for(int i = 0; i < 32; i++) if (f[i].getPosition() == oldPos) n = i;

                for(int k = 0; k < 50; k++)
                {
                    Vector2f p = newPos - oldPos;
                    f[n].move(p.x / 50, p.y / 40);
                    window.draw(sBoard);
                    for(int i = 0; i  < 32; i++) window.draw(f[i]); window.draw(f[n]);
                    window.display();
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
