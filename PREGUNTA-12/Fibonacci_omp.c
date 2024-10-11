//=================================================================================
// COMPILAR: 						gcc Fibonacci_omp.c -o Fibonacci_omp -fopenmp
// CORRER EL PROGRAMA				./Fibonacci_omp
//=================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int n = 10;       // Número de términos de Fibonacci
    int a = -1, b = 1, c;
    int i;

    // Calculo de la serie de Fibonacci en paralelo
    #pragma omp parallel shared(a, b, c) private(i)
    {
        int procesador = omp_get_thread_num(); // Obtener el ID del procesador

        #pragma omp for
        for (i = 0; i < n; i++) {
            #pragma omp critical  // Sección crítica para evitar conflictos de acceso
            {
                c = a + b;
                a = b;
                b = c;

                // Imprimir el hilo y el valor calculado de Fibonacci
                printf("Procesador %d calculando Fibonacci %d\n", procesador, c);
            }
        }
    }

    return 0;
}

//=================================================================================
// COMPILAR: 						gcc Fibonacci_omp.c -o Fibonacci_omp -fopenmp
// CORRER EL PROGRAMA				./Fibonacci_omp
//=================================================================================
