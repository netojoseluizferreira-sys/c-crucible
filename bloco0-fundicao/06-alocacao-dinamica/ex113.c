// 113 — O Túmulo Abençoado (calloc)
// Aloca dinamicamente um array de N inteiros usando calloc,
// que inicializa todos os bytes com zero. Imprime os elementos
// (todos zeros) e libera a memória.
//
// calloc(n, size) aloca um array de n elementos de tamanho size
// e zera toda a memória, diferentemente de malloc.
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // Aloca espaço para ler o tamanho N
    int *p = (int *)malloc(sizeof(int));

    if (p == NULL) {
        return 1;  // falha na alocação
    }

    scanf("%d", p);

    // calloc aloca e inicializa tudo com zero
    int *arr = (int *)calloc((size_t)*p, sizeof(int));

    if (arr == NULL) {
        free(p);   // libera o inteiro alocado antes de sair
        return 1;  // falha na alocação
    }

    // Impressão dos elementos (todos devem ser zero)
    for (int i = 0; i < *p; i++) {
        printf("%d ", *(arr + i));
    }
    printf("\n");

    // Libera toda a memória
    free(p);
    free(arr);

    return 0;
}