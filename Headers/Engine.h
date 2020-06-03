#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Apple.h"
using std::unique_ptr;
using std::make_unique;

// Actual sprites are 32x32, so I use scaling for convenience
const int PIXEL_SIZE = 64;

class Engine
{
private:
    // Keep created window for drawing and boundary checking
    sf::RenderWindow *ref = NULL;

    // So I don't have to call getSize() every time
    sf::Vector2u bounds;

    // Rows & Columns of blocks that the snake can travel
    int rows = 0;
    int columns = 0;

    // Sprite for the BG
    sf::Texture t, t2, t3, t4;
    sf::Sprite background;
    sf::Sprite endScreen;

    // Snake and Apple representatives 
    // They handle their own positions, collisions, and drawings
    unique_ptr<Snake> snek;
    unique_ptr<Apple> app;

    // - - - enum & game status
    enum Directions { STOP=0, UP, DOWN, LEFT, RIGHT } dir;
    bool continueRunning = true;
public:
    // Assign reference and retrieve boundaries
    Engine( sf::RenderWindow& window );

    // Game movement, analytics, and frame independence
    void runLoop();

    // Clear, Draw updated snake and/or apple, display
    void renderEntities();

    void drawBoard();

    // Collision checks
    void runChecks();
};

#endif