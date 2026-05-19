// 050 — Função Variádica (sem stdarg.h): Soma de Inteiros via Array
// Recebe a quantidade de números e um array de inteiros.
// Calcula a soma de todos os elementos e armazena no ponteiro *sum.
#include <stdio.h>

void soma_todos(int qnt, int *nums, int *sum);

int main(void) {
    int qnt;

    scanf("%d", &qnt);
    int numeros[qnt];

    for (int i = 0; i < qnt; i++) {
        scanf("%d", &numeros[i]);
    }

    int soma = 0;
    soma_todos(qnt, numeros, &soma);

    printf("%d\n", soma);

    return 0;
}

void soma_todos(int qnt, int *nums, int *sum) {
    *sum = 0;                    // inicializa o acumulador
    for (int i = 0; i < qnt; i++) {
        *sum += nums[i];
    }
}