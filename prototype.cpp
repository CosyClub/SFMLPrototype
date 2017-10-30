#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

using namespace std;
using namespace sf;

#define BPM 150
#define DELTA 200
#define SIZE 1000
#define GRID 100
#define TIME 60000000 / BPM
#define LOWERBOUND (DELTA * 1000)
#define UPPERBOUND TIME - (DELTA * 1000)

#define COLOR1 Color::Black
#define COLOR2 Color::White

Color switchColor(Color c)
{
    if (c == COLOR1){
        return COLOR2;
    }
    else{
        return COLOR1;
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(SIZE, SIZE), "Dance!");
    sf::RectangleShape grid(sf::Vector2f(GRID,GRID));
    Color currentColor = COLOR1;

    SoundBuffer tickbuffer;
    tickbuffer.loadFromFile("res/tick.ogg");
    Sound tick;
    tick.setBuffer(tickbuffer);

    sf::CircleShape player(GRID / 2);
    player.setFillColor(Color::Magenta);
    Clock clock;
    bool hasmoved = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // check the type of the event...
            switch (event.type)
            {
                // window closed
                case sf::Event::Closed:
                    window.close();
                    break;
            
                // key pressed
                case sf::Event::KeyPressed:
                    if(!hasmoved){
                        if (clock.getElapsedTime().asMicroseconds() < LOWERBOUND || clock.getElapsedTime().asMicroseconds() > UPPERBOUND){
                            if (event.KeyReleased && event.key.code == Keyboard::W)
                            {
                                player.move(Vector2f(0, -1 * GRID));
                                hasmoved = true;
                            }
                            if (event.KeyReleased && event.key.code == Keyboard::A)
                            {
                                player.move(Vector2f(-1 * GRID, 0));
                                hasmoved = true;
                            }
                            if (event.KeyReleased && event.key.code == Keyboard::S)
                            {
                                player.move(Vector2f(0, GRID));
                                hasmoved = true;
                            }
                            if (event.KeyReleased && event.key.code == Keyboard::D)
                            {
                                player.move(Vector2f(GRID, 0));
                                hasmoved = true;
                            }
                        }
                    }
                    break;
            
                // we don't process other types of events
                default:
                    break;
            }
        }

        if(player.getPosition().x < 0){
            player.setPosition(0, player.getPosition().y);
        }
        if(player.getPosition().x > SIZE){
            player.setPosition(SIZE, player.getPosition().y);
        }
        if(player.getPosition().y < 0){
            player.setPosition(player.getPosition().x, 0);
        }
        if(player.getPosition().y > SIZE){
            player.setPosition(player.getPosition().x, SIZE);
        }

        if (clock.getElapsedTime().asMicroseconds() > TIME){
            currentColor = switchColor(currentColor);
            tick.play();
            clock.restart();
            hasmoved = false;
        }

        window.clear();
        for (int I = 0; I <= SIZE; I+=GRID)
        {
            for (int J = 0; J <= SIZE; J+=GRID)
            {
                window.draw(grid);
                grid.setPosition(Vector2f(J,I));
                grid.setFillColor(currentColor);
                currentColor = switchColor(currentColor);
            }
        }
        
        currentColor = switchColor(currentColor);

        window.draw(player);
        window.display();
    }

    return 0;
}