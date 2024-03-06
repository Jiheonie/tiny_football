#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "PhysicsObject.h"

#ifndef BALL_H
#define BALL_H

const double PI = 3.14159265358979323846;

class Ball : public PhysicsObject
{
private:
  SDL_Texture *image;
  float rad;
  float inRad;
  float degree;

public:
  Ball(SDL_Renderer *renderer, SDL_Surface *screenSurface);
  float getRadius();
  void draw(SDL_Renderer *renderer);
  void touch(float x, float y);
  void update(float dt);
  bool isTouching(Vector2D p);
};

#endif