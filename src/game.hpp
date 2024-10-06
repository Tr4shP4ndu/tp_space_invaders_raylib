#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "mysteryship.hpp"

// Game class definition
class Game {
public:
    Game(); // Constructor to initialize the game
    ~Game(); // Destructor to clean up resources

    void Draw(); // Draw game elements
    void Update(); // Update game state
    void HandleInput(); // Handle user input

    bool run; // Indicates if the game is currently running
    int lives; // Player's lives
    int score; // Player's current score
    int highscore; // Player's high score
    Music music; // Background music

private:
    // Private methods for game functionality
    void DeleteInactiveLasers(); // Remove inactive lasers
    std::vector<Obstacle> CreateObstacles(); // Create obstacles
    std::vector<Alien> CreateAliens(); // Create aliens
    void MoveAliens(); // Move aliens based on game logic
    void MoveDownAliens(int distance); // Move aliens downwards
    void AlienShootLaser(); // Allow aliens to shoot lasers
    void CheckForCollisions(); // Check for collisions between entities
    void GameOver(); // Handle game over state
    void Reset(); // Reset game state
    void InitGame(); // Initialize game elements
    void checkForHighscore(); // Check and update high score
    void saveHighscoreToFile(int highscore); // Save high score to a file
    int loadHighscoreFromFile(); // Load high score from a file

    Spaceship spaceship; // Player's spaceship
    std::vector<Obstacle> obstacles; // List of obstacles
    std::vector<Alien> aliens; // List of aliens
    int aliensDirection; // Direction in which aliens are moving
    std::vector<Laser> alienLasers; // List of lasers shot by aliens
    constexpr static float alienLaserShootInterval = 0.35; // Interval for alien laser shooting
    float timeLastAlienFired; // Last time an alien fired a laser
    MysteryShip mysteryship; // Mystery ship instance
    float mysteryShipSpawnInterval; // Interval for spawning mystery ship
    float timeLastSpawn; // Last time a mystery ship was spawned
    Sound explosionSound; // Sound effect for explosions
};
