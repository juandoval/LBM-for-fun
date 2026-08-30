#pragma once
#include "params.h"
#include "lbm.h"

// Zou-He inlet: force left wall to equilibrium at given velocity
void apply_inlet(double f[NX][NY][9], double velocity_x);

// Zou-He outlet: let flow exit right wall cleanly at given velocity
void apply_outlet(double f[NX][NY][9], double velocity_x);

// Bounce-back: top/bottom walls + solid nodes from mask
void apply_bounceback(double f[NX][NY][9], bool solid[NX][NY]);
