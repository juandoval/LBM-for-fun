/*
 * LBM 2D Solver: D2Q9, BGK collision
 *
 * CASES (edit params.h + this file):
 *
 *   Poiseuille flow (current)
 *     - No obstacles  (solid[x][y] = false)
 *     - Periodic in x (stream() default: no inlet/outlet calls)
 *     - No-slip walls at y=0, y=NY-1 (apply_bounceback)
 *     - Body force drives flow: BODY_FORCE_X > 0, BODY_FORCE_Y = 0
 *     - Seed: equilibrium at rest (ux=0)
 *
 *   Couette flow
 *     - No obstacles
 *     - Periodic in x
 *     - Moving top wall: set U_TOP != 0 in params.h (apply_bounceback handles it)
 *     - No body force (BODY_FORCE_X = 0)
 *     - Analytical solution: u(y) = U_TOP * y / (NY-1)
 *
 *   Cylinder in channel
 *     - Cylinder obstacle: uncomment solid[x][y] = circle equation below
 *     - Zou-He inlet/outlet: uncomment apply_inlet / apply_outlet calls
 *     - No body force
 *     - Seed: equilibrium at inlet velocity (ux=0.1)
 *
 * BOUNDARY CONDITIONS (boundary.cpp):
 *   apply_inlet(f, ux)            Zou-He velocity BC at x=0
 *   apply_outlet(f, ux)           Zou-He velocity BC at x=NX-1
 *   apply_bounceback(f, solid,    Half-way bounce-back: top/bottom walls
 *                    U_BOTTOM,    + solid obstacle nodes (cylinder mask)
 *                    U_TOP)       U_BOTTOM/U_TOP != 0 → moving wall (Couette)
 *
 * BODY FORCE (params.h):
 *   BODY_FORCE_X    x-direction (streamwise, Poiseuille / pressure gradient)
 *   BODY_FORCE_Y    y-direction (gravity if negative)
 *   Both 0 → no body force
 *
 * OUTPUT:
 *   out/output_<t>.csv    x, y, rho, ux, uy — every 100 steps
 *   poiseuille_check.py   overlays LBM vs analytical parabola
 *   plotter.py            flow-field heatmap (cylinder case)
 */

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

    // Poiseuille case: no obstacles, body force drives the flow.
    // Walls at y=0 and y=NY-1 are no-slip (bounce-back). x is periodic (stream() default).
    for (int x = 0; x < NX; ++x)
        for (int y = 0; y < NY; ++y)
            // solid[x][y] = (x - NX/4)*(x - NX/4) + (y - NY/2)*(y - NY/2) < (NY/4)*(NY/4); // Cylinder obstacle
            solid[x][y] = false;

    // Seed to rest equilibrium — body force will accelerate from zero
    for (int x = 0; x < NX; ++x)
        for (int y = 0; y < NY; ++y)
            equilibrium(f[x][y], 1.0, 0.0, 0.0);

    for (int t = 0; t < T; ++t) {
        stream(f);
        apply_bounceback(f, solid, U_BOTTOM, U_TOP);
        // No inlet/outlet: x is periodic, flow driven by BODY_FORCE
        // apply_inlet(f, 0.1);
        // apply_outlet(f, 0.1);
        collide(f, TAU, solid, BODY_FORCE_X, BODY_FORCE_Y);

        if (t % 100 == 0) {
            write_csv(f, t);
            std::cout << "t = " << t << " / " << T << "\r" << std::flush;
        }
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
