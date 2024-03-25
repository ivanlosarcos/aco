#include <iostream>
#include <math.h>
#include <omp.h>
#include <chrono>
#include <string>
#include <iomanip>
#include <map>


using namespace std;
using namespace chrono;

double parallelPi(int k_max, int n) {

    double sum = 0.0;

    #pragma omp paralell for reduction(+:sum) num_threads(n)

    for (int k=0; k<k_max; k++) {

        sum = sum + pow(12.0, 0.5)*pow((-1.0/3.0), k)* (1.0/(2.0*k + 1.0));
    }

    return sum;
}

int main() {
    // Crear un diccionario donde las claves y los valores son enteros
    std::map<int, int> myMap;

    int k_max = 35;
    int n = 9;

    //Walltime
    double walltime=0.;
    high_resolution_clock::time_point begin, end;

    for (int i = 1; i<n; i++) {

        begin = high_resolution_clock::now();
        double pi_par = parallelPi(k_max, i);
        end = high_resolution_clock::now();

        double duration = duration_cast<nanoseconds>(end-begin).count();

        myMap[i] = duration;

        cout << "The duration of the computation using " << i << " threads is " << duration << "ns" <<endl;

    }

    // Busquemos ahora lo más optimo

    int minKey = -1;
    double minValue = std::numeric_limits<double>::max(); // Inicializa con el valor máximo posible para double

    for (const auto& pair : myMap) {

        if (pair.second < minValue) {

            minKey = pair.first;
            minValue = pair.second;
        }
    }
    cout<<endl;
    cout << "The most optimal number of threads is " << minKey <<  " with a duration of "
     << minValue  <<endl;  
    cout<<endl;
    
    
    return 0;    
}