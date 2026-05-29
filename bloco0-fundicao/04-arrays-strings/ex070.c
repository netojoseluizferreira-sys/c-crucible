// 070 — Diagonal Principal (Array Multidimensional)
// Lê uma matriz 3×3 e imprime apenas os elementos da diagonal principal
#include <stdio.h>

int main(void) {
    int matriz[3][3];

    // Leitura da matriz 3×3
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            scanf("%d", &matriz[i][j]);
        }
    }

    // Impressão da diagonal principal
    for (int i = 0; i < 3; i++) {
            printf("%d ", matriz[i][i]);
    }
    printf("\n");

    return 0;
}