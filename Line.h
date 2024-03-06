#pragma once
#include <iostream>
#include "Vector2D.h"
#ifndef LINE_H
#define LINE_H

class Line
{
private:
  float a;
  float b;
  float c;

public:
  Line(float a0, float b0, float c0);
  bool isParallel(Line const &l);
  Vector2D getSlideshow(Vector2D p);
  Vector2D getIntersection(Line const &l);
  Vector2D getReflect(Vector2D v);
};

#endif
