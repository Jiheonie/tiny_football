#include "Goal.h"
#include "media.h"

Goal::Goal(TeamEnum t, float x, float y, SDL_Renderer *renderer, SDL_Surface *screenSurface)
{
  team = t;
  image = loadTexture("assets/goal.png", renderer, screenSurface);
  rect.x = x;
  rect.y = y;
  rect.w = 128;
  rect.h = 256;
}

void Goal::draw(SDL_Renderer *renderer) {
  SDL_RendererFlip flip = (team == Blue) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
  SDL_RenderCopyEx(renderer, image, NULL, &rect, 0, NULL, flip);
}
