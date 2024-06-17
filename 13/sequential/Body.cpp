#include "Body.h"
#include "Vector3D.h"

Body::Body(Vector3D pos, Vector3D vel, double mass)
    : position(pos), velocity(vel), force(0, 0, 0), mass(mass) {}

void Body::update(double dt) {
  velocity = velocity + (force / mass) * dt;
  position = position + velocity * dt;
  force = Vector3D(0, 0, 0); // reset force
}

void Body::addForce(const Vector3D &f) { force = force + f; }
