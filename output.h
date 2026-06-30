#pragma once
#include "params.h"
#include "lbm.h"

// TODO: write density and velocity fields to a CSV file for visualisation
void write_csv(double f[NX][NY][9], int timestep);
