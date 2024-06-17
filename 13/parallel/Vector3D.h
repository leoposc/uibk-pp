#pragma once

#include <cmath>

class Vector3D {
public:
  double x, y, z;

  Vector3D(double x = 0, double y = 0, double z = 0);

  Vector3D operator+(const Vector3D &other) const;

  Vector3D operator-(const Vector3D &other) const;

  Vector3D operator*(double scalar) const;

  Vector3D operator/(double scalar) const;

  double magnitude() const;

  Vector3D normalize() const;
};
