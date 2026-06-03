// 097 — O Contrato com o Demônio (Callbacks Simples)
// Lê N inteiros e um caractere ('d' para dobro, 't' para triplo).
// Aplica a transformação escolhida a cada elemento do array usando
// uma função de callback e imprime o array resultante.
//
// A função operacao() recebe um ponteiro para inteiro e um ponteiro
// para função, demonstrando o conceito de callback: uma função que
// recebe outra função como argumento e a executa.
#include <stdio.h>

int dobro(int a);
int triplo(int a);
int operacao(int *arr, int (*func)(int));

int main(void) {
    int tamanho;
    char op;

    scanf("%d", &tamanho);

    int lista[tamanho];

    // Leitura dos elementos usando aritmética de ponteiros
    for (int i = 0; i < tamanho; i++) {
        scanf("%d", lista + i);
    }

    // Espaço antes de %c para ignorar o \n do buffer
    scanf(" %c", &op);

    // Ponteiro para a função escolhida
    int (*func)(int) = NULL;

    if (op == 'd') {
        func = dobro;
    } else if (op == 't') {
        func = triplo;
    } else {
        printf("Operacao invalida\n");
        return 1;
    }

    // Aplica a callback a cada elemento do array
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", operacao(lista + i, func));
    }
    printf("\n");

    return 0;
}

int dobro(int a)  { return a * 2; }
int triplo(int a) { return a * 3; }

// Aplica a função recebida via callback ao valor apontado por arr
int operacao(int *arr, int (*func)(int)) {
    return func(*arr);  // chama a função passada como argumento
}