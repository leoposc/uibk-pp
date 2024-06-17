/*
 * BarnesHut.cpp
 * Created on: 13/06/2024
 * Author: Leopold Schmid
 * based on: https://beltoforion.de/en/barnes-hut-galaxy-simulator/
 */

#include <random>
#include <fstream>
#include <iostream>

#include "Quadrant.h"
#include "BarnesHut.h"

BarnesHut::BarnesHut(int n, double dimension) : n(n), dim(dimension) {
    // open file to keep track of particles
    file.open("data.dat");

    particles.reserve(n);
    Coordinates c = { dim / 2, dim / 2, dim / 2};
    root = new Quadrant(c, dim, 0);
}

BarnesHut::~BarnesHut() {
    file.close();
    delete root;
}

void BarnesHut::buildTree() {
    for (int i = 0; i < n; i++) {
        std::cout << "PARTICLE " << i << " at " << particles[i].pos.x << " " << particles[i].pos.y << " " << particles[i].pos.z << std::endl;
        root->insertToQuadrant(&particles[i]);
    }
}

void BarnesHut::resetTree() {
    root->~Quadrant();
    Coordinates c = { dim / 2, dim / 2, dim / 2};

    root = new Quadrant(c, dim, 0);
}

void BarnesHut::createParticles() {
    for (int i = 0; i < n; i++) {
        int _dim = (int) dim;
        Coordinates c = {((double) (rand() % _dim)), ((double) (rand() % _dim)), ((double) (rand() % _dim))};
        Coordinates v = {0, 0, 0};
        Particle p = {c, v, 1};
        particles.push_back(p);
    }
}

void BarnesHut::updateParticles() {
    root->computeMassDistribution();
    for (int i = 0; i < n; i++) {
        root->computeForceFromNode(&particles[i]);
    }

    updateParticlesPosition();
}

void BarnesHut::updateParticlesPosition() {
    for (int i = 0; i < n; i++) {
        particles[i].pos.x += particles[i].vel.x;
        particles[i].pos.y += particles[i].vel.y;
        particles[i].pos.z += particles[i].vel.z;
    }
}

void BarnesHut::writeParticles() {
    // write to file "particles.txt"
    for (int i = 0; i < n; i++) {
        file << particles[i].pos.x << " " << particles[i].pos.y << " " << particles[i].pos.z << std::endl;
    }
    file << "\n" << std::endl;
}