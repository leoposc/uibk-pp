#include "Vector3D.h"
#include <cmath>

Vector3D::Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

Vector3D Vector3D::operator+(const Vector3D &other) const {
  return Vector3D(x + other.x, y + other.y, z + other.z);
}

Vector3D Vector3D::operator-(const Vector3D &other) const {
  return Vector3D(x - other.x, y - other.y, z - other.z);
}

Vector3D Vector3D::operator*(double scalar) const {
  return Vector3D(x * scalar, y * scalar, z * scalar);
}

Vector3D Vector3D::operator/(double scalar) const {
  return Vector3D(x / scalar, y / scalar, z / scalar);
}

double Vector3D::magnitude() const { return std::sqrt(x * x + y * y + z * z); }

Vector3D Vector3D::normalize() const {
  double mag = magnitude();
  return Vector3D(x / mag, y / mag, z / mag);
}
