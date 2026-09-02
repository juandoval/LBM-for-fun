#include "boundary.h"

// Zou-He inlet: sets rightward directions at x=0 to enforce velocity_x
void apply_inlet(double f[NX][NY][9], double velocity_x) {
    for (int j = 0; j < NY; ++j) {
        double density = f[0][j][0] + f[0][j][2] + f[0][j][4] + 2*(f[0][j][3] + f[0][j][6] + f[0][j][7]);
        f[0][j][1] = f[0][j][3] + (2.0/3.0) * density * velocity_x;
        f[0][j][5] = f[0][j][7] + (1.0/6.0) * density * velocity_x;
        f[0][j][8] = f[0][j][6] + (1.0/6.0) * density * velocity_x;
    }
}

// Zou-He outlet: sets leftward directions at x=NX-1 to let flow exit cleanly
void apply_outlet(double f[NX][NY][9], double velocity_x) {
    for (int j = 0; j < NY; ++j) {
        double density = f[NX-1][j][0] + f[NX-1][j][2] + f[NX-1][j][4] + 2*(f[NX-1][j][1] + f[NX-1][j][5] + f[NX-1][j][8]);
        f[NX-1][j][3] = f[NX-1][j][1] - (2.0/3.0) * density * velocity_x;
        f[NX-1][j][7] = f[NX-1][j][5] - (1.0/6.0) * density * velocity_x;
        f[NX-1][j][6] = f[NX-1][j][8] - (1.0/6.0) * density * velocity_x;
    }
}

// Bounce-back: reverses distributions at top/bottom walls and solid nodes
void apply_bounceback(double f[NX][NY][9], bool solid[NX][NY], double u_bottom, double u_top) {
    double temp;

    // Top wall (y=NY-1): reverse downward-pointing directions back up
    for (int x = 0; x < NX; ++x) {
        double rho = f[x][NY-1][0] + f[x][NY-1][1] + f[x][NY-1][2] + f[x][NY-1][3] + f[x][NY-1][4]
                   + f[x][NY-1][5] + f[x][NY-1][6] + f[x][NY-1][7] + f[x][NY-1][8];
        double mc = (1.0/6.0) * rho * u_top;
        f[x][NY-1][4] = f[x][NY-1][2];
        f[x][NY-1][7] = f[x][NY-1][5] + mc;
        f[x][NY-1][8] = f[x][NY-1][6] - mc;
    }

    // Bottom wall (y=0): reverse upward-pointing directions back down
    for (int x = 0; x < NX; ++x) {
        double rho = f[x][0][0] + f[x][0][1] + f[x][0][2] + f[x][0][3] + f[x][0][4]
                   + f[x][0][5] + f[x][0][6] + f[x][0][7] + f[x][0][8];
        double mc = (1.0/6.0) * rho * u_bottom;
        f[x][0][2] = f[x][0][4];
        f[x][0][5] = f[x][0][7] + mc;
        f[x][0][6] = f[x][0][8] - mc;
    }

    // Solid nodes (cylinder): swap each direction with its opposite
    for (int x = 0; x < NX; ++x) {
        for (int y = 0; y < NY; ++y) {
            if (solid[x][y]) {
                temp = f[x][y][1]; f[x][y][1] = f[x][y][3]; f[x][y][3] = temp;
                temp = f[x][y][2]; f[x][y][2] = f[x][y][4]; f[x][y][4] = temp;
                temp = f[x][y][5]; f[x][y][5] = f[x][y][7]; f[x][y][7] = temp;
                temp = f[x][y][6]; f[x][y][6] = f[x][y][8]; f[x][y][8] = temp;
            }
        }
    }
}
