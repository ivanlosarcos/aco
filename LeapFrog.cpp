#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

double Grav = 6.6726e-11;        // m^3/kg/s^2 (Universal gravitational constant)
double Msun = 1.989e30;          // kg
double Mearth = 5.973e24;        // kg
double Dse = 1.496e11;           // distance Sun-Earth in meters
int nsteps = 10;               // Timesteps per orbit


void LeapFrog(int n)
{
    // Initial Conditions
    double x0 = Dse;
    double y0 = 0;

    double vx0 = 0;
    double vy0 = sqrt(Grav*Msun/Dse);

    double px0 = Mearth*vx0;
    double py0 = Mearth*vy0;

    // Timestep
    double dt = ( 2 * 3.141592654 * Dse / vy0 ) / nsteps;      // fraction of a year

    // Create a file for saving the coordinates
    ofstream outputFile("LF.dat");
    outputFile << x0 << " " << y0 << '\n';

    for (int i = 0; i<n; i++) {
        double x = x0 + dt*px0/(2*Mearth);
        double y = y0 + dt*py0/(2*Mearth);

        double px = px0 - dt * Grav* Msun * Mearth * x / pow(sqrt(x*x + y*y), 3);        // Don't forget the earth!
        double py = py0 - dt * Grav* Msun * Mearth * y / pow(sqrt(x*x + y*y), 3);

        double x2 = x + dt*px/(2*Mearth);
        double y2 = y + dt*py/(2*Mearth);

        outputFile << x2 << " " << y2 << std::endl;

        // Initialise the values for the following step
        x0 = x2;
        y0 = y2;

        px0 = px;
        py0 = py;
    }

    outputFile.close();
}




int main()
{
    LeapFrog( nsteps * 5 );                   // One orbit
}
