#pragma once

// Simulation parameters
const int    NX  = 200;  // grid width  (nodes in x)
const int    NY  = 40;   // grid height (nodes in y) — Poiseuille V&V: t_conv ≈ 4900 steps
const int    T   = 20000; // number of timesteps
const double TAU = 0.6;   // relaxation time (controls viscosity)   // relaxation time (controls viscosity)
const double U_BOTTOM = 0.0; // velocity at the bottom wall (0 = static)
const double U_TOP    = 0.0; // velocity at the top wall    (0 = static)

// Body force (lattice units = acceleration, δx/δt²). 0 to disable.
// Poiseuille: BODY_FORCE_X drives streamwise flow. u_max = F*H²/(8*ν), ν = cs²*(τ-0.5).
// Gravity: set BODY_FORCE_Y = -g_lattice (negative = downward).
// Pick F so that u_max/cs < 0.1 (low Mach). Back-calculate: F = 8*ν*u_max/H².
const double BODY_FORCE_X = 1e-6;
const double BODY_FORCE_Y = 0.0;
