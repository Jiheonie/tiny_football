#include "Goal.h"
#include "media.h"

std::vector<Goal *> Goal::_allGoals = {};

Goal::Goal(TeamEnum t, float x, float y, float ax, float ay, float bx, float by, SDL_Renderer *renderer, SDL_Surface *screenSurface)
{
  team = t;
  image = loadTexture("assets/goal.png", renderer, screenSurface);
  rect.x = x;
  rect.y = y;
  rect.w = 128;
  rect.h = 256;
  a = Vector2D(ax, ay);
  b = Vector2D(bx, by);

  _allGoals.push_back(this);
}

void Goal::draw(SDL_Renderer *renderer)
{
  SDL_RendererFlip flip = (team == Blue) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
  SDL_RenderCopyEx(renderer, image, NULL, &rect, 0, NULL, flip);
}

TeamEnum Goal::getTeam() {
  return team;
}

Vector2D Goal::getA() {
  return a;
}

Vector2D Goal::getB() {
  return b;
}