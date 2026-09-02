#include <iostream>
#include "params.h"
#include "lbm.h"
#include "boundary.h"
#include "output.h"

int main() {
    // f[x][y][i]: distribution function at node (x,y) for direction i
    // static keeps it off the stack — NX*NY*9 doubles is too large for stack memory
    static double f[NX][NY][9];
    static bool solid[NX][NY];

    // Define cylinder: centre at (NX/4, NY/2), radius NY/4
    for (int x = 0; x < NX; ++x)
        for (int y = 0; y < NY; ++y)
            solid[x][y] = (x - NX/4)*(x - NX/4) + (y - NY/2)*(y - NY/2) < (NY/4)*(NY/4);

    // Seed every node to equilibrium with slight rightward flow to help startup
    for (int x = 0; x < NX; ++x)
        for (int y = 0; y < NY; ++y)
            equilibrium(f[x][y], 1.0, 0.1, 0.0);

    for (int t = 0; t < T; ++t) {
        stream(f);
        apply_bounceback(f, solid, U_BOTTOM, U_TOP);
        apply_inlet(f, 0.1);
        apply_outlet(f, 0.1);
        collide(f, TAU, solid);

        if (t % 100 == 0)
            write_csv(f, t);
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
