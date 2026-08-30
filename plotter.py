import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

NX, NY = 400, 100
TAU    = 0.6
U_IN   = 0.1
D      = NY // 2        # cylinder diameter in nodes (2 * radius)
nu     = (1.0/3.0) * (TAU - 0.5)
Re     = U_IN * D / nu


# CMD argument for the iteration number
# Usage: python plotter.py <iteration_number>
import sys
iteration = sys.argv[1]

# Change this to a later timestep to see developed flow
df = pd.read_csv("out/output_" + iteration + ".csv")

ux    = df.pivot(index='y', columns='x', values='ux').values
uy    = df.pivot(index='y', columns='x', values='uy').values
speed = np.sqrt(ux**2 + uy**2)

# Mask cylinder nodes so they show as black
cx, cy, r = NX//4, NY//2, NY//4
Y, X = np.ogrid[:NY, :NX]
cylinder_mask = (X - cx)**2 + (Y - cy)**2 < r**2
speed[cylinder_mask] = np.nan

plt.figure(figsize=(14, 4))
plt.imshow(speed, origin='lower', cmap='jet', vmin=0, vmax=0.15)
plt.colorbar(label='velocity magnitude')
plt.title(f'Flow around cylinder  |  Re = {Re:.1f}  |  TAU = {TAU}  |  U = {U_IN}')
plt.tight_layout()
plt.show()
