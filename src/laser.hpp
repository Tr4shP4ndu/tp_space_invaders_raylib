#pragma once
#include <raylib.h>

// Laser class definition
class Laser {
public:
    // Constructor: initializes position and speed of the laser
    Laser(Vector2 position, int speed);
    
    // Updates the laser's position
    void Update();
    
    // Draws the laser on the screen
    void Draw();
    
    // Returns the rectangle representing the laser's position and size
    Rectangle getRect();

    bool active; // Indicates if the laser is currently active

private:
    Vector2 position; // Position of the laser
    int speed;        // Speed at which the laser moves
};
