#include <raylib.h>
#include "game.hpp"
#include "obstacle.hpp"


int main()
{
    Color grey = Color{29, 29, 27, 255};
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);

    Game game;
    Obstacle obstacle = Obstacle({100, 100});

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(grey);
        game.Update();
        game.Draw();
        game.HandleInput();
        obstacle.Draw();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
