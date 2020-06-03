#ifndef APPLE_H
#define APPLE_H

#include <cstdlib>
#include <random>
#include <SFML/Graphics.hpp>

// Actual sprites are 32x32, so I use scaling for convenience
const int APPLE_SIZE = 64;

class Apple
{
private:
    std::mt19937 generator;
    std::random_device device;
    std::uniform_int_distribution<int> distX;
    std::uniform_int_distribution<int> distY;
public:
    sf::Sprite appleSprite;

    Apple( const sf::Texture& t, const int rows, const int columns );
    void drawApple( sf::RenderWindow* window );
    void randomizeLocation();
};

#endif