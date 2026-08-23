// 116 — A Cópia das Sombras (memcpy)
// Lê N inteiros para um array de origem, copia-os para um array
// de destino usando memcpy e imprime o array de destino.
// A leitura e a impressão usam aritmética de ponteiros.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int *origem, *destino;
    size_t N;

    scanf("%zu", &N);

    // Aloca os dois arrays dinamicamente
    origem = (int *)malloc(N * sizeof(int));
    if (origem == NULL) return 1;

    destino = (int *)malloc(N * sizeof(int));
    if (destino == NULL) {
        free(origem);
        return 1;
    }

    // Leitura dos elementos no array de origem
    for (size_t i = 0; i < N; i++) {
        scanf("%d", origem + i);
    }

    // Copia N inteiros de origem para destino
    memcpy(destino, origem, N * sizeof(int));

    // Impressão do array de destino
    for (size_t i = 0; i < N; i++) {
        printf("%d ", *(destino + i));
    }
    printf("\n");

    free(origem);
    free(destino);

    return 0;
}