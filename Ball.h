#pragma once
#include <SDL2/SDL.h>
#include <vector>

#ifndef BALL_H
#define BALL_H

const double PI = 3.14159265358979323846;

class Ball
{
private:
  float cenX;
  float cenY;
  float outRad;
  float inRad;

public:
  Ball();
  void draw(SDL_Renderer *renderer);
  void move();
};

#endif