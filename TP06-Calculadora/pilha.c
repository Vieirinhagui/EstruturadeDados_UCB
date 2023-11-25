#include "pilha.h"
#include <stdlib.h>

Pilha* criarPilha(unsigned capacidade) {
    Pilha* pilha = (Pilha*) malloc(sizeof(Pilha));
    pilha->capacidade = capacidade;
    pilha->topo = -1;
    pilha->array = (double*) malloc(pilha->capacidade * sizeof(double));
    return pilha;
}

int pilhaCheia(Pilha* pilha) {
    return pilha->topo == pilha->capacidade - 1;
}

int pilhaVazia(Pilha* pilha) {
    return pilha->topo == -1;
}

void empilhar(Pilha* pilha, double item) {
    if (pilhaCheia(pilha))
        return;
    pilha->array[++pilha->topo] = item;
}

double desempilhar(Pilha* pilha) {
    if (pilhaVazia(pilha))
        return 0;
    return pilha->array[pilha->topo--];
}
