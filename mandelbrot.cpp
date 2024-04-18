#include <iostream>
#include <fstream>
#include <math.h>
#include <omp.h>
#include <chrono>
#include <string>
#include <iomanip>
#include <map>
#include <complex>

using namespace std;
using namespace chrono;


//// Function to check divergence

bool checkDiv(const complex<double>& c, int max_iterations) {

    std::complex<double> z = 0;

    for (int i=0; i<max_iterations; i++) {

        z = z*z + c;

        if (abs(z) > 2){

            return true; // divergence
        }
    }
    return false; // No divergence
}


int main(){

    const int NPOINTS_PER_DIMENSION = 1000; // Dimensions that our arrays c_img and c_real are going to have
    const int NMAXITERATIONS = 100; // Maximum number of iterations from which we would consider the series NOT convergent

    const double C_real_min = -2.0;
    const double C_real_max = 0.5;

    const double C_img_min = -1.1;
    const double C_img_max = 1.1;

    double *c_real = new double[NPOINTS_PER_DIMENSION];  // Array where all the real values of C from C_real_min to C_real_max are going to be
    double *c_img = new double[NPOINTS_PER_DIMENSION];  // Array where all the imaginary values of C from C_img_min to C_img_max are going to be

    
    // Get the maximum number of available threads
    int max_threads = omp_get_max_threads();
    
    #pragma omp paralell num_threads(max_threads) // parallel computing using the maximum number of threads

    for (int i = 0; i < NPOINTS_PER_DIMENSION; i++){

        for (int j = 0; j < NPOINTS_PER_DIMENSION; j++){

            c_real[i] = C_real_min + (C_real_max - C_real_min)*i/(NPOINTS_PER_DIMENSION - 1) ;
            c_img[j] = C_img_min + (C_img_max - C_img_min)*j/(NPOINTS_PER_DIMENSION-1)  ;

        }
    }

    std::ofstream outputFile("mandelbrot.dat");

    // also paralellized
    #pragma omp paralell num_threads(max_threads)
    for (int i = 0; i < NPOINTS_PER_DIMENSION; i++) {

        for (int j = 0; j < NPOINTS_PER_DIMENSION; j++){

            if (checkDiv(std::complex<double> (c_real[i], c_img[j]), NMAXITERATIONS) == false){

                outputFile << c_real[i] << " " << c_img[j] << std::endl;

            }

        }
    }
    outputFile.close();

    // Dealocate the arrays to save memory
    
    delete[] c_real;
    delete[] c_img;


    return 0;

}