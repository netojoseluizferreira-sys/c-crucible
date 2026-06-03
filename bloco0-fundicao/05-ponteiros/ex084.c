// 084 — A Forja de Funções (Ponteiros para Funções I)
// Lê dois inteiros e um caractere (+, -, *, /). Executa a operação
// correspondente usando um ponteiro para função.
//
// O ponteiro 'operacao' é atribuído com o endereço da função escolhida
// e depois chamado diretamente, demonstrando que funções podem ser
// referenciadas e invocadas indiretamente através de ponteiros.
#include <stdio.h>

int somar(int n1, int n2);
int subtrair(int n1, int n2);
int multiplicacao(int n1, int n2);
int divisao(int n1, int n2);

int main(void) {
    int n1, n2;
    char op;

    scanf("%d %c %d", &n1, &op, &n2);

    // Ponteiro para função: armazena o endereço da operação escolhida
    int (*operacao)(int, int) = NULL;

    switch (op) {
        case '+':
            operacao = somar;         // aponta para a função somar
            break;
        case '-':
            operacao = subtrair;      // aponta para a função subtrair
            break;
        case '*':
            operacao = multiplicacao; // aponta para a função multiplicacao
            break;
        case '/':
            if (n2 == 0) {
                printf("Divisao por zero\n");
                return 1;
            }
            operacao = divisao;       // aponta para a função divisao
            break;
        default:
            printf("Operacao invalida\n");
            return 1;
    }

    // Chama a função através do ponteiro
    printf("%d\n", operacao(n1, n2));

    return 0;
}

// Funções de operação básicas
int somar(int n1, int n2)        { return n1 + n2; }
int subtrair(int n1, int n2)     { return n1 - n2; }
int multiplicacao(int n1, int n2){ return n1 * n2; }
int divisao(int n1, int n2)      { return n1 / n2; }