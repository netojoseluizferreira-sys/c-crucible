// 056 — Soma dos Elementos (Array Unidimensional)
// Lê um inteiro N e depois N inteiros. Calcula e imprime a soma de todos.
#include <stdio.h>

int main(void) {
    int qnt;

    scanf("%d", &qnt);
    int numeros[qnt];

    // Leitura dos N elementos
    for (int i = 0; i < qnt; i++) {
        scanf("%d", &numeros[i]);
    }

    // Cálculo da soma
    int soma = 0;
    for (int i = 0; i < qnt; i++) {
        soma += numeros[i];
    }

    printf("%d\n", soma);

    return 0;
}