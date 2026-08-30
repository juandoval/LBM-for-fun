#include "output.h"
#include <fstream>
#include <string>
#include <iomanip>

// Write velocity and density at every node to a CSV for visualisation in Python
void write_csv(double f[NX][NY][9], int timestep) {
    std::string filename = "out/output_" + std::to_string(timestep) + ".csv";
    std::ofstream file(filename);

    file << "x,y,rho,ux,uy\n";

    for (int x = 0; x < NX; ++x) {
        for (int y = 0; y < NY; ++y) {
            double rho, ux, uy;
            macroscopic(f[x][y], rho, ux, uy);
            file << x << "," << y << ","
                 << std::setprecision(6) << rho << ","
                 << std::setprecision(6) << ux  << ","
                 << std::setprecision(6) << uy  << "\n";
        }
    }

    file.close();
}
