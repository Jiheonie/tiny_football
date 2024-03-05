#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(float x, float y, float m)
{
  forces = {Vector2D(0, 1000)};
  // forces = {};
  acceleration = Vector2D();
  velocity = Vector2D();
  position = Vector2D(x, y);
  mass = m;
}

void PhysicsObject::update(float deltaTime)
{
  Vector2D sumOfForces = getSumOfForces();

  acceleration = sumOfForces / mass;

  velocity = velocity + acceleration * deltaTime;

  position = position + velocity * deltaTime;

  if (position.getY() > groundY)
  {
    position.setY(groundY);
    velocity.setY(0);
  }
}

Vector2D PhysicsObject::getSumOfForces()
{
  Vector2D sumOfForces = Vector2D();
  for (int i = 0; i < forces.size(); i++)
  {
    sumOfForces = sumOfForces + forces[i];
  }

  return sumOfForces;
}

void PhysicsObject::resetForces()
{
  while (forces.size() > 1)
  {
    forces.pop_back();
  }
  acceleration = Vector2D();
  velocity.setX(velocity.getX() * 0.99);
}

Vector2D PhysicsObject::getPosition()
{
  return position;
}

void PhysicsObject::setPosition(float x, float y)
{
  position.setX(x);
  position.setY(y);
}

Vector2D PhysicsObject::getVelocity()
{
  return velocity;
}

void PhysicsObject::setVelocity(float x, float y)
{
  velocity.setX(x);
  velocity.setY(y);
}