// 058 — O Espelhador (Array Unidimensional + Aritmética de Ponteiros)
// Lê N inteiros e imprime-os na ordem inversa usando apenas aritmética
// de ponteiros (sem usar [] para acessar os elementos na impressão).
#include <stdio.h>

int main(void) {
    int tam;

    scanf("%d", &tam);
    int numeros[tam];

    // Ponteiro para o início do array
    int *p = numeros;

    // Leitura dos N elementos
    for (int i = 0; i < tam; i++) {
        scanf("%d", p + i);
    }

    // Percorre de trás para frente usando aritmética de ponteiros
    for (int i = tam - 1; i >= 0; i--) {
        printf("%d ", *(p + i));
    }
    printf("\n");

    return 0;
}