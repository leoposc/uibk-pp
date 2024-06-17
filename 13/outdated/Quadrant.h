#pragma once

#include "Particle.h"

class Quadrant {
    public:
        Quadrant(Coordinates pos, double dim, int depth);

        ~Quadrant();

        void insertToQuadrant(Particle* newParticle);

        void computeForce(Particle* p);

        int getQuadrant(Particle* p);

        Coordinates getNewCenter(int i);

        void computeMassDistribution();

        void computeForceFromNode(Particle* p);
    
    private:
        Coordinates pos;
        double dim;
        int depth;

        int numberParticles;
        Quadrant *quadrants[8];

        double mass;
        Coordinates centerMass;
        Coordinates velocity;
        
        Particle* existingParticle;

};