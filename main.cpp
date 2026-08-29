#include <iostream>
#include "params.h"
#include "lbm.h"
#include "boundary.h"
#include "output.h"

int main() {
    // f[x][y][i]: distribution function at node (x,y) for direction i

    // (Grid) NX columns and NY rows, i (9) buckets each node

    // static keeps it off the stack, NX*NY*9 doubles is too large for stack memory
    static double f[NX][NY][9];

    // seed every node to equilibrium (w/ ρ=1, u=0, v=0)

    // initialize x as 0, while x < NX is true, increment x each loop (same for NY)
    // fluid at rest
    for (int x = 0; x < NX; ++x)
        for (int y = 0; y < NY; ++y)

            // compute equilibrium distribution for given x and y, 

            // and distribution function values:             
            // f[x][y][i] how much fluid mass is moving in direction i at node (x,y) (weight/amount)
            // f[x][y][1] how much is headed to this node from the left

            // with initial conditions; rho = 1, u = 0 and v = 0

            equilibrium(f[x][y], 1.0, 0.0, 0.0);

            // equilibrium distribution gives 9 values at each node (x,y)


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
