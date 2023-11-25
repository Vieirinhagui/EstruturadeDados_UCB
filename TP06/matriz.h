// matriz.h

#ifndef MATRIZ_H
#define MATRIZ_H

// Estrutura de uma célula na matriz esparsa
typedef struct Celula {
    struct Celula *direita, *abaixo;
    int linha, coluna;
    float valor;
} Celula;

// Estrutura da matriz esparsa
typedef struct {
    Celula *cabeca;
    int nlin, ncol;
} Matriz;

// Protótipos das funções
Matriz criaMatriz(int nlin, int ncol);
void insere(Matriz *matriz, int i, int j, float v);
void removeCelula(Matriz *matriz, int i, int j);
void imprimeMatriz(Matriz A);
Matriz leMatriz(FILE *arquivo);
Matriz somaMatrizes(Matriz A, Matriz B);
Matriz multiplicaMatrizes(Matriz A, Matriz B);
void liberaMatriz(Matriz matriz);

#endif
