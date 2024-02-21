#pragma once
#include <SDL2/SDL.h>
#include <vector>

#ifndef BALL_H
#define BALL_H

const double PI = 3.14159265358979323846;

class Ball
{
private:
  SDL_Texture *image;
  float cenX;
  float cenY;
  float rad;
  float inRad;
  float degree;

public:
  Ball(SDL_Renderer *renderer, SDL_Surface *screenSurface);
  void draw(SDL_Renderer *renderer);
  void move();
};

#endif