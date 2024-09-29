#include <raylib.h>
#include "spaceship.hpp"

int main()
{
    // Color darkGreen = Color{20, 160, 133, 255};
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);

    Spaceship spaceship;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        spaceship.Draw();
        // ClearBackground(darkGreen);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
