#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <deque>
#include <iostream>
#include "Apple.h"

// Actual sprites are 32x32, so I use scaling for convenience
const int SNAKE_SIZE = 64;

class Snake
{
private:
    struct Position 
    {
        int x = 0;
        int y = 0;
    };

    std::deque<Position*> body;  
    int length = 5;
    bool alive = true;
public:
    sf::Sprite bodySegment;
    int lastDirection = 0;

    Snake( const sf::Texture& t );
    void moveSnakeBody( const int direction, const sf::Vector2u bounds, const float d );
    void drawSnake( sf::RenderWindow* window );
    bool foundApple( const std::unique_ptr<Apple>& apple );
    bool validMove( const int direction, const sf::Vector2u bounds );
    bool hitDeathCollision();
    void addSnakeSegment();
};

#endif