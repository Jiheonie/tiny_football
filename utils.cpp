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

Vector2D collidePlayerAndBall(Player *p, Ball *b)
{
  Vector2D pPos = p->getPosition();
  Vector2D bPos = b->getPosition();
  float d2 = pow(pPos.getX() - bPos.getX(), 2) + pow(pPos.getY() - bPos.getY(), 2);
  float rSum2 = pow(p->getRadius() + b->getRadius(), 2);

  if (d2 <= rSum2)
  {
    float cX = (pPos.getX() - bPos.getX()) / 2 + bPos.getX();
    float cY = (pPos.getY() - bPos.getY()) / 2 + bPos.getY();
    return Vector2D(cX, cY);
  }
  else
  {
    return Vector2D();
  }
}

Vector2D collidePlayerAndPlayer(Player *p1, Player *p2)
{
  Vector2D p1Pos = p1->getPosition();
  Vector2D p2Pos = p2->getPosition();
  float d2 = pow(p1Pos.getX() - p2Pos.getX(), 2) + pow(p1Pos.getY() - p2Pos.getY(), 2);
  float rSum2 = pow(p1->getRadius() + p2->getRadius(), 2);

  if (d2 <= rSum2)
  {
    float cX = (p1Pos.getX() - p2Pos.getX()) / 2 + p2Pos.getX();
    float cY = (p1Pos.getY() - p2Pos.getY()) / 2 + p2Pos.getY();
    return Vector2D(cX, cY);
  }
  else
  {
    return Vector2D();
  }
}

void collidePlayerAndWall(Player *p)
{
  if (p->getPosition().getX() - 50 <= 0)
  {
    p->setPosition(50, p->getPosition().getY());
  }
  if (p->getPosition().getX() + 50 >= 1280)
  {
    p->setPosition(1230, p->getPosition().getY());
  }
}

void collideBallAndWall(Ball *b)
{
  bool collideX = false;
  bool collideY = false;
  if (b->getPosition().getX() - 50 <= 0)
  {
    b->setPosition(50, b->getPosition().getY());
    collideX = true;
  }
  if (b->getPosition().getX() + 50 >= 1280)
  {
    b->setPosition(1230, b->getPosition().getY());
    collideX = true;
  }
  if (b->getPosition().getY() - 50 <= 0)
  {
    b->setPosition(b->getPosition().getX(), 50);
    collideY = true;
  }
  if (b->getPosition().getY() >= groundY)
  {
    b->setPosition(b->getPosition().getX(), groundY);
    collideY = true;
  }
  if (collideX)
  {
    b->setVelocity(-1 * b->getVelocity().getX(), b->getVelocity().getY());
  }
  if (collideY)
  {
    b->setVelocity(b->getVelocity().getX(), -1 * b->getVelocity().getY());
  }
}

Line makeLineNormal(Vector2D p, Vector2D n)
{
  float c = -1 * (n.getX() * p.getX() + n.getY() * p.getY());
  return Line(n.getX(), n.getY(), c);
}

Line makeLinePoint(Vector2D p1, Vector2D p2)
{
  Vector2D normal = Vector2D(-1 * (p1.getY() - p2.getY()), p1.getX() - p2.getX());
  float c = -1 * (normal.getX() * p1.getX() + normal.getY() * p1.getY());
  return Line(normal.getX(), normal.getY(), c);
}

void collideBallAndGoal(Ball *b)
{
  for (int i = 0; i < 2; i++)
  {
    Goal *g = Goal::_allGoals[i];
    Line l = makeLinePoint(g->getA(), g->getB());
    Vector2D slideshow = l.getSlideshow(b->getPosition());
    float d = pow(b->getPosition().getX() - slideshow.getX(), 2) + pow(b->getPosition().getY() - slideshow.getY(), 2);
    if (b->isTouching(g->getA()))
    {
      b->setVelocity(-1 * b->getVelocity().getX(), -1 * b->getVelocity().getY());
    }
    else if (b->isTouching(slideshow) && slideshow.getY() < g->getA().getY() && slideshow.getY() > g->getA().getY())
    {
      b->setVelocity(0, 0);
    }
  }
}

bool isInGoal(Goal *g, Ball *b)
{
  if (b->getPosition().getY() - 50 > 464)
  {
    if (g->getTeam() == Blue)
    {
      if (b->getPosition().getX() + 50 <= 128)
        return true;
      return false;
    }
    if (b->getPosition().getX() - 50 >= 1152)
      return true;
    return false;
  }
  return false;
}

bool isRootVector(Vector2D v)
{
  return v.getX() == 0 && v.getY() == 0;
}
