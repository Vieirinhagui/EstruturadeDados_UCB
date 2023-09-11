#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ALUNOS 100

struct Aluno
{
    char nome[100];
    float notas[2];
    float media;
    char situacao[20];
};

int main()
{
    struct Aluno alunos[MAX_ALUNOS];
    int num_alunos = 0;

    FILE *arquivo_entrada = fopen("DadosEntrada.txt", "r");
    if (arquivo_entrada == NULL)
    {
        perror("Erro ao abrir o arquivo de entrada");
        return 1;
    }

    while (num_alunos < MAX_ALUNOS &&
           fscanf(arquivo_entrada, "%[^,],%*[^,],%*[^,],%f,%f\n",
                  alunos[num_alunos].nome,
                  &alunos[num_alunos].notas[0],
                  &alunos[num_alunos].notas[1]) == 3)
    {

        alunos[num_alunos].media = (alunos[num_alunos].notas[0] + alunos[num_alunos].notas[1]) / 2;

        if (alunos[num_alunos].media >= 7.0)
        {
            strcpy(alunos[num_alunos].situacao, "APROVADO");
        }
        else
        {
            strcpy(alunos[num_alunos].situacao, "REPROVADO");
        }

        num_alunos++;
    }

    fclose(arquivo_entrada);

    FILE *arquivo_saida = fopen("SituacaoFinal.csv", "w");
    if (arquivo_saida == NULL)
    {
        perror("Erro ao abrir o arquivo de saída");
        return 1;
    }
    int i;

    for (i = 0; i < num_alunos; i++)
    {
        fprintf(arquivo_saida, "%s, %.2f, %s\n", alunos[i].nome, alunos[i].media, alunos[i].situacao);
    }

    fclose(arquivo_saida);

    printf("Processamento concluido. Os resultados foram salvos em SituacaoFinal.csv\n");

    return 0;
}
