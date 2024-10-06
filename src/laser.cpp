#include "laser.hpp"
#include <iostream>

// Constructor implementation
Laser::Laser(Vector2 position, int speed) {
    this->position = position; // Initialize position
    this->speed = speed;       // Initialize speed
    active = true;             // Set laser to active by default
}

// Draw the laser on the screen
void Laser::Draw() {
    if (active) // Only draw if the laser is active
        DrawRectangle(position.x, position.y, 4, 15, {243, 216, 63, 255}); // Draw the laser as a rectangle
}

// Returns the rectangle that represents the laser
Rectangle Laser::getRect() {
    Rectangle rect;           // Create a rectangle instance
    rect.x = position.x;     // Set the x position
    rect.y = position.y;     // Set the y position
    rect.width = 4;          // Set the width of the rectangle
    rect.height = 15;        // Set the height of the rectangle
    return rect;             // Return the rectangle
}

// Update the laser's position
void Laser::Update() {
    position.y += speed; // Move the laser based on its speed

    if (active) { // If the laser is active
        // Deactivate the laser if it goes off-screen
        if (position.y > GetScreenHeight() - 100 || position.y < 25) {
            active = false; // Set active to false if out of bounds
        }
    }
}
