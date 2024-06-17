#include <iostream>
#include "BarnesHut.h"

#define NUM_PARTICLES 6
#define DIMENSION_SIZE 100.0
#define TIME_STEPS 1000

int main() {

    BarnesHut* bh = new BarnesHut(NUM_PARTICLES, DIMENSION_SIZE);

    bh->createParticles();
    // bh->buildTree();

    for (int i = 0; i < TIME_STEPS; i++) {
        std::cout << "Time step: " << i << std::endl;
        if (i == 0) {
        }

        bh->buildTree();
        bh->updateParticles();
        bh->writeParticles();
        bh->resetTree();
    }

    delete bh;

    return 0;
}