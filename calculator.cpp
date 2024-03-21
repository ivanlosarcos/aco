#include <stdio.h>
#include <string.h>


#define MAX_LEN 100


double suma(double n, double m) {

    return n+m;
}

double resta(double n, double m) {

    return n-m;
}

double multi(double n, double m) {

    return n*m;
}

double div(double n, double m) {

    if (m != 0){

        return n/m;
    }

    else {
        printf("Error division entre cero\n");
        return 0;
    }
}

int main() {

    double n, m;
    char respuesta[MAX_LEN];

    printf("Que operacionón quieres realizar? (s/r/m/d)");
    scanf("%s", respuesta);

    printf("Con qué numeros quieres realizar la operacion? (n, m)");
    scanf("%lf, %lf", &n, &m);

    if (strcmp(respuesta, "s") ==0) {

        printf("El resultado de la operación es: %.2f\n", suma(n, m));
    }

    if (strcmp(respuesta, "r") ==0) {

        printf("El resultado de la operación es: %.2f\n", resta(n, m));
    }

    if (strcmp(respuesta, "m") ==0) {

        printf("El resultado de la operación es: %.2f\n", multi(n, m));
    }

    if (strcmp(respuesta, "d") ==0) {

        printf("El resultado de la operación es: %.2f\n", div(n, m));
    }


    return 0;
}