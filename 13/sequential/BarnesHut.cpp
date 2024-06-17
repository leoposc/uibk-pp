#include <vector>

#include "BarnesHut.h"
#include "Body.h"
#include "Vector3D.h"

BarnesHutTree::BarnesHutTree(Vector3D center, double size)
    : center(center), size(size), massCenter(0, 0, 0), totalMass(0),
      body(nullptr), isExternal(true) {
  for (int i = 0; i < 8; ++i)
    children[i] = nullptr;
}

BarnesHutTree::~BarnesHutTree() {
  for (int i = 0; i < 8; ++i)
    delete children[i];
}

int BarnesHutTree::getOctant(Vector3D pos) {
  int oct = 0;
  if (pos.x >= center.x)
    oct |= 4;
  if (pos.y >= center.y)
    oct |= 2;
  if (pos.z >= center.z)
    oct |= 1;
  return oct;
}

void BarnesHutTree::insert(Body *b) {
  if (body == nullptr && totalMass == 0) {
    body = b;
    massCenter = b->position;
    totalMass = b->mass;
  } else {
    if (isExternal) {
      isExternal = false;
      Body *oldBody = body;
      body = nullptr;
      insertIntoChild(oldBody);
    }
    insertIntoChild(b);
    updateCenterOfMass(b);
  }
}

void BarnesHutTree::insertIntoChild(Body *b) {
  int oct = getOctant(b->position);
  Vector3D newCenter = center;
  double newSize = size / 2;
  newCenter.x += (oct & 4) ? newSize / 2 : -newSize / 2;
  newCenter.y += (oct & 2) ? newSize / 2 : -newSize / 2;
  newCenter.z += (oct & 1) ? newSize / 2 : -newSize / 2;

  if (children[oct] == nullptr) {
    children[oct] = new BarnesHutTree(newCenter, newSize);
  }
  children[oct]->insert(b);
}

void BarnesHutTree::updateCenterOfMass(Body *b) {
  totalMass += b->mass;
  massCenter = (massCenter * totalMass + b->position * b->mass) / (totalMass);
}

void BarnesHutTree::calculateForce(Body *b, double theta) {
  if (body == b)
    return;
  Vector3D d = massCenter - b->position;
  double distance = d.magnitude();
  if (isExternal || (size / distance) < theta) {
    double force = (b->mass * totalMass) / (distance * distance);
    b->addForce(d.normalize() * force);
  } else {
    for (int i = 0; i < 8; ++i) {
      if (children[i])
        children[i]->calculateForce(b, theta);
    }
  }
}
