#include <cmath>
#include <iostream>
#include <unistd.h>
// #include <cstdlib>

#include "Quadrant.h"


#define THETA 1

Quadrant::Quadrant(Coordinates pos, double dim, int depth) : pos(pos), dim(dim), depth(depth) {
    // std::cout << "New quadrant at " << pos.x << " " << pos.y << " " << pos.z << std::endl;
    // std::cout << "Dim: " << dim << std::endl;
    std::cout << "Depth: " << depth << std::endl;
    numberParticles = 0;
    existingParticle = nullptr;
    for (int i = 0; i < 8; i++) {
        quadrants[i] = nullptr;
    }
    sleep(0.01);
}

Quadrant::~Quadrant() {
    // free all quadrants
    for (int i = 0; i < 8; i++) {
        if (quadrants[i] != nullptr) {
            delete quadrants[i];
        }
    }
}

// ------------------------------------------------------

void Quadrant::insertToQuadrant(Particle* newParticle) {
    // std::cout << "Inserting particle no. " << numberParticles << " at " << newParticle->pos.x << " " << newParticle->pos.y << " " << newParticle->pos.z << std::endl;
    int quad;
    Coordinates c;

    if (numberParticles > 1) {
        quad = getQuadrant(newParticle);
        c = getNewCenter(quad);
        // create quad if it doesn't exist
        if (quadrants[quad] == nullptr) {
            if (fabs(c.x - newParticle->pos.x) < 0.00000001) {
                std::cout << "c.x: " << (double) c.x << " newParticle->pos.x: " << newParticle->pos.x << " substraction: " << fabs(c.x - newParticle->pos.x) << " result: " << (abs(c.x - newParticle->pos.x) < 0.00000001) << std::endl;
                std::cout << c.x << c.y << c.z << std::endl;
                throw std::runtime_error("Error in inserting particle (0)");
            }
            quadrants[quad] = new Quadrant(c, dim / 2.0, depth + 1);
        }

        quadrants[quad]->insertToQuadrant(newParticle);

    } else if (numberParticles == 1) {
        // std::cout << "Second Particle in new quadrant inserted at " << newParticle->pos.x << " " << newParticle->pos.y << " " << newParticle->pos.z << std::endl;
        // std::cout << "Existing Particle in new quadrant inserted at " << existingParticle->pos.x << " " << existingParticle->pos.y << " " << existingParticle->pos.z << std::endl;
        quad = getQuadrant(existingParticle);
        c = getNewCenter(quad);

        // create quad if it doesn't exist
        if (quadrants[quad] == nullptr) {
            if (fabs(c.x - existingParticle->pos.x) < 0.00000001) {
                std::cout << "c.x: " << c.x << " existingParticle->pos.x: " << existingParticle->pos.x << " substraction: " << c.x - existingParticle->pos.x <<  std::endl;
                throw std::runtime_error("Error in inserting particle (1)");
            }
            quadrants[quad] = new Quadrant(c, dim / 2.0, depth + 1);
        }

        quadrants[quad]->insertToQuadrant(existingParticle);
        // existingParticle = nullptr;

        quad = getQuadrant(newParticle);
        c = getNewCenter(quad);

        // create quad if it doesn't exist
        if (quadrants[quad] == nullptr) {
            if (fabs(c.x - newParticle->pos.x) < 0.00000001) {
                // throw error
                std::cout << "c.x: " << c.x << " newParticle->pos.x: " << newParticle->pos.x << " substraction: " << c.x - newParticle->pos.x << std::endl;
                throw std::runtime_error("Error in inserting particle (2)");
            }
            quadrants[quad] = new Quadrant(c, dim / 2.0, depth + 1);
        }

        quadrants[quad]->insertToQuadrant(newParticle);

    // Node is empty
    }  else if (numberParticles == 0) {
        existingParticle = newParticle;
        // std::cout << "First Particle in new quadrant inserted at " << existingParticle->pos.x << " " << existingParticle->pos.y << " " << existingParticle->pos.z << std::endl;
    }

    numberParticles++;
}

// ------------------------------------------------------

