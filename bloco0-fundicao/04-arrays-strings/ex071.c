// 071 — Multiplicação de Matrizes (2×3 por 3×2)
// Lê uma matriz 2×3 e uma matriz 3×2, calcula a multiplicação e imprime
// a matriz resultante 2×2. A multiplicação segue a regra:
// C[i][j] = soma de A[i][k] * B[k][j] para k de 0 a 2.
#include <stdio.h>

int main(void) {
    int matriz[2][3], matriz2[3][2], resultado[2][2] = {0};

    // Leitura da primeira matriz (2×3)
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            scanf("%d", &matriz[i][j]);
        }
    }

    // Leitura da segunda matriz (3×2)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            scanf("%d", &matriz2[i][j]);
        }
    }

    // Multiplicação: (2×3) × (3×2) = (2×2)
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 3; k++) {
                resultado[i][j] += matriz[i][k] * matriz2[k][j];
            }
        }
    }

    // Impressão da matriz resultante (2×2)
    for (int i = 0; i < 2; i++) {
        printf("[ ");
        for (int j = 0; j < 2; j++) {
            printf("%d ", resultado[i][j]);
        }
        printf("]\n");
    }

    return 0;
}