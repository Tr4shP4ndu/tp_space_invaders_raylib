#include "spaceship.hpp"

Spaceship::Spaceship()
{
    image = LoadTexture("resources/spaceship.png");
    position.x = (GetScreenWidth() - image.width) / 2; //Screen calculation by middle of the screen x axis
    position.y = (GetScreenHeight() - image.height); //Screen calculation by middle of the screen y axis

}

Spaceship::~Spaceship() {
    UnloadTexture(image);
}


void Spaceship::Draw() 
{
    DrawTextureV(image, position, WHITE);
}
