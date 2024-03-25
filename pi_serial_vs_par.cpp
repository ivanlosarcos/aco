#include <iostream>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <omp.h> // Include the OpenMP library

using namespace std;
using namespace chrono;


double calculatePiSerial(int k_max) {
    double sum = 0.0;

    for (int k=0; k<=k_max; k++) {

        sum = sum + pow(12.0, 0.5)*pow((-1.0/3.0), k)* (1.0/(2.0*k + 1.0));
    }

    return sum;
}

double calculatePiParallel(int k_max) {
    double sum = 0.0;
    #pragma omp parallel for reduction(+:sum)

    for (int k=0; k<=k_max; k++) {

        sum = sum + pow(12.0, 0.5)*pow((-1.0/3.0), k)* (1.0/(2.0*k + 1.0));
    }

    return sum;
}

int main() {
    int k_max = 35;

    // Calculating Pi in serial
    high_resolution_clock::time_point start_serial = high_resolution_clock::now();
    double pi_serial = calculatePiSerial(k_max);
    high_resolution_clock::time_point end_serial = high_resolution_clock::now();
    auto duration_serial = duration_cast<nanoseconds>(end_serial - start_serial).count();

    // Calculating Pi in parallel
    high_resolution_clock::time_point start_parallel = high_resolution_clock::now();
    double pi_parallel = calculatePiParallel(k_max);
    high_resolution_clock::time_point end_parallel = high_resolution_clock::now();
    auto duration_parallel = duration_cast<nanoseconds>(end_parallel - start_parallel).count();

    // Output results
    cout << "Pi calculated in serial: " << pi_serial << endl;
    cout << "Time taken for serial calculation: " << duration_serial << " ns" << endl;
    cout << "Pi calculated in parallel: " << pi_parallel << endl;
    cout << "Time taken for parallel calculation: " << duration_parallel << " ns" << endl;

    return 0;
}
