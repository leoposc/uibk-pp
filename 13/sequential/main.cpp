#include <fstream>
#include <iostream>
#include <vector>

#include "BarnesHut.h"
#include "Body.h"
#include "Vector3D.h"

const double G = 6.67430e-11; // gravitational constant
const int n = 1000;            // number of bodies

void runSimulation(std::vector<Body> &bodies, double dt, double theta,
                   int steps) {

  std::ofstream file;
  file.open("data.dat");
  // test if file is open
  if (!file.is_open()) {
    std::cerr << "Error: Could not open file" << std::endl;
    exit(1);
  }

  for (int step = 0; step < steps; ++step) {
    // std::cout << "Step " << step << "\n";
    Vector3D center(size/ 2, size / 2, size / 2);
    double size = 1000; // Assume a cube of size 1000 units

    BarnesHutTree tree(center, size);

    for (Body &body : bodies) {
      tree.insert(&body);
    }

    for (Body &body : bodies) {
      tree.calculateForce(&body, theta);
    }

    for (Body &body : bodies) {
      body.update(dt);
    }

    if (step % 50 == 0) {
      // Optionally: print positions or other data for analysis
      for (const Body &body : bodies) {
        // std::cout << body.position.x << " " << body.position.y << " "
        //      << body.position.z << "\n";
        file << body.position.x << " " << body.position.y << " "
            << body.position.z << std::endl;
      }
      file << "\n" << std::endl;
    }
  }

  file.close();
}

void createBodies(std::vector<Body> &bodies) {
  for (int i = 0; i < n; ++i) {
    Vector3D pos((double)(rand() % 100), (double)(rand() % 100),
                 (double)(rand() % 100));
    Vector3D vel(0.0, 0.0, 0.0);
    double mass = 1; // rand() % 10;
    bodies.push_back(Body(pos, vel, mass));
  }
}

int main() {
  std::vector<Body> bodies;
  bodies.reserve(n);
  createBodies(bodies);

  double dt = 1;
  double theta = 1;
  int steps = 100;

  runSimulation(bodies, dt, theta, steps);

  return 0;
}
