#include "Apple.h"

Apple::Apple( const sf::Texture& t, const int rows, const int columns ) : distX( 0, columns-1 ), distY( 0, rows-1 ), generator( device() )
{
    appleSprite.setTexture( t );
    appleSprite.setScale( 2.0f, 2.0f );
    randomizeLocation();
}

void Apple::drawApple( sf::RenderWindow* window )
{
    window->draw( appleSprite );
}

void Apple::randomizeLocation()
{
    sf::Vector2f newPosition;

    newPosition.x = APPLE_SIZE * distY( generator );
    newPosition.y = APPLE_SIZE * distX( generator );

    appleSprite.setPosition( newPosition );
}