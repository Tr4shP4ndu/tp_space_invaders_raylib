#include <raylib.h>
#include "game.hpp"
#include <string>

// Function to format numbers with leading zeros (e.g., for score display)
std::string FormatWithLeadingZeros(int number, int width) {
    std::string numberText = std::to_string(number);
    int leadingZeros = width - numberText.length();
    return numberText = std::string(leadingZeros, '0') + numberText;
}

int main() {
    // Define colors
    Color grey = {29, 29, 27, 255};
    Color yellow = {243, 216, 63, 255};

    int offset = 50;               // Offset for drawing area
    int windowWidth = 750;         // Width of the game window
    int windowHeight = 700;        // Height of the game window

    // Initialize window and audio device
    InitWindow(windowWidth + offset, windowHeight + 2 * offset, "C++ Space Invaders");
    InitAudioDevice();

    // Load font and spaceship texture
    Font font = LoadFontEx("fonts/monogram.ttf", 64, 0, 0);
    Texture2D spaceshipImage = LoadTexture("resources/spaceship.png");

    SetTargetFPS(60); // Set target frames per second

    Game game; // Create an instance of the Game class

    // Main game loop
    while (WindowShouldClose() == false) {
        UpdateMusicStream(game.music);  // Keep the music stream updated
        game.HandleInput();             // Handle player input
        game.Update();                  // Update game state

        // Begin drawing the frame
        BeginDrawing();
        ClearBackground(grey);          // Clear background to grey

        // Draw game area boundaries
        DrawRectangleRoundedLines({10, 10, 780, 780}, 0.18f, 20, 2, yellow);
        DrawLineEx({25, 730}, {775, 730}, 3, yellow);

        // If the game is running, display level information, otherwise show "GAME OVER"
        if (game.run) {
            DrawTextEx(font, "LEVEL 01", {570, 740}, 34, 2, yellow);
        } else {
            DrawTextEx(font, "GAME OVER", {570, 740}, 34, 2, yellow);
        }

        // Draw player lives as spaceship icons
        float x = 50.0;
        for (int i = 0; i < game.lives; i++) {
            DrawTextureV(spaceshipImage, {x, 745}, WHITE);
            x += 50;
        }

        // Draw score
        DrawTextEx(font, "SCORE", {50, 15}, 34, 2, yellow);
        std::string scoreText = FormatWithLeadingZeros(game.score, 5); // Format score with leading zeros
        DrawTextEx(font, scoreText.c_str(), {50, 40}, 34, 2, yellow);

        // Draw high score
        DrawTextEx(font, "HIGH-SCORE", {570, 15}, 34, 2, yellow);
        std::string highscoreText = FormatWithLeadingZeros(game.highscore, 5); // Format highscore with leading zeros
        DrawTextEx(font, highscoreText.c_str(), {655, 40}, 34, 2, yellow);

        // Draw the game (aliens, player, etc.)
        game.Draw();

        // End drawing the frame
        EndDrawing();
    }

    // Close the window and audio device before exiting
    CloseWindow();
    CloseAudioDevice();
}
