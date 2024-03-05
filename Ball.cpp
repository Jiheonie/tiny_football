#include "Ball.h"
#include <SDL2/SDL.h>
#include "utils.h"
#include "media.h"

Ball::Ball(SDL_Renderer *renderer, SDL_Surface *screenSurface)
    : PhysicsObject(640, 300, 10)
{
  image = loadTexture("assets/ball.png", renderer, screenSurface);
  rad = 50;
  degree = 0;
}

float Ball::getRadius()
{
  return rad;
}

void Ball::draw(SDL_Renderer *renderer)
{
  SDL_Rect ballRect;
  ballRect.w = ballRect.h = rad * 2;
  ballRect.x = position.getX() - rad;
  ballRect.y = position.getY() - rad;

  SDL_RenderCopyEx(renderer, image, NULL, &ballRect, degree, NULL, SDL_FLIP_NONE);
}

void Ball::touch(float x, float y)
{
  if (velocity.getX() != 0 || velocity.getY() != 0)
  {
    velocity.setX(0);
    velocity.setY(0);
    acceleration.setX(0);
    acceleration.setY(0);
  }
  forces.pop_back();
  forces.push_back(Vector2D(x, y));
}