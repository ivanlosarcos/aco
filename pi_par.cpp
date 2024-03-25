#include <iostream>
#include <math.h>
#include <omp.h>
#include <chrono>
#include <string>
#include <iomanip>


using namespace std;
using namespace chrono;

double parallelPi(int k_max) {

    double sum = 0.0;

    #pragma omp paralell for reduction(+:sum)

    for (int k=0; k<k_max; k++) {

        sum = sum + pow(12.0, 0.5)*pow((-1.0/3.0), k)* (1.0/(2.0*k + 1.0));
    }

    return sum;
}

int main() {

    int k_max = 35;

    //Walltime
    double walltime=0.;
    high_resolution_clock::time_point begin, end;


    begin = high_resolution_clock::now();
    double pi_par = parallelPi(k_max);
    end = high_resolution_clock::now();

    double duration = duration_cast<nanoseconds>(end-begin).count();

    cout << "Estimated value of pi using parallel computing: " << pi_par << endl;
    cout << "Duration of the computation: " <<duration << "ns" <<endl;
    
    
    
    
    return 0;    
}