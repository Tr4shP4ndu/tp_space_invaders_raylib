#include "game.hpp"
#include <iostream>
#include <fstream>

// Constructor implementation
Game::Game() {
    music = LoadMusicStream("sounds/music.ogg"); // Load background music
    explosionSound = LoadSound("sounds/explosion.ogg"); // Load explosion sound
    PlayMusicStream(music); // Start playing music
    InitGame(); // Initialize game elements
}

// Destructor implementation
Game::~Game() {
    Alien::UnloadImages(); // Unload alien images
    UnloadMusicStream(music); // Unload background music
    UnloadSound(explosionSound); // Unload explosion sound
}

// Update game state
void Game::Update() {
    if (run) {
        double currentTime = GetTime(); // Get the current time
        
        // Spawn mystery ship if the time interval has passed
        if (currentTime - timeLastSpawn > mysteryShipSpawnInterval) {
            mysteryship.Spawn(); // Spawn the mystery ship
            timeLastSpawn = GetTime(); // Reset last spawn time
            mysteryShipSpawnInterval = GetRandomValue(10, 20); // Randomize next spawn interval
        }

        // Update lasers fired by the spaceship
        for (auto& laser : spaceship.lasers) {
            laser.Update();
        }

        MoveAliens(); // Update aliens' positions
        AlienShootLaser(); // Allow aliens to shoot lasers

        // Update lasers shot by aliens
        for (auto& laser : alienLasers) {
            laser.Update();
        }

        DeleteInactiveLasers(); // Remove inactive lasers
        mysteryship.Update(); // Update mystery ship state
        CheckForCollisions(); // Check for collisions
    } else {
        // Reset the game if the ENTER key is pressed
        if (IsKeyDown(KEY_ENTER)) {
            Reset();
            InitGame();
        }
    }
}

// Draw game elements
void Game::Draw() {
    spaceship.Draw(); // Draw the spaceship

    // Draw lasers fired by the spaceship
    for (auto& laser : spaceship.lasers) {
        laser.Draw();
    }

    // Draw obstacles
    for (auto& obstacle : obstacles) {
        obstacle.Draw();
    }

    // Draw aliens
    for (auto& alien : aliens) {
        alien.Draw();
    }

    // Draw lasers fired by aliens
    for (auto& laser : alienLasers) {
        laser.Draw();
    }

    mysteryship.Draw(); // Draw mystery ship
}

// Handle user input
void Game::HandleInput() {
    if (run) {
        // Move spaceship left or right based on key input
        if (IsKeyDown(KEY_LEFT)) {
            spaceship.MoveLeft();
        } else if (IsKeyDown(KEY_RIGHT)) {
            spaceship.MoveRight();
        } else if (IsKeyDown(KEY_SPACE)) {
            spaceship.FireLaser(); // Fire laser if SPACE is pressed
        }
    }
}

// Remove inactive lasers from both spaceship and alien lists
void Game::DeleteInactiveLasers() {
    // Remove inactive lasers from the spaceship
    for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();) {
        if (!it->active) {
            it = spaceship.lasers.erase(it); // Erase inactive laser
        } else {
            ++it; // Move to the next laser
        }
    }

    // Remove inactive lasers shot by aliens
    for (auto it = alienLasers.begin(); it != alienLasers.end();) {
        if (!it->active) {
            it = alienLasers.erase(it); // Erase inactive laser
        } else {
            ++it; // Move to the next laser
        }
    }
}

// Create obstacles and position them on the screen
std::vector<Obstacle> Game::CreateObstacles() {
    int obstacleWidth = Obstacle::grid[0].size() * 3; // Calculate obstacle width
    float gap = (GetScreenWidth() - (4 * obstacleWidth)) / 5; // Calculate gap between obstacles

    // Create obstacles in a loop
    for (int i = 0; i < 4; i++) {
        float offsetX = (i + 1) * gap + i * obstacleWidth; // Calculate x position
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 200)})); // Add obstacle
    }
    return obstacles; // Return the created obstacles
}

// Create aliens and position them in a grid
std::vector<Alien> Game::CreateAliens() {
    std::vector<Alien> aliens; // Vector to hold created aliens

    // Loop to create a grid of aliens
    for (int row = 0; row < 5; row++) {
        for (int column = 0; column < 11; column++) {
            int alienType; // Variable to hold alien type
            
            // Determine alien type based on row
            if (row == 0) {
                alienType = 3; // Strongest aliens
            } else if (row == 1 || row == 2) {
                alienType = 2; // Medium-strength aliens
            } else {
                alienType = 1; // Weakest aliens
            }

            // Calculate position for each alien
            float x = 75 + column * 55;
            float y = 110 + row * 55;
            aliens.push_back(Alien(alienType, {x, y})); // Add alien to vector
        }
    }
    return aliens; // Return the created aliens
}

