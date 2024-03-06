#include <SDL2/SDL.h>
#include <cmath>
#include "Ball.h"
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
  printf("%f---%f\n", x, velocity.getX());
  if (x * velocity.getX() <= 0)
  {
    velocity.setX(-1 * velocity.getX());
  }
  if (y * velocity.getY() <= 0)
    velocity.setY(-1 * velocity.getY());

  forces.push_back(Vector2D(x, y));
}

void Ball::update(float dt)
{

  collideBallAndWall(this);
  collideBallAndGoal(this);
  PhysicsObject::update(dt);
}

bool Ball::isTouching(Vector2D p)
{
  return pow(p.getX() - position.getX(), 2) + pow(p.getY() - position.getY(), 2) - pow(rad, 2) <= 0;
}

void Ball::reset() {
  position = Vector2D(640, 300);
  velocity = Vector2D(0, 0);
  acceleration = Vector2D(0, 0);
}