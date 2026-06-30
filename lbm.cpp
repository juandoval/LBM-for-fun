/*
Sanity Check:

1. What are the 9 discrete velocities e_i in D2Q9?
- The 9 discrete velocities e_i in D2Q9 are:
e_0 = (0, 0)
e_1 = (1, 0)
e_2 = (0, 1)
e_3 = (-1, 0)
e_4 = (0, -1)
e_5 = (1, 1)
e_6 = (-1, 1)
e_7 = (-1, -1)
e_8 = (1, -1)

2. What are the 9 weights w_i? (They must sum to 1)
- The 9 weights w_i in D2Q9 are:
w_0 = 4/9
w_1 = 1/9
w_2 = 1/9
w_3 = 1/9
w_4 = 1/9
w_5 = 1/36
w_6 = 1/36
w_7 = 1/36
w_8 = 1/36

3. What is the equilibrium distribution f_i^eq(ρ, u)?
The equilibrium distribution f_i^eq(ρ, u) in D2Q9 is given by the formula:
f_i^eq(ρ, u) = w_i * ρ * [1 + (e_i · u) / c_s^2 + (e_i · u)^2 / (2 * c_s^4) - (u · u) / (2 * c_s^2)]

where:
- ρ is the density
- u is the macroscopic velocity
- c_s is the speed of sound in the lattice (c_s = 1/sqrt(3) for D2Q9)
- e_i is the discrete velocity vector

4. What is the BGK collision step? What does ω (or τ) control physically?
The BGK collision step is given by:
f_i(x, t + Δt) = f_i(x, t) - ω * (f_i(x, t) - f_i^eq(ρ, u))

where:
- ω = 1/τ is the relaxation rate
- τ is the relaxation time, which controls the viscosity of the fluid

5. How do you recover ρ and u from f_i?
The macroscopic density ρ and velocity u can be recovered from the distribution functions f_i as follows:
ρ = Σ_i f_i
ρ * u = Σ_i f_i * e_i
*/

#include "lbm.h"

// Compute f_eq at a single node: what the 9 buckets would look like at local equilibrium
void equilibrium(double f[9], double density, double velocity_x, double velocity_y) {
    for (int i = 0; i < 9; ++i) {
        double eu = e_x[i] * velocity_x + e_y[i] * velocity_y; // e_i · u
        double uu = SQ(velocity_x) + SQ(velocity_y);            // u · u
        f[i] = weight[i] * density * (1.0 + eu/cs2 + SQ(eu)/(2.0*SQ(cs2)) - uu/(2.0*cs2));
    }
}

// BGK collision at every node: relaxes f toward f_eq at rate ω = 1/τ
void collide(double f[NX][NY][9], double tau) {
    double omega = 1.0 / tau;
    for (int x = 0; x < NX; ++x) {
        for (int y = 0; y < NY; ++y) {
            double density, velocity_x, velocity_y;
            macroscopic(f[x][y], density, velocity_x, velocity_y);
            double f_eq[9];
            equilibrium(f_eq, density, velocity_x, velocity_y);
            for (int i = 0; i < 9; ++i)
                f[x][y][i] += -omega * (f[x][y][i] - f_eq[i]);
        }
    }
}

// Streaming: propagate f_i from each node to its neighbour along e_i (periodic boundaries)
void stream(double f[NX][NY][9]) {
    static double f_temp[NX][NY][9];

    for (int x = 0; x < NX; ++x)
        for (int y = 0; y < NY; ++y)
            for (int i = 0; i < 9; ++i)
                f_temp[x][y][i] = f[x][y][i];

    for (int x = 0; x < NX; ++x)
        for (int y = 0; y < NY; ++y)
            for (int i = 0; i < 9; ++i) {
                int next_x = (x + e_x[i] + NX) % NX;
                int next_y = (y + e_y[i] + NY) % NY;
                f[next_x][next_y][i] = f_temp[x][y][i];
            }
}

// Recover ρ = Σ f_i and u = (Σ f_i e_i) / ρ at a single node
void macroscopic(double f[9], double &density, double &velocity_x, double &velocity_y) {
    density = 0.0; velocity_x = 0.0; velocity_y = 0.0;
    for (int i = 0; i < 9; ++i) {
        density    += f[i];
        velocity_x += f[i] * e_x[i];
        velocity_y += f[i] * e_y[i];
    }
    if (density > 0.0) {
        velocity_x /= density;
        velocity_y /= density;
    }
}
