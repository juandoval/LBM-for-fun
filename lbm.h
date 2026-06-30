#pragma once
#include "params.h"

#define SQ(x) ((x)*(x))

// D2Q9 lattice unit direction vectors (e_i)
const int    e_x[9]    = { 0,  1,  0, -1,  0,  1, -1, -1,  1 };
const int    e_y[9]    = { 0,  0,  1,  0, -1,  1,  1, -1, -1 };

// D2Q9 weights (must sum to 1)
const double weight[9] = { 4.0/9, 1.0/9, 1.0/9, 1.0/9, 1.0/9, 1.0/36, 1.0/36, 1.0/36, 1.0/36 };

// c_s^2 = 1/3 for D2Q9
const double cs2 = 1.0 / 3.0;

void equilibrium(double f[9], double density, double velocity_x, double velocity_y);
void collide(double f[NX][NY][9], double tau);
void stream(double f[NX][NY][9]);
void macroscopic(double f[9], double &density, double &velocity_x, double &velocity_y);
