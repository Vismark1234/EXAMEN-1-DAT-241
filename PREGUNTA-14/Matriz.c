//=================================================================================
// COMPILAR: 						mpicc -o Matriz Matriz.c
// CORRER EL PROGRAMA				mpirun -np 2 ./Matriz
//=================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define M 4 // Filas de la matriz A
#define N 4 // Columnas de la matriz A / Filas de la matriz B
#define P 4 // Columnas de la matriz B

void print_matrix(int matrix[M][P]) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char** argv) {
    int procesador, cantidad;
    int A[M][N] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    int B[N][P] = {
        {0, 2, 3, 4},
        {0, 6, 7, 8},
        {0, 10, 11, 12},
        {0, 14, 15, 16}
    };
    int C[M][P] = {0}; // Matriz resultante

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &procesador);
    MPI_Comm_size(MPI_COMM_WORLD, &cantidad);

    // SOLO SE USARAN 2 PROCESADORES
    if (cantidad != 2) {
        if (procesador == 0) {
            printf("Este programa debe ejecutarse con 2 procesos.\n");
        }
        MPI_Finalize();
        return -1;
    }

    // Filas que procesará cada proceso
    int fila_procesos= M / cantidad; // Cada proceso maneja 2 filas

    int aux_A[fila_procesos][N]; // Matriz local A para cada proceso
    int aux_C[fila_procesos][P]; // Resultado local C para cada proceso

    // Distribución de filas de A a los procesos
    MPI_Scatter(A, fila_procesos * N, MPI_INT, aux_A, fila_procesos * N, MPI_INT, 0, MPI_COMM_WORLD);

    // Proceso 0 envía la matriz B completa a Proceso 1
    if (procesador == 0) {
        MPI_Send(B, N * P, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else {
        MPI_Recv(B, N * P, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Multiplicación de matrices
    for (int i = 0; i < fila_procesos; i++) {
        for (int j = 0; j < P; j++) {
            aux_C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                aux_C[i][j] += aux_A[i][k] * B[k][j]; // Multiplicacion
            }
        }
    }

    // REUNE todo en el proceso 0
    MPI_Gather(aux_C, fila_procesos * P, MPI_INT, C, fila_procesos * P, MPI_INT, 0, MPI_COMM_WORLD);

    // Solo el proceso 0 imprime la matriz resultante
    if (procesador == 0) {
        printf("Matriz A:\n");
        print_matrix(A);
        printf("Matriz B:\n");
        print_matrix(B);
        printf("Producto C = A * B:\n");
        print_matrix(C);
    }

    MPI_Finalize();
    return 0;
}

//=================================================================================
// COMPILAR: 						mpicc -o Matriz Matriz.c
// CORRER EL PROGRAMA				mpirun -np 2 ./Matriz
//=================================================================================
