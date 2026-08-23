// 117 — O Movimento das Almas (memmove)
// Lê N inteiros para um array dinâmico, desloca todos os elementos
// uma posição à direita usando memmove (seguro para sobreposição)
// e insere 0 na primeira posição. A leitura e a impressão usam
// aritmética de ponteiros.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int *src;
    size_t N;

    scanf("%zu", &N);

    // Aloca o array dinamicamente
    src = (int *)malloc(N * sizeof(int));
    if (src == NULL) return 1;

    // Leitura dos elementos usando aritmética de ponteiros
    for (size_t i = 0; i < N; i++) {
        scanf("%d", src + i);
    }

    // Desloca N-1 elementos uma posição à direita.
    // memmove é usado porque as regiões de origem e destino se sobrepõem.
    memmove(src + 1, src, (N - 1) * sizeof(int));

    // Insere 0 na primeira posição
    *src = 0;

    // Impressão do array resultante
    for (size_t i = 0; i < N; i++) {
        printf("%d ", *(src + i));
    }
    printf("\n");

    free(src);

    return 0;
}