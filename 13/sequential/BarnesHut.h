#pragma once

#include <vector>

#include "Body.h"
#include "Vector3D.h"

class BarnesHutTree {
public:
  // Define bounds and center of mass
  Vector3D center;
  double size;
  Vector3D massCenter;
  double totalMass;
  Body *body;
  bool isExternal;

  // Children
  BarnesHutTree *children[8];

  BarnesHutTree(Vector3D center, double size);

  ~BarnesHutTree();

  int getOctant(Vector3D pos);

  void insert(Body *b);

  void insertIntoChild(Body *b);

  void updateCenterOfMass(Body *b);

  void calculateForce(Body *b, double theta);
};
