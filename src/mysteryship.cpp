#include "mysteryship.hpp"

// Constructor: Loads the texture for the mystery ship and sets it to inactive (alive = false)
MysteryShip::MysteryShip()
{
    image = LoadTexture("resources/mystery.png");
    alive = false;
}

// Destructor: Unloads the mystery ship texture to free memory
MysteryShip::~MysteryShip() {
    UnloadTexture(image);
}

// Spawns the mystery ship at a random side of the screen and sets its speed and position
void MysteryShip::Spawn() {
    position.y = 90;
    int side = GetRandomValue(0, 1);  // Randomize the side it spawns from

    if(side == 0) {
        position.x = 25;       // Spawn on the left
        speed = 3;             // Move right
    } else {
        position.x = GetScreenWidth() - image.width - 25;  // Spawn on the right
        speed = -3;            // Move left
    }
    alive = true;               // Set the ship as active
}

// Returns the rectangle (hitbox) of the mystery ship if it's alive, otherwise returns an empty rectangle
Rectangle MysteryShip::getRect()
{
    if(alive){
        return {position.x, position.y, float(image.width), float(image.height)};
    } else {
        return {position.x, position.y, 0, 0};
    }
}

// Updates the position of the mystery ship if it's alive and deactivates it when it goes off-screen
void MysteryShip::Update() {
    if(alive) {
        position.x += speed;  // Move the ship in the current direction
        if(position.x > GetScreenWidth() - image.width -25 || position.x < 25) {
            alive = false;    // Deactivate when it goes off the screen
        }
    }
}

// Draws the mystery ship if it's alive
void MysteryShip::Draw() {
    if(alive) {
        DrawTextureV(image, position, WHITE);
    }
}
