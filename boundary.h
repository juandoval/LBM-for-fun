#pragma once
#include "params.h"
#include "lbm.h"

// TODO: inlet boundary: force left wall to equilibrium at a given velocity
void apply_inlet(double f[NX][NY][9], double velocity_x);

// TODO: bounce-back boundary: reverse streamed distributions at solid nodes
void apply_bounceback(double f[NX][NY][9]);
