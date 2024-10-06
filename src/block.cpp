#include "block.hpp"

// Constructor implementation
Block::Block(Vector2 position)
{
    this->position = position; // Initialize the block's position
}

// Draw the block using a specific color
void Block::Draw() {
    DrawRectangle(position.x, position.y, 3, 3, {243, 216, 63, 255}); // Draw a yellow block
}

// Get the rectangle representing the block's dimensions
Rectangle Block::getRect()
{
    Rectangle rect;
    rect.x = position.x; // X coordinate
    rect.y = position.y; // Y coordinate
    rect.width = 3;      // Width of the block
    rect.height = 3;     // Height of the block
    return rect; // Return the rectangle
}
