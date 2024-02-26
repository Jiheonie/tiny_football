#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(float x, float y, float m)
{
  forces = {Vector2D(0, 10)};
  acceleration = Vector2D(0, 0);
  velocity = Vector2D(0, 0);
  position = Vector2D(x, y);
  mass = m;
}

void PhysicsObject::Update(float deltaTime)
{
  Vector2D sumOfForces{0, 0};
  for (int i = 0; i < forces.size(); i++)
  {
    sumOfForces = sumOfForces + forces[i];
  }
  Vector2D avgVelocity = velocity + acceleration * deltaTime / 2.0f;

  position = position + avgVelocity * deltaTime;

  acceleration = sumOfForces / mass;

  velocity = avgVelocity + acceleration * deltaTime / 2.0f;
}