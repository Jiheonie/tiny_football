#include "Line.h"
#include "utils.h"

Line::Line(float a0, float b0, float c0) : a(a0), b(b0), c(c0) {}

bool Line::isParallel(Line const &l)
{
  if ((a == 0 && l.a == 0) && (b != 0 || l.b != 0))
    return true;
  if ((b == 0 && l.b == 0) && (a != 0 || l.a != 0))
    return true;
  if (a / l.a == b / l.b)
    return true;
  return false;
}

Vector2D Line::getSlideshow(Vector2D p)
{
  Vector2D normal = Vector2D(-b, a);
  Line squaredLine = makeLineNormal(p, normal);
  return getIntersection(squaredLine);
}

Vector2D Line::getIntersection(Line const &l)
{
  if (!isParallel(l))
  {
    if (a == 0 && b == 0)
      return Vector2D();
    if (a == 0)
    {
      float cT = c * l.b / b;
      float x = (l.c - cT) / l.a;
      float y = -c / b;
      return Vector2D(x, y);
    }
    if (b == 0)
    {
      float x = -c / a;
      float y = (-l.c - l.a * x) / l.b;
      return Vector2D(x, y);
    }
    float aT = a * l.b / b;
    float cT = c * l.b / b;
    float x = (l.c - cT) / (l.a - aT);
    float y = (-c - a * x) / b;
    return Vector2D(x, y);
  }
  return Vector2D();
}

// Vector2D Line::getReflect(Vector2D v)
// {

// }