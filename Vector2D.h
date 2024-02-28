#include <iostream>

#pragma once
#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D
{
private:
  float x;
  float y;

public:
  Vector2D();
  Vector2D(float newX, float newY);
  float getX();
  float getY();
  void setX(float newX);
  void setY(float newY);
  Vector2D operator+(Vector2D const &other);
  Vector2D operator-(Vector2D const &other);
  Vector2D operator*(float const &mass);
  Vector2D operator/(float const &mass);
};

#endif
