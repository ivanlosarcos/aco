#include <iostream>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <omp.h> // Include the OpenMP library

using namespace std;
using namespace chrono;

double calculatePi(int k_max) {

    double sum = 0.0;

    for (int k=0; k<=k_max; k++) {

        sum = sum + pow(12.0, 0.5)*pow((-1.0/3.0), k)* (1.0/(2.0*k + 1.0));
    }

    return sum;
}


int main() {

    int k_max = 35;
    

    //Walltime
    double walltime=0.;
    high_resolution_clock::time_point begin, end;

    // Calculamos el tiempo en serie
    begin = high_resolution_clock::now(); // Start the timer
    double pi_serial = calculatePi(k_max);
    cout << "Estimated value of pi using serial computing: " << pi_serial << endl;
    end = high_resolution_clock::now();

    walltime = duration_cast<nanoseconds>(end - begin).count();
    cout<< "Tiempo del cálculo en serie: " << walltime <<" ns" << endl;

    return 0;

}