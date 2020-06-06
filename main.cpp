#include <SFML/Graphics.hpp>
#include <iostream>
#include "Engine.h"

const int SCREEN_HEIGHT = 1600;
const int SCREEN_WIDTH = 2240;

int main()
{
    std::srand( time( NULL) );
    // Create a window of 2500 x 1500
    sf::RenderWindow win( sf::VideoMode( SCREEN_WIDTH, SCREEN_HEIGHT ), "Snake! :)" );
    // Initiate game and run
    Engine gameEngine( win );
    gameEngine.runLoop();
    // Terminate
    return 0;
}
