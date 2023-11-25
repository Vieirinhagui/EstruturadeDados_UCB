#ifndef PILHA_H
#define PILHA_H

typedef struct {
    int topo;
    unsigned capacidade;
    double* array;
} Pilha;

Pilha* criarPilha(unsigned capacidade);
int pilhaCheia(Pilha* pilha);
int pilhaVazia(Pilha* pilha);
void empilhar(Pilha* pilha, double item);
double desempilhar(Pilha* pilha);

#endif
