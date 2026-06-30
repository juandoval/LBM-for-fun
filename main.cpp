#include <iostream>
#include "params.h"
#include "lbm.h"
#include "boundary.h"
#include "output.h"

int main() {
    // f[x][y][i]: distribution function at node (x,y) for direction i
    // static keeps it off the stack — NX*NY*9 doubles is too large for stack memory
    static double f[NX][NY][9];

    // Seed every node to equilibrium (ρ=1, u=0) — fluid at rest
    for (int x = 0; x < NX; ++x)
        for (int y = 0; y < NY; ++y)
            equilibrium(f[x][y], 1.0, 0.0, 0.0);

    for (int t = 0; t < T; ++t) {
        stream(f);
        collide(f, TAU);
    }

    // Print macroscopic state at the centre node as a sanity check
    double rho, ux, uy;
    macroscopic(f[NX/2][NY/2], rho, ux, uy);
    std::cout << "Centre node after " << T << " steps:" << std::endl;
    std::cout << "  density    = " << rho << std::endl;
    std::cout << "  velocity_x = " << ux  << std::endl;
    std::cout << "  velocity_y = " << uy  << std::endl;

    return 0;
}
