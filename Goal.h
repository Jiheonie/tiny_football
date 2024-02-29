#include <iostream>
#include <SDL2/SDL.h>
#include "PhysicsObject.h"
#include "Player.h"

#ifndef GOAL_H
#define GOAL_H

class Goal
{
private:
  TeamEnum team;
  SDL_Texture *image;
  SDL_Rect rect;

public:
  Goal(TeamEnum team, float x, float y, SDL_Renderer *renderer, SDL_Surface *screenSurface);
  void draw(SDL_Renderer *renderer);
};

#endif