#pragma once
#include <raylib.h>
#include "laser.hpp"
#include <vector>

class Spaceship {
    public:
        Spaceship();          // Constructor
        ~Spaceship();         // Destructor
        void Draw();          // Draw the spaceship
        void MoveLeft();      // Move spaceship left
        void MoveRight();     // Move spaceship right
        void FireLaser();     // Fire a laser
        Rectangle getRect();  // Get spaceship hitbox
        void Reset();         // Reset spaceship state
        std::vector<Laser> lasers;  // List of lasers fired
    private:
        Texture2D image;      // Spaceship texture
        Vector2 position;     // Spaceship position
        double lastFireTime;  // Time since last laser fired
        Sound laserSound;     // Laser sound effect
};
