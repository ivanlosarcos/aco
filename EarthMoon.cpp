#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

double Grav = 6.6726e-11;        // m^3/kg/s^2 (Universal gravitational constant)
double Msun = 1.989e30;          // kg
double Mearth = 5.973e24;        // kg
double Mmoon = 7.349e22;         // kg
double Dse = 1.496e11;           // distance Sun-Earth in meters
double Dem = 3.844e8;            // distance Earth-Moon in meters
int nsteps = 10000;                  // Timesteps per orbit


void LeapFrog(int n)
{
    // Initial Conditions
    double x0 = Dse;
    double y0 = 0;

    double vx0 = 0;
    double vy0 = sqrt(Grav * Msun / Dse);

    double px0 = Mearth * vx0;
    double py0 = Mearth * vy0;

    // Initial Conditions for Moon
    double xm0 = Dse + Dem;
    double ym0 = 0;

    double vxm0 = sqrt(Grav * Mearth / Dem);  // La velocidad en x es opuesta a la velocidad orbital de la Tierra
    double vym0 = vy0;   // La velocidad en y es igual a la velocidad orbital de la Tierra

    double pxm0 = Mmoon * vxm0;
    double pym0 = Mmoon * vym0;

    // Timestep
    double dt = (2 * 3.141592654 * Dse / vy0) / nsteps;      // fraction of a year

    
    // Create a file for saving the coordinates of Earth
    ofstream earthFile("LFEarth.dat");
    // Create a file for saving the coordinates of Moon
    ofstream moonFile("LFMoon.dat");

    earthFile << x0 << " " << y0 << '\n';
    moonFile << xm0 << " " << ym0 << '\n';

    for (int i = 0; i < n; i++)
    {
        // Update Earth position
        double x = x0 + dt * px0 / (2 * Mearth);
        double y = y0 + dt * py0 / (2 * Mearth);

        // Update Moon position
        double xm = xm0 + dt * pxm0 / (2 * Mmoon);
        double ym = ym0 + dt * pym0 / (2 * Mmoon);

        // Calculate distances to the Sun
        double r_earth_sun = sqrt(x * x + y * y);
        double r_moon_sun = sqrt(xm * xm + ym * ym);
        double r_moon_earth = sqrt((xm-x)*(xm-x) + (ym-y)*(ym-y));

        // Update Earth momentum
        double px = px0 - dt * Grav * Msun * Mearth * x / pow(r_earth_sun, 3) - dt * Grav * Mmoon * Mearth * (x - xm) / pow(r_moon_earth, 3);
        double py = py0 - dt * Grav * Msun * Mearth * y / pow(r_earth_sun, 3) - dt * Grav * Mmoon * Mearth * y / pow(r_moon_earth, 3);

        // Update Moon momentum
        double pxm = pxm0 - dt * Grav * (Msun * Mmoon) * (xm) / pow(r_moon_sun, 3) - dt * Grav * (Mearth * Mmoon) * (xm - x) / pow(r_moon_earth, 3);
        double pym = pym0 - dt * Grav * (Msun * Mmoon) * (ym) / pow(r_moon_sun, 3) - dt * Grav * (Mearth * Mmoon) * (ym - y) / pow(r_moon_earth, 3);

        // Another Step for Earth position
        double x2 = x + dt * px / (2 * Mearth);
        double y2 = y + dt * py / (2 * Mearth);

        // Another Step for Moon position
        double xm2 = xm + dt * pxm / (2 * Mmoon);
        double ym2 = ym + dt * pym / (2 * Mmoon);

        earthFile << x2 << " " << y2 << std::endl;
        moonFile << xm2 << " " << ym2 << std::endl;

        // Initialise the values for the following step
        x0 = x2;
        y0 = y2;

        xm0 = xm2;
        ym0 = ym2;

        px0 = px;
        py0 = py;

        pxm0 = pxm;
        pym0 = pym;
    }
    // Close the files
    earthFile.close();
    moonFile.close();
}

int main()
{
    LeapFrog(nsteps * 10);                   // One orbit
    return 0;
}