// Move aliens based on game logic
void Game::MoveAliens() {
    for (auto& alien : aliens) {
        // Check if aliens reach screen bounds and change direction if needed
        if (alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth() - 25) {
            aliensDirection = -1; // Change direction to left
            MoveDownAliens(4); // Move aliens down
        }
        if (alien.position.x < 25) {
            aliensDirection = 1; // Change direction to right
            MoveDownAliens(4); // Move aliens down
        }

        alien.Update(aliensDirection); // Update alien's position
    }
}

// Move aliens downwards by a specified distance
void Game::MoveDownAliens(int distance) {
    for (auto& alien : aliens) {
        alien.position.y += distance; // Move each alien down
    }
}

void Game::AlienShootLaser()
{
    double currentTime = GetTime();
    if(currentTime - timeLastAlienFired >= alienLaserShootInterval && !aliens.empty()) {
        int randomIndex = GetRandomValue(0, aliens.size() - 1);
        Alien& alien = aliens[randomIndex];
        alienLasers.push_back(Laser({alien.position.x + alien.alienImages[alien.type -1].width/2, 
                                    alien.position.y + alien.alienImages[alien.type - 1].height}, 6));
        timeLastAlienFired = GetTime();
    }
}

void Game::CheckForCollisions()
{
    //Spaceship Lasers

    for(auto& laser: spaceship.lasers) {
        auto it = aliens.begin();
        while(it != aliens.end()){
            if(CheckCollisionRecs(it -> getRect(), laser.getRect()))
            {
                PlaySound(explosionSound);
                if(it -> type == 1) {
                    score += 100;
                } else if (it -> type == 2) {
                    score += 200;
                } else if(it -> type == 3) {
                    score += 300;
                }
                checkForHighscore();

                it = aliens.erase(it);
                laser.active = false;
            } else {
                ++it;
            }
        }

        for(auto& obstacle: obstacles){
            auto it = obstacle.blocks.begin();
            while(it != obstacle.blocks.end()){
                if(CheckCollisionRecs(it -> getRect(), laser.getRect())){
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                } else {
                    ++it;
                }
            }
        }

        if(CheckCollisionRecs(mysteryship.getRect(), laser.getRect())){
            mysteryship.alive = false;
            laser.active = false;
            score += 500;
            checkForHighscore();
            PlaySound(explosionSound);
        }
    }

    //Alien Lasers

    for(auto& laser: alienLasers) {
        if(CheckCollisionRecs(laser.getRect(), spaceship.getRect())){
            laser.active = false;
            lives --;
            if(lives == 0) {
                GameOver();
            }
        }

          for(auto& obstacle: obstacles){
            auto it = obstacle.blocks.begin();
            while(it != obstacle.blocks.end()){
                if(CheckCollisionRecs(it -> getRect(), laser.getRect())){
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                } else {
                    ++it;
                }
            }
        }
    }

    //Alien Collision with Obstacle
    
    for(auto& alien: aliens) {
        for(auto& obstacle: obstacles) {
            auto it = obstacle.blocks.begin();
            while(it != obstacle.blocks.end()) {
                if(CheckCollisionRecs(it -> getRect(), alien.getRect())) {
                    it = obstacle.blocks.erase(it);
                } else {
                    it ++;
                }
            }
        }

        if(CheckCollisionRecs(alien.getRect(), spaceship.getRect())) {
            GameOver();
        }
    }
}

void Game::GameOver()
{
    run = false;
}

void Game::InitGame()
{
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    aliensDirection = 1;
    timeLastAlienFired = 0.0;
    timeLastSpawn = 0.0;
    lives = 3;
    score = 0;
    highscore = loadHighscoreFromFile();
    run = true;
    mysteryShipSpawnInterval = GetRandomValue(10, 20);
}

void Game::checkForHighscore()
{
    if(score > highscore) {
        highscore = score;
        saveHighscoreToFile(highscore);
    }
}

void Game::saveHighscoreToFile(int highscore)
{
    std::ofstream highscoreFile("highscore.txt");
    if(highscoreFile.is_open()) {
        highscoreFile << highscore;
        highscoreFile.close();
    } else {
        std::cerr << "Failed to save highscore to file" << std::endl;
    }
}

int Game::loadHighscoreFromFile() {
    int loadedHighscore = 0;
    std::ifstream highscoreFile("highscore.txt");
    if(highscoreFile.is_open()) {
        highscoreFile >> loadedHighscore;
        highscoreFile.close();
    } else {
        std::cerr << "Failed to load highscore from file." << std::endl;
    }
    return loadedHighscore;
}

void Game::Reset() {
    spaceship.Reset();
    aliens.clear();
    alienLasers.clear();
    obstacles.clear();
}
