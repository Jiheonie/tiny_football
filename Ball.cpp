#include "Ball.h"
#include <SDL2/SDL.h>
#include "utils.h"
#include "media.h"

Ball::Ball(SDL_Renderer *renderer, SDL_Surface *screenSurface)
{
  image = loadTexture("assets/ball.png", renderer, screenSurface);
  cenX = 400;
  cenY = 300;
  rad = 50;
  degree = 0;
}

void Ball::draw(SDL_Renderer *renderer)
{
  // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  // SDL_RenderFillCircle(renderer, cenX, cenY, outRad);

  // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  // drawCircle(renderer, cenX, cenY, outRad);
  // drawCircle(renderer, cenX, cenY, inRad);
  // SDL_RenderFillCircle(renderer, cenX, cenY, inRad);

  SDL_Rect ballRect;
  ballRect.w = ballRect.h = rad * 2;
  ballRect.x = cenX - rad;
  ballRect.y = cenY - rad;

  SDL_RenderCopyEx(renderer, image, NULL, &ballRect, degree, NULL, SDL_FLIP_NONE);
}