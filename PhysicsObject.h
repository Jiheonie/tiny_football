#include <iostream>
#include <vector>
#include "Vector2D.h"

#pragma once
#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

extern int groundY;

class PhysicsObject
{
protected:
  std::vector<Vector2D> forces;
  Vector2D acceleration;
  Vector2D velocity;
  Vector2D position;
  float mass;

public:
  PhysicsObject(float x, float y, float m);
  void update(float deltaTime);
  Vector2D getSumOfForces();
  void resetForces();
  Vector2D getPosition();
  void setPosition(float x, float y);
  Vector2D getVelocity();
  void setVelocity(float x, float y);
};

#endif