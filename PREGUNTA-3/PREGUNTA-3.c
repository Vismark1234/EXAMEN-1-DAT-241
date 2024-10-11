#include <stdio.h>

// Funciones
void suma(float *a, float *b, float *resultado) {
    *resultado = *a + *b;
}

void resta(float *a, float *b, float *resultado) {
    *resultado = *a - *b;
}

void multiplicacion(float *a, float *b, float *resultado) {
    *resultado = *a * *b;
}

void division(float *a, float *b, float *resultado) {
    if (*b != 0) {
        *resultado = *a / *b;
    } else {
        printf("ERROR: no se puede dividir por 0\n");
        *resultado = 0.0; // Se establece a 0.0 en caso de error
    }
}

int main() {
    float num1, num2, resultado;
    int opcion;
    char continuar;

    do {
        printf("Ingrese el primer numero: ");
        scanf("%f", &num1);

        printf("Ingrese el segundo numero: ");
        scanf("%f", &num2);

        // Menú
        printf("Seleccione la operacion:\n");
        printf("1. SUMA\n");
        printf("2. RESTA\n");
        printf("3. MULTIPLICACION\n");
        printf("4. DIVISION\n");
        scanf("%d", &opcion);

        // seleccionar
        switch(opcion) {
            case 1:
                suma(&num1, &num2, &resultado);
                printf("El resultado de la SUMA es: %.2f\n", resultado);
                break;
            case 2:
                resta(&num1, &num2, &resultado);
                printf("El resultado de la RESTA es: %.2f\n", resultado);
                break;
            case 3:
                multiplicacion(&num1, &num2, &resultado);
                printf("El resultado de la MULTIPLICACION es: %.2f\n", resultado);
                break;
            case 4:
                division(&num1, &num2, &resultado);
                if (num2 != 0) {
                    printf("El resultado de la DIVISION es: %.2f\n", resultado);
                }
                break;
            default:
                printf("OPCION NO VALIDA.\n");
        }


        printf("¿Desea realizar otra operacion? (s/n): "); //HACER MAS OPERACIONES
        scanf(" %c", &continuar);

    } while (continuar == 's' || continuar == 'S');

    printf("Gracias por usar el programa.\n");
    return 0;
}
