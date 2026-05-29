// 060 — Transposição de Matriz (Array Multidimensional 2×3)
// Lê uma matriz 2×3 e imprime sua transposta (3×2).
#include <stdio.h>

int main(void) {
    int matriz[2][3];

    // Leitura da matriz 2×3 com mensagens amigáveis
    printf("Digite os elementos da matriz 2x3:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("Posicao [%d][%d]: ", i + 1, j + 1);
            scanf("%d", &matriz[i][j]);
        }
    }

    // Exibe a matriz transposta (3×2)
    printf("\nMatriz transposta (3x2):\n");
    for (int i = 0; i < 3; i++) {
        printf("[ ");
        for (int j = 0; j < 2; j++) {
            printf("%d ", matriz[j][i]);  // troca índices para transpor
        }
        printf("]\n");
    }

    return 0;
}