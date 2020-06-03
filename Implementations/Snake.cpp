#include <deque>
#include <iostream>
#include "Snake.h"

Snake::Snake( const sf::Texture& t )
{
    for (int i = 0; i < length; ++i)
    {
        body.push_back( new Position );
    }

    bodySegment.setTexture( t );
    bodySegment.setScale( 2.0f, 2.0f );
}

void Snake::moveSnakeBody( const int direction, const sf::Vector2u bounds, const float d )
{
        if ( direction == 0 )
        {
            return; 
        }

        for (int i = length-1; i > 0; --i)
        {
            body[i]->x = body[i-1]->x;
            body[i]->y = body[i-1]->y;
        }

        switch ( direction )
        {
            case 1:
                --body[0]->y*d;
                lastDirection = 1;
                break;
            case 2:
                ++body[0]->y*d;
                lastDirection = 2;
                break;
            case 3:
                --body[0]->x*d;
                lastDirection = 3;
                break;
            case 4:
                ++body[0]->x*d;
                lastDirection = 4;
        };

        if ( body[0]->x < 0 )
        {
            body[0]->x = bounds.x / SNAKE_SIZE - 1;
        }
        if ( body[0]->y < 0 )
        {
            body[0]->y = bounds.y / SNAKE_SIZE - 1;
        }
        if ( body[0]->x >= bounds.x / SNAKE_SIZE )
        {
            body[0]->x = 0;
        }
        if ( body[0]->y >= bounds.y / SNAKE_SIZE )
        {
            body[0]->y = 0;
        }
}

void Snake::drawSnake( sf::RenderWindow* window )
{
    for (int i = 0; i < length; ++i)
    {
        bodySegment.setPosition( body[i]->x * SNAKE_SIZE, body[i]->y * SNAKE_SIZE );
        window->draw( bodySegment );
    }
}

bool Snake::foundApple( const std::unique_ptr<Apple>& apple )
{
    // Grab current position of the snake's head
    sf::Vector2f headPosition( body[0]->x * SNAKE_SIZE, body[0]->y * SNAKE_SIZE );
    // Return whether the unit that contains the head is also within the apple's unit
    return ( apple->appleSprite.getGlobalBounds().contains( headPosition ) );
}

bool Snake::validMove( const int direction, const sf::Vector2u bounds )
{
    bool canMove = true;
    
    int tempX = body[0]->x;
    int tempY = body[0]->y;

    switch ( direction )
    {
        case 1:
            --tempY;
            break;
        case 2:
            ++tempY;
            break;
        case 3:
            --tempX;
            break;
        case 4:
            ++tempX;
    };

    if ( tempX < 0
        || tempY < 0
        || tempX >= bounds.x / SNAKE_SIZE
        || tempY >= bounds.y / SNAKE_SIZE )
    {
        canMove = false;
    }

    return canMove;
}

bool Snake::hitDeathCollision()
{
    if ( lastDirection == 0 ) 
    { 
        return 0;
    }

    sf::Vector2f headPosition( body[0]->x, body[0]->y );
    for (int i = 1; i < length; ++i)
    {
        if ( body[0]->x == body[i]->x && body[0]->y == body[i]->y )
        {
            alive = false;
            return true;
        }
    }
    return false;
}

void Snake::addSnakeSegment()
{
    ++length;
    body.push_back( new Position );
}