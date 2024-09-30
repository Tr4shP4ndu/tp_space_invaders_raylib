#include "game.hpp"
#include <iostream>

Game::Game()
{

}

Game::~Game()
{

}

void Game::Update(){
  for(auto& laser: spaceship.lasers)
  {
    laser.Update();
  }
  DeleteInactiveLasers();
  std::cout << "Vector Size: " << spaceship.lasers.size() << std::endl;
}

void Game::Draw()
{
  spaceship.Draw();
  for(auto& laser: spaceship.lasers)
  {
    laser.Draw();
  }
}

void Game::HandleInput()
{
  if(IsKeyDown(KEY_LEFT)) {
      spaceship.MoveLeft();
  } else if (IsKeyDown(KEY_RIGHT)){
      spaceship.MoveRight();
  } else if (IsKeyDown(KEY_SPACE)) {
    spaceship.FireLaser();
  }
}

void Game::DeleteInactiveLasers()
{
  for(auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();)  // Creating an interator named it, loop through the vector, when inactive l;aser we remove it from vector
  {
    if(!it -> active)
    {
      it = spaceship.lasers.erase(it); // The erase method returns a new iterator pointing to the correct element on the vector.
    }
    else
    {
      ++ it; 
    }
  }
}
