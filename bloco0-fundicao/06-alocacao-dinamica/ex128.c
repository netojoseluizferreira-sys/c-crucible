// 128 — O Espectro da Cópia Profunda (Cópia de Matriz Dinâmica)
// Lê uma matriz L×C de inteiros, aloca uma cópia profunda usando
// memcpy (bloco contíguo) e imprime a matriz copiada. Libera toda
// a memória alocada.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    size_t l, c;

    scanf("%zu %zu", &l, &c);

    // Aloca a matriz original como um único bloco contíguo (L×C)
    int *matriz = (int *)malloc((l * c) * sizeof(int));
    if (matriz == NULL) {
        return 1;
    }

    // Leitura dos elementos usando aritmética de ponteiros
    // matriz[i][j] = *(matriz + i*C + j)
    for (size_t i = 0; i < l; i++) {
        for (size_t j = 0; j < c; j++) {
            scanf("%d", (matriz + (i * c) + j));
        }
    }

    // Aloca a cópia profunda (novo bloco contíguo)
    int *copia = (int *)malloc((l * c) * sizeof(int));
    if (copia == NULL) {
        free(matriz);  // libera o original antes de encerrar
        return 1;
    }

    // Copia todo o conteúdo da matriz original para a cópia
    memcpy(copia, matriz, (l * c) * sizeof(int));

    // Impressão da matriz copiada
    for (size_t i = 0; i < l; i++) {
        printf("| ");
        for (size_t j = 0; j < c; j++) {
            printf("%d ", *(copia + (i * c) + j));
        }
        printf("|\n");
    }

    // Libera e anula os ponteiros (proteção contra double free)
    free(matriz);
    matriz = NULL;

    free(copia);
    copia = NULL;

    return 0;
}