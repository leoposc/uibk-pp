#pragma once

struct Coordinates
{
    double x;
    double y;
    double z;
};

struct Particle
{
    Coordinates pos;
    Coordinates vel;
    double mass;
};