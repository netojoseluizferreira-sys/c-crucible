// 119 — A Armadilha da Dupla Liberação (Evitando Double Free)
// Aloca dinamicamente um array de N inteiros, preenche com valores
// de 1 a N, imprime e libera a memória. Após o free, anula o ponteiro
// para evitar double free acidental.
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    size_t n;

    scanf("%zu", &n);

    // Aloca array para n inteiros
    int *p = (int *)malloc(n * sizeof(int));
    if (p == NULL) {
        return 1;  // falha na alocação
    }

    // Preenche com valores de 1 a n usando aritmética de ponteiros
    for (size_t i = 0; i < n; i++) {
        *(p + i) = (int)i + 1;
    }

    // Imprime os valores
    for (size_t i = 0; i < n; i++) {
        printf("%d ", *(p + i));
    }
    printf("\n");

    // Libera e anula o ponteiro (proteção contra double free)
    free(p);
    p = NULL;

    return 0;
}