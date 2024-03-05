#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include "Vector2D.h"
#include "PhysicsObject.h"

enum TeamEnum
{
  Blue,
  Red
};

class Player : public PhysicsObject
{
private:
  int team;
  SDL_Texture *image;
  float rad;
  bool turnLeft;
  bool isMoving;
  bool isJumping;

public:
  static std::vector<Player *> _allPlayers;
  Player(TeamEnum team, float x, float y, SDL_Renderer *renderer, SDL_Surface *screenSurface);
  float getRadius();
  bool getIsJumpint();
  bool getTurnLeft();
  void draw(SDL_Renderer *renderer);
  void move(char m);
  void stop();
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
  Player *getPlayerByIdx(int i);
  void drop();
  void switchPlayer();
  void draw(SDL_Renderer *renderer);
  void update(float dt);
};

#endif