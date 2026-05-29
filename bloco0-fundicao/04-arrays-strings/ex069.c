// 069 — Soma de Matrizes (Array Multidimensional)
// Lê duas matrizes 2×2 de inteiros, calcula a soma e imprime a matriz resultante.
// A leitura é feita elemento por elemento, e a soma é realizada durante a impressão.
#include <stdio.h>

int main(void) {
    int matriz1[2][2], matriz2[2][2];

    // Leitura da primeira matriz 2×2
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            scanf("%d", &matriz1[i][j]);
        }
    }

    // Leitura da segunda matriz 2×2
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            scanf("%d", &matriz2[i][j]);
        }
    }

    // Impressão da matriz soma (2×2)
    for (int i = 0; i < 2; i++) {
        printf("[ ");
        for (int j = 0; j < 2; j++) {
            printf("%d ", matriz1[i][j] + matriz2[i][j]);
        }
        printf("]\n");
    }

    return 0;
}