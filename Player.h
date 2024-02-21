#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <SDL2/SDL.h>

class Player
{
private:
  SDL_Surface *image =  
  float cenX;
  float cenY;
  float rad;

public:
  Player(float cenX);
  void move();
  void draw(SDL_Renderer *renderer);
};

#endif