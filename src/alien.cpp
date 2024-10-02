#include "alien.hpp"

Alien::Alien(int type, Vector2 position)
{
  this -> type = type;
  this -> position = position;

  switch(type)
  {
    case 1:
        image = LoadTexture("resources/alien_1.png");
        break;
    case 2:
        image = LoadTexture("resources/alien_2.png");
        break;
    case 3:
        image = LoadTexture("resources/alien_3.png");
        break;
    default:
        image = LoadTexture("resources/alien_1.png");
        break;
  }
}

void Alien::Draw()
{
  DrawTextureV(image, position, WHITE);
}

int Alien::GetType()
{
  return type;
}
