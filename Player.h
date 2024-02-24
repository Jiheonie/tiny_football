#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>

enum TeamEnum
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
  bool turnLeft;

public:
  Player(TeamEnum team, float x, float y, SDL_Renderer *renderer, SDL_Surface *screenSurface);
  void draw(SDL_Renderer *renderer);
  void move(char m);
  void shoot();
};

class Team
{
private:
  std::vector<Player *> players;
  TeamEnum color;
  int selectedNumber;

public:
  Team(TeamEnum c);
  Player *selectPlayer();
  void addPlayer(Player *p);
  void switchPlayer();
  void draw(SDL_Renderer *renderer);
};

#endif