// 105 — A Sinfonia dos Destruidores (Callbacks com Contexto via void*)
// Lê N inteiros, uma operação ('m' para multiplicar, 'i' para incrementar)
// e um valor de referência. Aplica a transformação escolhida a cada
// elemento do array e imprime o resultado.
//
// Utiliza um array de ponteiros para função (tabela_operacoes) para
// selecionar a operação sem switch/if na lógica de transformação.
//
// Esta versão simplifica o conceito de "contexto" (void*) usando um
// valor fixo passado como argumento para a função de callback.
#include <stdio.h>

int somar(int a, int b);
int multiplicar(int a, int b);

int main(void) {
    // Tabela de ponteiros para função: índice 0 = soma, índice 1 = multiplicação
    int (*tabela_operacoes[])(int, int) = {somar, multiplicar};

    int a, b;
    char op;

    // Leitura do tamanho do array
    scanf("%d", &a);
    int arr[a];

    // Leitura dos elementos do array usando aritmética de ponteiros
    for (int i = 0; i < a; i++) {
        scanf("%d", arr + i);
    }

    // Leitura da operação ('i' para incrementar/somar, 'm' para multiplicar)
    scanf(" %c", &op);

    // Leitura do valor de referência
    scanf("%d", &b);

    // Aplica a operação escolhida a cada elemento do array
    switch (op) {
        case 'i':
            // Incrementa cada elemento pelo valor de referência
            for (int i = 0; i < a; i++) {
                printf("%d ", tabela_operacoes[0](*(arr + i), b));
            }
            break;
        case 'm':
            // Multiplica cada elemento pelo valor de referência
            for (int i = 0; i < a; i++) {
                printf("%d ", tabela_operacoes[1](*(arr + i), b));
            }
            break;
        default:
            break;
    }
    printf("\n");

    return 0;
}

int somar(int a, int b)        { return a + b; }
int multiplicar(int a, int b)  { return a * b; }