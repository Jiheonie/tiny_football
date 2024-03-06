#include <iostream>
#include <SDL2/SDL.h>
#include "PhysicsObject.h"
#include "Player.h"
#include "Vector2D.h"

#ifndef GOAL_H
#define GOAL_H

class Goal
{
private:
  TeamEnum team;
  SDL_Texture *image;
  SDL_Rect rect;
  Vector2D a;
  Vector2D b;

public:
  static std::vector<Goal *> _allGoals;
  Goal(TeamEnum team, float x, float y, float ax, float ay, float bx, float by, SDL_Renderer *renderer, SDL_Surface *screenSurface);
  void draw(SDL_Renderer *renderer);
  TeamEnum getTeam();
  Vector2D getA();
  Vector2D getB();
};

#endif