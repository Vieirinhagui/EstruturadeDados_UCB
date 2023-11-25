
#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

Matriz criaMatriz(int nlin, int ncol)
{
    Matriz matriz;
    matriz.nlin = nlin;
    matriz.ncol = ncol;

    matriz.cabeca = (Celula *)malloc(sizeof(Celula));
    matriz.cabeca->linha = -1;
    matriz.cabeca->coluna = -1;
    matriz.cabeca->direita = matriz.cabeca;
    matriz.cabeca->abaixo = matriz.cabeca;
    matriz.cabeca->valor = 0.0;

    Celula *cabecaColuna = (Celula *)malloc(sizeof(Celula));
    cabecaColuna->linha = -1;
    cabecaColuna->coluna = -1;
    cabecaColuna->direita = cabecaColuna;
    cabecaColuna->abaixo = cabecaColuna;
    cabecaColuna->valor = 0.0;

    matriz.cabeca->direita = cabecaColuna;
    cabecaColuna->abaixo = matriz.cabeca;

    return matriz;
}

void insere(Matriz *matriz, int i, int j, float v)
{
    if (i < 0 || i >= matriz->nlin || j < 0 || j >= matriz->ncol)
    {
        printf("Erro: Posição fora dos limites da matriz.\n");
        return;
    }

    // Crie uma nova célula
    Celula *novaCelula = (Celula *)malloc(sizeof(Celula));
    novaCelula->linha = i;
    novaCelula->coluna = j;
    novaCelula->valor = v;

    // Encontre a célula cabeça da linha correspondente
    Celula *celulaCabecaLinha = matriz->cabeca;
    while (celulaCabecaLinha->linha != i)
    {
        celulaCabecaLinha = celulaCabecaLinha->abaixo;
    }

    // Encontre a célula cabeça da coluna correspondente
    Celula *celulaCabecaColuna = matriz->cabeca->direita;
    while (celulaCabecaColuna->coluna != j)
    {
        celulaCabecaColuna = celulaCabecaColuna->direita;
    }

    // Insira a célula na lista da linha
    novaCelula->direita = celulaCabecaLinha->direita;
    celulaCabecaLinha->direita = novaCelula;

    // Insira a célula na lista da coluna
    novaCelula->abaixo = celulaCabecaColuna->abaixo;
    celulaCabecaColuna->abaixo = novaCelula;
}

void removeCelula(Matriz *matriz, int i, int j)
{
    if (i < 0 || i >= matriz->nlin || j < 0 || j >= matriz->ncol)
    {
        printf("Erro: Posição fora dos limites da matriz.\n");
        return;
    }

    Celula *cabecaLinha = matriz->cabeca;
    while (cabecaLinha->linha != i)
    {
        cabecaLinha = cabecaLinha->abaixo;
    }

    Celula *celulaAnterior = cabecaLinha;
    Celula *atual = cabecaLinha->direita;
    while (atual != matriz->cabeca && atual->coluna != j)
    {
        celulaAnterior = atual;
        atual = atual->direita;
    }

    if (atual != matriz->cabeca && atual->coluna == j)
    {
        celulaAnterior->direita = atual->direita;

        Celula *cabecaColuna = matriz->cabeca->direita;
        while (cabecaColuna->coluna != j)
        {
            cabecaColuna = cabecaColuna->direita;
        }

        Celula *colunaAnterior = cabecaColuna;
        atual = cabecaColuna->abaixo;
        while (atual != matriz->cabeca && atual->linha != i)
        {
            colunaAnterior = atual;
            atual = atual->abaixo;
        }

        colunaAnterior->abaixo = atual->abaixo;

        free(atual);
    }
}

// Função para imprimir a matriz esparsa
void imprimeMatriz(Matriz A)
{
    for (int i = 0; i < A.nlin; i++)
    {
        Celula *atual = A.cabeca->abaixo;
        for (int j = 0; j < A.ncol; j++)
        {
            if (atual != A.cabeca && atual->linha == i && atual->coluna == j)
            {
                printf("%.2f\t", atual->valor);
                atual = atual->abaixo;
            }
            else
            {
                printf("0.00\t");
            }
        }
        printf("\n");
    }
}

// Função para ler a matriz de um arquivo
Matriz leMatriz(FILE *arquivo)
{
    int nlin, ncol;
    fscanf(arquivo, "%d, %d", &nlin, &ncol);
    Matriz matriz = criaMatriz(nlin, ncol);

    while (!feof(arquivo))
    {
        int i, j;
        float valor;
        fscanf(arquivo, "%d, %d, %f", &i, &j, &valor);
        insere(&matriz, i, j, valor);
    }

    return matriz;
}

// Função para somar duas matrizes esparsas
Matriz somaMatrizes(Matriz A, Matriz B)
{
    if (A.nlin != B.nlin || A.ncol != B.ncol)
    {
        printf("Erro: As matrizes têm dimensões diferentes.\n");
        return criaMatriz(0, 0); // Matriz vazia para indicar erro
    }

    Matriz C = criaMatriz(A.nlin, A.ncol);

    for (int i = 0; i < A.nlin; i++)
    {
        for (int j = 0; j < A.ncol; j++)
        {
            float valorA = 0.0, valorB = 0.0;

            Celula *atualA = A.cabeca->direita;
            while (atualA != A.cabeca && atualA->coluna <= j)
            {
                if (atualA->linha == i)
                {
                    valorA = atualA->valor;
                    break;
                }
                atualA = atualA->direita;
            }

            Celula *atualB = B.cabeca->direita;
            while (atualB != B.cabeca && atualB->coluna <= j)
            {
                if (atualB->linha == i)
                {
                    valorB = atualB->valor;
                    break;
                }
                atualB = atualB->direita;
            }

            insere(&C, i, j, valorA + valorB);
        }
    }

    return C;
}
// Função para multiplicar duas matrizes esparsas
Matriz multiplicaMatrizes(Matriz A, Matriz B)
{
    if (A.ncol != B.nlin)
    {
        printf("Erro: Não é possível multiplicar as matrizes com essas dimensões.\n");
        return criaMatriz(0, 0); // Matriz vazia para indicar erro
    }

    Matriz C = criaMatriz(A.nlin, B.ncol);

    for (int i = 0; i < A.nlin; i++)
    {
        for (int j = 0; j < B.ncol; j++)
        {
            float valor = 0.0;
            for (int k = 0; k < A.ncol; k++)
            {
                float valorA = 0.0, valorB = 0.0;

                Celula *atualA = A.cabeca->direita;
                while (atualA != A.cabeca && atualA->coluna <= k)
                {
                    if (atualA->linha == i)
                    {
                        valorA = atualA->valor;
                        break;
                    }
                    atualA = atualA->direita;
                }

                Celula *atualB = B.cabeca->abaixo;
                while (atualB != B.cabeca && atualB->linha <= k)
                {
                    if (atualB->coluna == j)
                    {
                        valorB = atualB->valor;
                        break;
                    }
                    atualB = atualB->abaixo;
                }

                valor += valorA * valorB;
            }

            insere(&C, i, j, valor);
        }
    }

    return C;
}
// Função para liberar a memória alocada para a matriz
void liberaMatriz(Matriz matriz)
{
    Celula *atual = matriz.cabeca;
    Celula *linhaAnterior = NULL;

    while (atual != NULL)
    {
        Celula *colunaAnterior = NULL;

        while (atual != NULL)
        {
            Celula *temp = atual;
            atual = atual->direita;
            free(temp);
        }

        if (linhaAnterior != NULL)
        {
            free(linhaAnterior);
        }
        linhaAnterior = atual;
    }
}
