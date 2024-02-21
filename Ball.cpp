#include "Ball.h"
#include <SDL2/SDL.h>
#include "utils.h"

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