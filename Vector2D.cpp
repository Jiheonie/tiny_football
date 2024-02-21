#include "Vector2D.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Vector2D::Vector2D(float newX, float newY)
{
  x = newX;
  y = newY;
}

Vector2D Vector2D::operator+(Vector2D const &other)
{
  float newX = x + other.x;
  float newY = y + other.y;
  return Vector2D(newX, newY);
}

Vector2D Vector2D::operator-(Vector2D const &other)
{
  float newX = x - other.x;
  float newY = y - other.y;
  return Vector2D(newX, newY);
}