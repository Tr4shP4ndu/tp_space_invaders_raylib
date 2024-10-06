#pragma once
#include <raylib.h>

class MysteryShip {
    public:
        MysteryShip();        // Constructor
        ~MysteryShip();       // Destructor
        void Update();        // Update ship position
        void Draw();          // Draw the ship
        void Spawn();         // Spawn the ship at random side
        Rectangle getRect();  // Get ship hitbox
        bool alive;           // Ship state (alive or not)
    private:
        Vector2 position;     // Ship position
        Texture2D image;      // Ship texture
        int speed;            // Ship movement speed
};
