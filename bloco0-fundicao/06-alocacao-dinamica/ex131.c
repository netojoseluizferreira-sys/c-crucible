// 131 — O Labirinto de Fugas (Gerenciamento de Memória sem Vazamentos)
// Lê N e M inteiros, concatena em um terceiro array dinâmico,
// imprime o resultado e libera toda a memória sem vazamentos.
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    size_t n, m;

    // Lê o tamanho do primeiro array
    scanf("%zu", &n);

    // Aloca o primeiro array dinamicamente
    int *p = (int *)malloc(n * sizeof(int));
    if (p == NULL) return 1;

    // Lê os elementos do primeiro array
    for (size_t i = 0; i < n; i++) {
        scanf("%d", p + i);
    }

    // Lê o tamanho do segundo array
    scanf("%zu", &m);

    // Aloca o segundo array dinamicamente
    int *q = (int *)malloc(m * sizeof(int));
    if (q == NULL) {
        free(p);  // Libera o primeiro array antes de encerrar
        return 1;
    }

    // Lê os elementos do segundo array
    for (size_t i = 0; i < m; i++) {
        scanf("%d", q + i);
    }

    // Aloca o array concatenado (n + m elementos)
    int *total = (int *)malloc((n + m) * sizeof(int));
    if (total == NULL) {
        free(p);
        free(q);
        return 1;
    }

    // Copia os elementos do primeiro array para o array concatenado
    for (size_t i = 0; i < n; i++) {
        *(total + i) = *(p + i);
    }

    // Copia os elementos do segundo array após os do primeiro
    for (size_t i = 0; i < m; i++) {
        *(total + i + n) = *(q + i);
    }

    // Imprime o array concatenado
    for (size_t i = 0; i < (n + m); i++) {
        printf("%d ", *(total + i));
    }
    printf("\n");

    // Libera toda a memória alocada e anula os ponteiros
    free(p);
    p = NULL;

    free(q);
    q = NULL;

    free(total);
    total = NULL;

    return 0;
}