#pragma once

#include <vector>
#include <fstream>

#include "Particle.h"
#include "Quadrant.h"


class BarnesHut {
    public:

        // Constructor
        BarnesHut(int n, double dim);

        // Destructor
        ~BarnesHut();

        // build the tree
        void buildTree();

        // reset the tree
        void resetTree();

        // create particles
        void createParticles();

        // update the tree
        void updateParticles();

        // update position of particles
        void updateParticlesPosition();

        // print particles in the tree
        void writeParticles();


    private:

        // number of particles
        int n;

        // dimension of the space
        double dim;

        // root node
        Quadrant* root;

        // create vector for particles
        std::vector<Particle> particles;

        // file for output
        std::ofstream file;
};