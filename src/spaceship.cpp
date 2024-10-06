#include "spaceship.hpp"

// Constructor: Loads the spaceship texture and initializes the position and laser sound
Spaceship::Spaceship()
{
    image = LoadTexture("resources/spaceship.png");
    position.x = (GetScreenWidth() - image.width)/2;  // Center horizontally
    position.y = GetScreenHeight() - image.height - 100;  // Position near the bottom of the screen
    lastFireTime = 0.0;
    laserSound = LoadSound("sounds/laser.ogg");  // Load laser sound effect
}

// Destructor: Unloads the spaceship texture and sound to free memory
Spaceship::~Spaceship() {
    UnloadTexture(image);
    UnloadSound(laserSound);
}

// Draws the spaceship
void Spaceship::Draw() {
    DrawTextureV(image, position, WHITE);
}

// Moves the spaceship to the left and prevents it from going off-screen
void Spaceship::MoveLeft() {
    position.x -= 7;
    if(position.x < 25) {
        position.x = 25;  // Clamp the position to the screen bounds
    }
}

// Moves the spaceship to the right and prevents it from going off-screen
void Spaceship::MoveRight() {
    position.x += 7;
    if(position.x > GetScreenWidth() - image.width - 25) {
        position.x = GetScreenWidth() - image.width - 25;  // Clamp the position to the screen bounds
    }
}

// Fires a laser if the cooldown time has passed
void Spaceship::FireLaser()
{
    if(GetTime() - lastFireTime >= 0.35) {  // Fire every 0.35 seconds
        lasers.push_back(Laser({position.x + image.width/2 - 2, position.y}, -6));  // Add a new laser
        lastFireTime = GetTime();  // Reset fire time
        PlaySound(laserSound);     // Play laser sound effect
    }
}

// Returns the rectangle (hitbox) of the spaceship
Rectangle Spaceship::getRect()
{
    return {position.x, position.y, float(image.width), float(image.height)};
}

// Resets the spaceship's position and clears its lasers
void Spaceship::Reset()
{
    position.x = (GetScreenWidth() - image.width) / 2.0f;  // Re-center the spaceship
    position.y = GetScreenHeight() - image.height - 100;  // Reset to the original position
    lasers.clear();  // Clear the lasers
}
