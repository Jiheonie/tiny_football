#include "Vector2D.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Vector2D::Vector2D() : x(0), y(0) {}

Vector2D::Vector2D(float newX, float newY) : x(newX), y(newY) {}

float Vector2D::getX()
{
  return x;
}

float Vector2D::getY()
{
  return y;
}

void Vector2D::setX(float newX)
{
  x = newX;
}

void Vector2D::setY(float newY)
{
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

Vector2D Vector2D::operator*(float const &mass)
{
  return Vector2D(x * mass, y * mass);
}

Vector2D Vector2D::operator/(float const &mass)
{
  return Vector2D(x / mass, y / mass);
}