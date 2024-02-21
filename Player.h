#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <SDL2/SDL.h>

enum Team
{
  Blue,
  Red
};

class Player
{
private:
  int team;
  SDL_Texture *image;
  float cenX;
  float cenY;
  float rad;

public:
  Player(Team team, float x, float y, SDL_Renderer *renderer, SDL_Surface *screenSurface);
  void move();
  void draw(SDL_Renderer *renderer);
};

#endif