void Quadrant::computeForce(Particle* p) {
    double force = 0;
    double d = sqrt(pow(p->pos.x - centerMass.x, 2) + pow(p->pos.y - centerMass.y, 2) + pow(p->pos.z - centerMass.z, 2));

    // skip if distance is 0
    if (d < 0.00000001) {
        return;
    }

    if (numberParticles == 1) {

        // compute force
        force = p->mass * existingParticle->mass / pow(d, 2);

        // update velocity of p
        p->vel.x += force * (existingParticle->vel.x - p->pos.x) / d;
        p->vel.y += force * (existingParticle->vel.y - p->pos.y) / d;
        p->vel.z += force * (existingParticle->vel.z - p->pos.z) / d;
    } else {
        // compute force
        if (dim / d < THETA) {
            // compute force between node and particle
            force = mass * p->mass / pow(d, 2);

            // update velocity of p
            p->vel.x += force * (centerMass.x - p->pos.x) / d;
            p->vel.y += force * (centerMass.y - p->pos.y) / d;
            p->vel.z += force * (centerMass.z - p->pos.z) / d;
        } else {
            for (int i = 0; i < 8; i++) {
                if (quadrants[i] != nullptr) {
                    quadrants[i]->computeForce(p);
                }
            }
        }
    }
}

// ------------------------------------------------------

int Quadrant::getQuadrant(Particle* p) {
    if (p->pos.x <= pos.x) {
        if (p->pos.y <= pos.y) {
            if (p->pos.z <= pos.z) {
                return 0;
            } else {
                return 1;
            }
        } else {
            if (p->pos.z <= pos.z) {
                return 2;
            } else {
                return 3;
            }
        }
    } else {
        if (p->pos.y <= pos.y) {
            if (p->pos.z <= pos.z) {
                return 4;
            } else {
                return 5;
            }
        } else {
            if (p->pos.z <= pos.z) {
                return 6;
            } else {
                return 7;
            }
        }

    }
}

// ------------------------------------------------------

Coordinates Quadrant::getNewCenter(int i) {

    switch (i) {
        case 0:
            return {(double) (pos.x - dim / 4.0), (double) (pos.y - dim / 4.0), (double) (pos.z - dim / 4.0)};
        case 1:
            return {(double) (pos.x - dim / 4.0), (double) (pos.y - dim / 4.0), (double) (pos.z + dim / 4.0)};
        case 2:
            return {(double) (pos.x - dim / 4.0), (double) (pos.y + dim / 4.0), (double) (pos.z - dim / 4.0)};
        case 3:
            return {(double) (pos.x - dim / 4.0), (double) (pos.y + dim / 4.0), (double) (pos.z + dim / 4.0)};
        case 4:
            return {(double) (pos.x + dim / 4.0), (double) (pos.y - dim / 4.0), (double) (pos.z - dim / 4.0)};
        case 5:
            return {(double) (pos.x + dim / 4.0), (double) (pos.y - dim / 4.0), (double) (pos.z + dim / 4.0)};
        case 6:
            return {(double) (pos.x + dim / 4.0), (double) (pos.y + dim / 4.0), (double) (pos.z - dim / 4.0)};
        case 7:
            return {(double) (pos.x + dim / 4.0), (double) (pos.y + dim / 4.0), (double) (pos.z + dim / 4.0)};
    }

    std::cerr << "Error in getNewCenter" << std::endl;
    return {0, 0, 0};
}

// ------------------------------------------------------

void Quadrant::computeMassDistribution() {
    if (numberParticles > 1) {
        mass = 0;
        centerMass = {0, 0, 0};
        for (int i = 0; i < 8; i++) {
            if (quadrants[i] != nullptr) {
                quadrants[i]->computeMassDistribution();
                mass += quadrants[i]->mass;
                centerMass.x += quadrants[i]->mass * quadrants[i]->centerMass.x;
                centerMass.y += quadrants[i]->mass * quadrants[i]->centerMass.y;
                centerMass.z += quadrants[i]->mass * quadrants[i]->centerMass.z;
            }
        }
        centerMass.x /= mass;
        centerMass.y /= mass;
        centerMass.z /= mass;

    } else if (numberParticles == 1) {
        mass = existingParticle->mass;
        pos = existingParticle->pos;
        centerMass = existingParticle->pos;
    }
}

// ------------------------------------------------------

void Quadrant::computeForceFromNode(Particle* p) {
    for (int i = 0; i < 8; i++) {
        if (quadrants[i] != nullptr) {
            quadrants[i]->computeForce(p);
        }
    }
}