#pragma once
#include <raylib.h>

// Block class representing a small rectangular block in the game
class Block {
public:
    // Constructor to initialize the block's position
    Block(Vector2 position);

    // Method to draw the block on the screen
    void Draw();

    // Method to get the rectangle representing the block's dimensions
    Rectangle getRect();

private:
    Vector2 position; // Position of the block
};
