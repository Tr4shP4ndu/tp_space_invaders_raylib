#include "alien.hpp"

// Initialize static member for alien textures
Texture2D Alien::alienImages[3] = {};

// Constructor implementation
Alien::Alien(int type, Vector2 position)
{
    this->type = type; // Initialize the alien's type
    this->position = position; // Initialize the alien's position

    // Load alien textures only if not already loaded
    if (alienImages[type - 1].id == 0) {
        switch (type) {
            case 1:
                alienImages[0] = LoadTexture("resources/alien_1.png");
                break;
            case 2:
                alienImages[1] = LoadTexture("resources/alien_2.png");
                break;
            case 3:
                alienImages[2] = LoadTexture("resources/alien_3.png");
                break;
            default:
                alienImages[0] = LoadTexture("resources/alien_1.png");
                break;
        }
    }
}

// Draw the alien using its texture
void Alien::Draw() {
    DrawTextureV(alienImages[type - 1], position, WHITE); // Draw the alien at its position
}

// Get the type of the alien
int Alien::GetType() {
    return type; // Return the type
}

// Unload alien images from memory
void Alien::UnloadImages()
{
    for (int i = 0; i < 3; i++) { // Fixed the loop limit to 3
        UnloadTexture(alienImages[i]); // Unload each texture
    }
}

// Get the rectangle representing the alien's dimensions
Rectangle Alien::getRect()
{
    return {position.x, position.y, 
            static_cast<float>(alienImages[type - 1].width), 
            static_cast<float>(alienImages[type - 1].height)}; // Return the rectangle
}

// Update the alien's position based on the direction
void Alien::Update(int direction) {
    position.x += direction; // Move the alien horizontally
}
