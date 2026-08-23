// 127 — A Purificação pelo Fogo (calloc e Inicialização)
// Aloca um array de N inteiros com calloc (todos zerados), soma
// i*2 a cada posição i e imprime o resultado. Libera a memória.
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    size_t n;

    scanf("%zu", &n);

    // calloc aloca e inicializa todos os bytes com zero
    int *p = (int *)calloc(n, sizeof(int));
    if (p == NULL) {
        return 1;  // falha na alocação
    }

    // Soma i*2 a cada posição (calloc já deixou tudo zerado)
    for (size_t i = 0; i < n; i++) {
        *(p + i) += (int)i * 2;
    }

    // Impressão dos valores usando aritmética de ponteiros
    for (size_t i = 0; i < n; i++) {
        printf("%d ", *(p + i));
    }
    printf("\n");

    // Libera a memória alocada
    free(p);

    return 0;
}