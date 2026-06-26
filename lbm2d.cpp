/*
Sanity Check:

1. What are the 9 discrete velocities e_i in D2Q9? Write them down.
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

3. What is the equilibrium distribution f_i^eq(ρ, u)? Write the formula.
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

#include <iostream>
#include <cmath>

#define SQ(x) ((x)*(x))

// D2Q9 lattice unit direction vectors (e_i)
const int e_x[9] = { 0,  1,  0, -1,  0,  1, -1, -1,  1 };
const int e_y[9] = { 0,  0,  1,  0, -1,  1,  1, -1, -1 };

// D2Q9 weights (must sum to 1)
const double weight[9] = { 4.0/9, 1.0/9, 1.0/9, 1.0/9, 1.0/9, 1.0/36, 1.0/36, 1.0/36, 1.0/36 };

// c_s^2 = 1/3 for D2Q9
const double cs2 = 1.0 / 3.0;

// Initialise f to equilibrium for a given density and velocity
void initialize(double f[9], double density, double velocity_x, double velocity_y) {
    for (int i = 0; i < 9; ++i) {
        double eu = e_x[i] * velocity_x + e_y[i] * velocity_y; // e_i · u
        double uu = SQ(velocity_x) + SQ(velocity_y);            // u · u
        f[i] = weight[i] * density * (1.0 + eu/cs2 + SQ(eu)/(2.0*SQ(cs2)) - uu/(2.0*cs2));
    }
}

// Collision step: Apply BGK operator — relaxes f toward f_eq at rate ω = 1/τ
void collide(double f[9], double tau) {
    // TODO
}

// Streaming step: Propagate f_i to neighbouring nodes along e_i
void stream(double f[9]) {
    // TODO
}

// Recover macroscopic density ρ = Σ f_i and momentum ρu = Σ f_i e_i
void macroscopic(double f[9], double &density, double &velocity_x, double &velocity_y) {
    // TODO
}

int main() {
    double f[9];
    double density    = 1.0;
    double velocity_x = 0.0;
    double velocity_y = 0.0;

    initialize(f, density, velocity_x, velocity_y);

    std::cout << "Initialised f_i:" << std::endl;
    for (int i = 0; i < 9; ++i)
        std::cout << "f[" << i << "] = " << f[i] << std::endl;

    return 0;
}
