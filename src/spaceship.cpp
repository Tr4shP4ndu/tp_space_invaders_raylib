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

void Spaceship::MoveLeft() {
    position.x -= 7;
    if(position.x < 25) {
        position.x = 25;
    }
}

void Spaceship::MoveRight() {
    position.x += 7;
    if(position.x > GetScreenWidth() - image.width - 25) {
        position.x = GetScreenWidth() - image.width - 25;
    }
}
