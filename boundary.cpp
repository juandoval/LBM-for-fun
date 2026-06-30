#include "boundary.h"

// TODO: force left wall nodes to equilibrium at inlet velocity each timestep
void apply_inlet(double f[NX][NY][9], double velocity_x) {
}

// TODO: at solid nodes, reverse the direction of streamed distributions
void apply_bounceback(double f[NX][NY][9]) {
}
