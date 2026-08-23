// 126 — A Fusão dos Exércitos (Concatenação de Arrays Dinâmicos)
// Lê N1 inteiros para um array, N2 inteiros para outro, aloca um
// terceiro array de tamanho N1+N2 e copia os elementos do primeiro
// e depois do segundo. Imprime o array concatenado e libera tudo.
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    size_t n1, n2;

    // Leitura do tamanho do primeiro array
    scanf("%zu", &n1);

    // Aloca o primeiro array dinamicamente
    int *p = (int *)malloc(n1 * sizeof(int));
    if (p == NULL) return 1;

    // Leitura dos elementos do primeiro array
    for (size_t i = 0; i < n1; i++) {
        scanf("%d", p + i);
    }

    // Leitura do tamanho do segundo array
    scanf("%zu", &n2);

    // Aloca o segundo array dinamicamente
    int *q = (int *)malloc(n2 * sizeof(int));
    if (q == NULL) {
        free(p);
        return 1;
    }

    // Leitura dos elementos do segundo array
    for (size_t i = 0; i < n2; i++) {
        scanf("%d", q + i);
    }

    // Aloca o array concatenado com tamanho n1 + n2
    int *total = (int *)malloc((n1 + n2) * sizeof(int));
    if (total == NULL) {
        free(p);
        free(q);
        return 1;
    }

    // Copia os elementos do primeiro array
    for (size_t i = 0; i < n1; i++) {
        *(total + i) = *(p + i);
    }

    // Copia os elementos do segundo array (após os do primeiro)
    for (size_t i = 0; i < n2; i++) {
        *(total + i + n1) = *(q + i);
    }

    // Impressão do array concatenado
    for (size_t i = 0; i < (n1 + n2); i++) {
        printf("%d ", *(total + i));
    }
    printf("\n");

    // Libera toda a memória alocada
    free(p);
    free(q);
    free(total);

    return 0;
}