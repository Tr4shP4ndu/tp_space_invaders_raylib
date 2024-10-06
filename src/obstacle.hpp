#pragma once
#include <vector>
#include "block.hpp"

class Obstacle {
    public:
        Obstacle(Vector2 position);  // Constructor
        void Draw();                 // Draw obstacle blocks
        Vector2 position;            // Position of the obstacle
        std::vector<Block> blocks;   // List of blocks that make up the obstacle
        static std::vector<std::vector<int>> grid;  // The grid pattern of the obstacle
    private:
};
