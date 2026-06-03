// 106 — A Ira do Cartógrafo (Ponteiros para Matriz 4×4)
// Lê uma matriz 4×4 de inteiros, calcula a soma da diagonal principal
// e a soma da diagonal secundária usando exclusivamente aritmética de
// ponteiros (sem []).
//
// A matriz é tratada como um array unidimensional de 16 elementos.
// Diagonal principal: i == j → índice (i * 4) + j
// Diagonal secundária: i + j == 3 → índice (i * 4) + j
#include <stdio.h>

int main(void) {
    int matriz[16];
    int somadp = 0;  // soma da diagonal principal
    int somads = 0;  // soma da diagonal secundária

    // Leitura e cálculo das diagonais em um único loop
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            // Leitura via aritmética de ponteiros (sem [])
            scanf("%d", matriz + (i * 4) + j);

            // Diagonal principal: i == j
            if (i == j) {
                somadp += *(matriz + (i * 4) + j);
            }

            // Diagonal secundária: i + j == 3 (para matriz 4×4)
            if (i + j == 3) {
                somads += *(matriz + (i * 4) + j);
            }
        }
    }

    printf("%d\n%d\n", somadp, somads);

    return 0;
}