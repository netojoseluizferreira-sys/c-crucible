// 123 — A Matriz do Caos (Matriz Dinâmica)
// Lê L linhas e C colunas, aloca dinamicamente uma matriz L×C,
// preenche cada posição [i][j] com (i+1)*(j+1), imprime no formato
// de linhas e colunas e libera toda a memória.
//
// A alocação é feita em dois níveis: um array de ponteiros para as
// linhas e, para cada linha, um array de inteiros.
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    size_t L, C;

    scanf("%zu %zu", &L, &C);

    // Aloca o array de ponteiros para as linhas
    int **matriz = (int **)malloc(L * sizeof(int *));
    if (matriz == NULL) return 1;

    // Aloca cada linha e preenche os elementos
    for (size_t i = 0; i < L; i++) {
        // Aloca a linha i (um array de C inteiros)
        *(matriz + i) = (int *)malloc(C * sizeof(int));
        if (*(matriz + i) == NULL) {
            // Falha: libera as linhas já alocadas e o array de ponteiros
            for (size_t k = 0; k < i; k++) {
                free(*(matriz + k));
            }
            free(matriz);
            return 1;
        }

        // Preenche a linha i: posição [i][j] = (i+1)*(j+1)
        for (size_t j = 0; j < C; j++) {
            *(*(matriz + i) + j) = ((int)i + 1) * ((int)j + 1);
        }
    }

    // Impressão da matriz no formato de linhas e colunas
    for (size_t i = 0; i < L; i++) {
        printf("[ ");
        for (size_t j = 0; j < C; j++) {
            printf("%d ", *(*(matriz + i) + j));
        }
        printf("]\n");
    }

    // Liberação: primeiro cada linha, depois o array de ponteiros
    for (size_t i = 0; i < L; i++) {
        free(*(matriz + i));
    }
    free(matriz);

    return 0;
}