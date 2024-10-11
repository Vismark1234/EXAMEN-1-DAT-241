#include <stdio.h>
#include <math.h>

void calcular_pi_gauss_legendre_recursivo(int n, long double *a, long double *b, long double *t, long double *p, int i, long double *pi) {
    if (i < n) {
        long double a_aux = (*a + *b) / 2.0L;
        long double b_aux = sqrtl(*a * *b);
        long double temp = (*a - a_aux) * (*a - a_aux);
        *t -= *p * temp;
        *p *= 2;

        // Actualizar a y b
        *a = a_aux;
        *b = b_aux;

        // Llamada recursiva
        calcular_pi_gauss_legendre_recursivo(n, a, b, t, p, i + 1, pi);
    } else {
        // Calcular el valor de pi
        *pi = powl(*a + *b, 2) / (4.0L * (*t));
    }
}

int main() {
    int n;
    long double pi;

    // Inicializar variables
    long double a = 1.0L;
    long double b = 1.0L / sqrtl(2.0L);
    long double t = 0.25L;
    long double p = 1.0L;

    printf("Ingrese el numero de iteraciones: ");
    scanf("%d", &n);

	// Llamada recursiva
    calcular_pi_gauss_legendre_recursivo(n, &a, &b, &t, &p, 0, &pi);


    printf("Valor aproximado de pi: %.21Lf\n", pi);

    return 0;
}
