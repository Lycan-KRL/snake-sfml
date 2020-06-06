#include <iostream>
#include "Engine.h"

Engine::Engine( sf::RenderWindow& window )
{
    // References
    ref = &window;
    bounds = ref->getSize();

    // # of blocks for grid and initially faced direction
    rows = bounds.x / ( PIXEL_SIZE );
    columns = bounds.y / ( PIXEL_SIZE );
    dir = STOP;

    // Upload BG, snake, and apple textures
    if ( !t.loadFromFile( "Images/TrueBG.png" ) )
    {
        std::cout << "Error in loading background\n"; 
    }
    // - - -
    background.setTexture( t );
    background.setScale( 2.0f, 2.0f );

    if ( !t2.loadFromFile( "Images/Snake_Body.png" ) )
    {
        std::cout << "Error in loading snake\n";
    }
    // - - -
    snek = make_unique<Snake>( t2 );

    if ( !t3.loadFromFile( "Images/Apple_Body.PNG" ) )
    {
        std::cout << "Error in loading apple" << std::endl;
    }
    // - - -
    app = make_unique<Apple>( t3, rows, columns );
}

void Engine::renderEntities()
{
    ref->clear();
    drawBoard();
    snek->drawSnake( ref );
    app->drawApple( ref );
    ref->display();
}

void Engine::runLoop()
{
    // Event handler
    sf::Event e;
    // FPS clock handler
    sf::Clock clock;
    // Game will run at 100fps
    const float timeStep = 0.04f;
    float deltaT = 0.f;
    // Game loop
    while ( ref->isOpen() )
    {
        // Time calculations
        float timePassed = clock.restart().asSeconds();
        deltaT += timePassed;

        // Handle keyboard inputs
        while ( ref->pollEvent( e ) )
        {
            if ( e.type == sf::Event::Closed
                || sf::Keyboard::isKeyPressed( sf::Keyboard::Q ) )
            {
                ref->close();
            }

            if ( e.type == sf::Event::KeyPressed )
            {
                switch ( e.key.code )
                {
                    case sf::Keyboard::Up:
                        if ( snek->lastDirection == DOWN ) break;
                        dir = UP;
                        break;
                    case sf::Keyboard::Down:
                        if ( snek->lastDirection == UP ) break;
                        dir = DOWN;
                        break;
                    case sf::Keyboard::Left:
                        if ( snek->lastDirection == RIGHT ) break;
                        dir = LEFT;
                        break;
                    case sf::Keyboard::Right:
                        if ( snek->lastDirection == LEFT ) break;
                        dir = RIGHT;
                        break;
                    case sf::Keyboard::P:
                        dir = STOP;
                        break;
                };
            }
        }

        // If the frame delay is met, update the snake's position
        // Also, restart the accumulator
        if ( deltaT >= timeStep )
        {
            snek->moveSnakeBody( (int)dir, bounds, deltaT );
            deltaT = 0.0;
        }

        // Death or Apple collision checks
        runChecks();

        // Update the screen
        renderEntities();

        if ( !continueRunning )
        {
            ref->close();
        }
    }
}

void Engine::drawBoard()
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            background.setPosition( i * PIXEL_SIZE, j * PIXEL_SIZE );
            ref->draw( background );
        }
    }
}

void Engine::runChecks()
{
    if ( snek->foundApple( app ) )
    {
        snek->addSnakeSegment();
        app->randomizeLocation();
    }

    if ( snek->hitDeathCollision() )
    {
        continueRunning = false;
    }
}
