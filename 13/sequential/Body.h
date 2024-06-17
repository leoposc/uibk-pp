#pragma once

#include "Vector3D.h"

class Body {
public:
  Vector3D position;
  Vector3D velocity;
  Vector3D force;
  double mass;

  Body(Vector3D pos, Vector3D vel, double mass);

  void update(double dt);

  void addForce(const Vector3D &f);
};
