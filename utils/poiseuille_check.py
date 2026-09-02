"""
Poiseuille validation: compare LBM x-velocity profile vs analytical parabola.

Analytical solution for body-force driven Poiseuille in a channel of height H:
    u(y) = F * y * (H - y) / (2 * nu)       y in [0, H-1] (lattice units)
    u_max = F * H^2 / (8 * nu)              at centreline y = H/2

Run the solver first (output at final timestep), then run this script.
"""

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# params.h
NX        = 200
NY        = 40
TAU       = 0.6
BODY_FORCE = 1e-6
T_SNAP    = 19900  # last csv

cs2 = 1.0 / 3.0
nu  = cs2 * (TAU - 0.5)
H   = NY # channel height in lattice nodes

# Analytical parabola (wall nodes at y=0 and y=NY-1 are no-slip)
y_ana = np.linspace(0, H - 1, 500)
u_ana = BODY_FORCE * y_ana * (H - 1 - y_ana) / (2.0 * nu)
u_max_theory = BODY_FORCE * (H - 1)**2 / (8.0 * nu)

# LBM profile: average over all x at each y (should be x-independent at steady state)
df = pd.read_csv(f"out/output_{T_SNAP}.csv")
profile = df.groupby("y")["ux"].mean().reset_index()

plt.figure(figsize=(6, 5))
plt.plot(u_ana, y_ana, "k-", lw=2, label="Analytical")
plt.plot(profile["ux"], profile["y"], "r--", lw=2, label="LBM")
plt.xlabel("u_x (lattice units)")
plt.ylabel("y (lattice nodes)")
plt.title(f"Poiseuille flow | τ={TAU} | F={BODY_FORCE} | u_max_theory={u_max_theory:.4f}")
plt.legend()
plt.tight_layout()
plt.savefig("poiseuille_check.png", dpi=150)
plt.show()

u_max_lbm = profile["ux"].max()
print(f"Analytical u_max : {u_max_theory:.6f}")
print(f"LBM      u_max   : {u_max_lbm:.6f}")
print(f"Error            : {abs(u_max_lbm - u_max_theory)/u_max_theory * 100:.2f}%")
