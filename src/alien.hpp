#pragma once
#include <raylib.h>

// Alien class representing an alien entity in the game
class Alien {
public:
    // Constructor to initialize the alien's type and position
    Alien(int type, Vector2 position);

    // Method to update the alien's position
    void Update(int direction);

    // Method to draw the alien on the screen
    void Draw();

    // Method to get the type of the alien
    int GetType();

    // Method to unload the alien images from memory
    static void UnloadImages();

    // Method to get the rectangle representing the alien's dimensions
    Rectangle getRect();

    static Texture2D alienImages[3]; // Array to hold alien textures
    int type;                          // Type of the alien
    Vector2 position;                  // Position of the alien

private:
};
