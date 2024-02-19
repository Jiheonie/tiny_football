#include "Ball.h"
#include <SDL2/SDL.h>
#include <cmath>

void drawCircle(SDL_Renderer *renderer, float centerX, float centerY, float radius)
{
  for (float x = -radius; x <= radius; ++x)
  {
    float y = sqrt(radius * radius - x * x);
    SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
    SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);
  }
}

void SDL_RenderFillCircle(SDL_Renderer *renderer, float centerX, float centerY, float radius)
{
  for (float y = -radius; y <= radius; ++y)
  {
    for (float x = -radius; x <= radius; ++x)
    {
      if (x * x + y * y <= radius * radius)
      {
        SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
      }
    }
  }
}

Ball::Ball()
{
  cenX = 400;
  cenY = 300;
  inRad = 100;
  outRad = 200;
}

void Ball::draw(SDL_Renderer *renderer)
{
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillCircle(renderer, cenX, cenY, outRad);

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  drawCircle(renderer, cenX, cenY, outRad);
  drawCircle(renderer, cenX, cenY, inRad);
  SDL_RenderFillCircle(renderer, cenX, cenY, inRad);

}