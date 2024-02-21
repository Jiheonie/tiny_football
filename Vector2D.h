#include <iostream>

#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D
{
private:
  float x;
  float y;

public:
  Vector2D(float newX, float newY);
  Vector2D operator+(Vector2D const& other);
  Vector2D operator-(Vector2D const& other);
};

#endif
