#include <stdio.h>
#include <math.h>


void calcular_pi_gauss_legendre(int n, long double *pi) { // n  numero de iteraciones *pi puntero
    long double a = 1.0L;
    long double b = 1.0L / sqrtl(2.0L);
    long double t = 0.25L;
    long double p = 1.0L;
    long double a_aux, b_aux;

    for (int i = 0; i < n; i++) {
        a_aux = (a + b) / 2.0L;
        b_aux = sqrtl(a * b);
        t -= p * powl(a - a_aux, 2);
        p *= 2;

        a = a_aux;
        b = b_aux;
    }

    *pi = powl(a + b, 2) / (4.0L * t);
}

int main() {
    int n;				// n numero de iteraciones
    long double pi;		// aproximacion de pi

    printf("Ingrese el número de iteraciones: ");
    scanf("%d", &n);

    calcular_pi_gauss_legendre(n, &pi);

    printf("Valor aproximado de pi: %.30Lf\n", pi);

    return 0;
}
