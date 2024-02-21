#include <iostream>
#include <cmath>
#include "utils.h"

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
