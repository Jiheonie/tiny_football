#include <string>
#include <SDL2/SDL.h>
#include "Player.h"
#include "Vector2D.h"
#include "Ball.h"
#ifndef UTIlS_H
#define UTIlS_H

void drawCircle(SDL_Renderer *renderer, float centerX, float centerY, float radius);

void SDL_RenderFillCircle(SDL_Renderer *renderer, float centerX, float centerY, float radius);

Vector2D collidePlayerAndBall(Player *p, Ball *b);

Vector2D collidePlayerAndPlayer(Player *p1, Player *p2);

void collidePlayerAndWall(Player *p);

void collideBallAndWall(Ball *b);

bool isRootVector(Vector2D v);

#endif