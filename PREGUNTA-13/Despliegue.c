//=================================================================================
// COMPILAR: 						mpicc -o Despliegue Despliegue.c
// CORRER EL PROGRAMA				mpirun -np 3 ./Despliegue
//=================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#define TAMANO_VECTOR 10    // puede cambiar
#define LONGITUD_CADENA 20	//puede cambiar

void imprimir_posiciones_pares(char cadenas[][LONGITUD_CADENA], int cuenta) {
    printf("Procesador 1 - Posiciones pares:\n");
    for (int i = 0; i < cuenta; i += 2) {
        printf("%s\n", cadenas[i]);
    }
}

void imprimir_posiciones_impares(char cadenas[][LONGITUD_CADENA], int cuenta) {
    printf("Procesador 2 - Posiciones impares:\n");
    for (int i = 1; i < cuenta; i += 2) {
        printf("%s\n", cadenas[i]);
    }
}

int main(int argc, char** argv) {
    int procesador, cantidad;
    char cadenas[TAMANO_VECTOR][LONGITUD_CADENA] = {
        "cero", "uno", "dos", "tres", "cuatro",
        "cinco", "seis", "siete", "ocho", "nueve"
    };

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &procesador);
    MPI_Comm_size(MPI_COMM_WORLD, &cantidad);

    // Asegúrate de que el número de procesos es 3
    if (cantidad != 3) {
        if (procesador == 0) {
            printf("Este programa debe ejecutarse con 3 procesos.\n");
        }
        MPI_Finalize();
        return -1;
    }

    // El proceso 0 distribuye el vector
    if (procesador == 0) {
        for (int i = 1; i < cantidad; i++) {
            MPI_Send(cadenas, TAMANO_VECTOR * LONGITUD_CADENA, MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
    } else {
        // Los procesos 1 y 2 reciben el vector
        MPI_Recv(cadenas, TAMANO_VECTOR * LONGITUD_CADENA, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Procesador 1 despliega posiciones pares
        if (procesador == 1) {
            imprimir_posiciones_pares(cadenas, TAMANO_VECTOR);
        }
        // Procesador 2 despliega posiciones impares
        else if (procesador == 2) {
            imprimir_posiciones_impares(cadenas, TAMANO_VECTOR);
        }
    }

    MPI_Finalize();
    return 0;
}
//=================================================================================
// COMPILAR: 						mpicc -o Despliegue Despliegue.c
// CORRER EL PROGRAMA				mpirun -np 3 ./Despliegue
//=================================================================================

