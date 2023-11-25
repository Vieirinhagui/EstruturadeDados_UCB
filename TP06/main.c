#include <stdio.h>
#include "matriz.h"

int main() {
    printf("ta aqui");
    FILE *arquivo = fopen("./input.txt", "r");
    Matriz A, B, C;
    A = leMatriz(arquivo);
    fclose(arquivo);

    printf("Matriz A:\n");
    imprimeMatriz(A);

    B = leMatriz(arquivo);
    printf("Matriz B:\n");
    imprimeMatriz(B);

    C = somaMatrizes(A, B);
    printf("Soma de A e B:\n");
    imprimeMatriz(C);
    liberaMatriz(C);

    C = multiplicaMatrizes(A, B);
    printf("Multiplicação de A e B:\n");
    imprimeMatriz(C);
    liberaMatriz(C);

    liberaMatriz(A);
    liberaMatriz(B);

    return 0;
}
