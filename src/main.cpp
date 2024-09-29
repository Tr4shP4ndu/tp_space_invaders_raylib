#include <raylib.h>
#include "game.hpp"
#include "laser.hpp"

int main()
{
    Color grey = Color{29, 29, 27, 255};
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);

    Game game;
    Laser laser = Laser({100, 100}, 7);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(grey);
        game.Draw();
        game.HandleInput();
        laser.Draw();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
