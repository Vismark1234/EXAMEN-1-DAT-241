
//=================================================================================
// COMPILAR: 						mpicc -o vectores vectores.c
// CORRER EL PROGRAMA				mpirun -np 3 ./vectores
//=================================================================================
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int rank, size, i;
    const int n = 8;  // Tamaño del vector
    int vectorA[n], vectorB[n], result[n];

    MPI_Init(&argc, &argv);               // Inicializar MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtener el rango del proceso
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtener el número total de procesos

    // Inicialización de los vectores en el proceso maestro (rank 0)
    if (rank == 0) {
        for (i = 0; i < n; i++) {
            vectorA[i] = i;          // Vector A: [0, 1, 2, 3, 4, 5, 6, 7]
            vectorB[i] = 10+i;    // Vector B: [10, 11, 12, 13, 14, 15, 16, 17]
        }
        for (i = 0; i < n; i++) {
            printf("%d ", vectorB[i]);
        }printf("\n");
    }



    // Se difunden los vectores a todos los procesos
    MPI_Bcast(vectorA, n, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(vectorB, n, MPI_INT, 0, MPI_COMM_WORLD);

    // Inicializar el resultado local
    int local_result[n];
    for (i = 0; i < n; i++) {
        local_result[i] = 0;  // Inicializar todo en 0
    }

    // Proceso 1: Suma los elementos impares y modifica el valor
    if (rank == 1) {
        for (i = 1; i < n; i += 2) {  // Índices impares: 1, 3, 5, 7...
            local_result[i] = vectorA[i] + vectorB[i];
        }
    }

    // Proceso 2: Suma los elementos pares y recibe el valor modificado
    if (rank == 2) {
    	//printf("R:\n");
        for (i = 0; i < n; i += 2) {  // Índices pares: 0, 2, 4, 6...
            local_result[i] = vectorA[i] + vectorB[i];
        }
    }

    // Reunir los resultados en el proceso maestro
    MPI_Reduce(local_result, result, n, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Mostrar el resultado en el proceso maestro (rank 0)
    if (rank == 0) {
        printf("Resultado de la suma de vectores:\n");
        for (i = 0; i < n; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
    }

    MPI_Finalize();  // Finalizar MPI
    return 0;
}
//=================================================================================
// COMPILAR: 						mpicc -o vectores vectores.c
// CORRER EL PROGRAMA				mpirun -np 3 ./vectores
//=================================================================================
