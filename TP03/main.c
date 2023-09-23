#include <stdio.h>

typedef struct {
    float X;
    float Y;
} Ponto;

float CalculaArea(Ponto A, Ponto B, Ponto C) {
    // Calcula a área do triângulo usando a fórmula do determinante
    return 0.5 * ((A.X * B.Y + B.X * C.Y + C.X * A.Y) - (A.Y * B.X + B.Y * C.X + C.Y * A.X));
}

int main() {
    FILE *arquivo;
    arquivo = fopen("vertices.txt", "r"); // Abre o arquivo de entrada (substitua "vertices.txt" pelo nome do seu arquivo)

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

    int numVertices;
    fscanf(arquivo, "%d", &numVertices);

    if (numVertices < 3) {
        printf("O polígono deve ter pelo menos 3 vértices.\n");
        fclose(arquivo);
        return 1;
    }

    Ponto vertices[numVertices];
    
    // Lê as coordenadas dos vértices do arquivo
    for (int i = 0; i < numVertices; i++) {
        fscanf(arquivo, "%f %f", &vertices[i].X, &vertices[i].Y);
    }

    fclose(arquivo);

    // Calcula a área do polígono dividindo-o em triângulos
    float areaTotal = 0.0;
    for (int i = 1; i < numVertices - 1; i++) {
        areaTotal += CalculaArea(vertices[0], vertices[i], vertices[i + 1]);
    }

    // Certifica-se de que a área é sempre positiva
    if (areaTotal < 0) {
        areaTotal = -areaTotal;
    }

    printf("A área do polígono é %.2f\n", areaTotal);

    return 0;
}
