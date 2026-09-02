#pragma once

// Simulation parameters
const int    NX  = 400;  // grid width  (nodes in x)
const int    NY  = 100;  // grid height (nodes in y)
const int    T   = 10000; // number of timesteps
const double TAU = 0.6;   // relaxation time (controls viscosity)
const double U_BOTTOM = 0.0; // velocity at the bottom wall (0 = static)
const double U_TOP    = 0.0; // velocity at the top wall    (0 = static)
