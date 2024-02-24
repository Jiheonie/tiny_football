#include "Ball.h"
#include <SDL2/SDL.h>
#include "utils.h"
#include "media.h"

Ball::Ball(SDL_Renderer *renderer, SDL_Surface *screenSurface)
{
  image = loadTexture("assets/ball.png", renderer, screenSurface);
  cenX = 300;
  cenY = 100;
  rad = 50;
  degree = 0;
}

void Ball::draw(SDL_Renderer *renderer)
{
  SDL_Rect ballRect;
  ballRect.w = ballRect.h = rad * 2;
  ballRect.x = cenX + rad;
  ballRect.y = cenY - rad;

  SDL_RenderCopyEx(renderer, image, NULL, &ballRect, degree, NULL, SDL_FLIP_NONE);
}