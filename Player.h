#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include "Vector2D.h"
#include "PhysicsObject.h"
#include "Ball.h"

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
  bool isShooting;
  Vector2D rootPos;

public:
  static std::vector<Player *> _allPlayers;
  static void reset();
  Player(TeamEnum team, float x, float y, SDL_Renderer *renderer, SDL_Surface *screenSurface);
  float getRadius();
  bool getIsJumpint();
  bool getIsShooting();
  void setIsShooting(bool b);
  bool getTurnLeft();
  void draw(SDL_Renderer *renderer);
  void move(char m);
  void stop();
  void shoot(char d, Ball *b);
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