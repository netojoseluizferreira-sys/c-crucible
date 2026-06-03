// 077 — Aritmética Abissal (Aritmética de Ponteiros Reversa)
// Lê N inteiros e imprime-os na ordem inversa
// usando apenas aritmética de ponteiros (sem []).
#include <stdio.h>

int main(void) {
    int n;

    scanf("%d", &n);
    int arr[n];

    // Leitura dos elementos usando aritmética de ponteiros
    for (int i = 0; i < n; i++) {
        scanf("%d", arr + i);
    }

    // Impressão na ordem inversa usando apenas aritmética de ponteiros
    for (int i = n; i > 0; i--) {
        printf("%d ", *(arr + i - 1));
    }
    printf("\n");

    return 0;
}