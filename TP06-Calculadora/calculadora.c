#include <stdlib.h>
#include "calculadora.h"
#include "pilha.h"
#include <string.h>
#include <ctype.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double avaliarPosfixa(char *expressao)
{
    Pilha *pilha = criarPilha(strlen(expressao));
    char *token = strtok(expressao, " ");

    while (token != NULL)
    {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1])))
        {
            empilhar(pilha, atof(token));
        }
        else
        {
            if (token[0] == 'l' || token[0] == 's' || token[0] == 'c' || token[0] == 't')
            {
                double val = desempilhar(pilha);
                switch (token[0])
                {
                case 'l':
                    empilhar(pilha, log10(val));
                    break;
                case 's':
                    empilhar(pilha, sin(val));
                    break;
                case 'c':
                    empilhar(pilha, cos(val));
                    break;
                case 't':
                    empilhar(pilha, tan(val));
                    break;
                }
            }
            else
            {
                double val1 = desempilhar(pilha);
                double val2 = desempilhar(pilha);
                switch (token[0])
                {
                case '+':
                    empilhar(pilha, val2 + val1);
                    break;
                case '-':
                    empilhar(pilha, val2 - val1);
                    break;
                case '*':
                    empilhar(pilha, val2 * val1);
                    break;
                case '/':
                    empilhar(pilha, val2 / val1);
                    break;
                case '^':
                    empilhar(pilha, pow(val2, val1));
                    break;
                }
            }
        }
        token = strtok(NULL, " ");
    }
    return desempilhar(pilha);
}
