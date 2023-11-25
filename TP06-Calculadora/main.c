// main.c
// #include "calculadora.h"
// #include <stdio.h>
// #include <string.h>

// int main() {
//     char expressao[256];
//     double resultado;

//     printf("Calculadora de Expressão Pós-fixada\n");
//     printf("Digite a expressão em notação pós-fixada (ou 'sair' para encerrar):\n");

//     while (1) {
//         printf("> ");
//         if (fgets(expressao, sizeof(expressao), stdin) == NULL)
//             break;

//         expressao[strcspn(expressao, "\n")] = 0;

//         if (strcmp(expressao, "sair") == 0)
//             break;

//         resultado = avaliarPosfixa(expressao);
//         printf("Resultado: %lf\n", resultado);
//     }

//     printf("Programa encerrado.\n");
//     return 0;
// }


#include "calculadora.h"
#include <stdio.h>
#include <string.h>

int main() {
    char *expressoes[] = {
        "3 4 + 5 *",
        "7 2 * 4 +",
        "8 5 2 4 + * +",
        "6 2 / 3 + 4 *",
        "9 5 2 8 * 4 + * +",
        "2 3 + log 5 /",
        "10 log 3 ^ 2 +",
        "45 60 + 30 cos *",
        "0.5 45 sen 2 ^ +",
        "3 4 + 5 tan *"
    };

    int numeroDeTestes = sizeof(expressoes) / sizeof(expressoes[0]);
    double resultado;

    for (int i = 0; i < numeroDeTestes; i++) {
        char expressaoCopiada[256];
        strncpy(expressaoCopiada, expressoes[i], sizeof(expressaoCopiada));
        expressaoCopiada[sizeof(expressaoCopiada) - 1] = '\0';

        printf("> %s\n", expressaoCopiada);
        resultado = avaliarPosfixa(expressaoCopiada);
        printf("Resultado: %lf\n\n", resultado);
    }

    return 0;
}
