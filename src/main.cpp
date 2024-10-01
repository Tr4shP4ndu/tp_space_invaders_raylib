#include <raylib.h>
#include "game.hpp"


int main()
{
    Color grey = Color{29, 29, 27, 255};
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(grey);
        game.Update();
        game.Draw();
        game.HandleInput();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
