// 075 — Cópia de Array com Ponteiros (Array + Aritmética de Ponteiros)
// Lê N inteiros para um array e copia-os para um segundo array
// usando apenas aritmética de ponteiros (sem []).
// Otimizado: leitura e cópia em um único loop.
#include <stdio.h>

int main(void) {
    int n;

    scanf("%d", &n);

    int arr[n], arr2[n];

    // Leitura e cópia em um único loop usando aritmética de ponteiros
    for (int i = 0; i < n; i++) {
        scanf("%d", arr + i);
        *(arr2 + i) = *(arr + i);
    }

    // Impressão do array copiado
    for (int i = 0; i < n; i++) {
        printf("%d ", *(arr2 + i));
    }
    printf("\n");

    return 0;
}