// 125 — O Filtro das Almas (Array Dinâmico com Remoção)
// Lê N inteiros e um valor X. Aloca array dinâmico com os N valores.
// Conta quantos elementos são diferentes de X, aloca um novo array
// com esse tamanho, copia apenas os diferentes de X e imprime.
// Libera ambos os arrays ao final.
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    size_t n;
    int x;

    scanf("%zu", &n);

    // Aloca o array original com n inteiros
    int *p = (int *)malloc(n * sizeof(int));
    if (p == NULL) {
        return 1;
    }

    // Leitura dos n valores (atenção: p+i para percorrer o array)
    for (size_t i = 0; i < n; i++) {
        scanf("%d", p + i);
    }

    // Leitura do valor a ser removido
    scanf("%d", &x);

    // Conta quantos elementos são diferentes de X
    size_t cont = 0;
    for (size_t i = 0; i < n; i++) {
        if (*(p + i) != x) {
            cont++;
        }
    }

    // Aloca um novo array para os elementos diferentes de X
    int *filtrado = (int *)malloc(cont * sizeof(int));
    if (filtrado == NULL && cont > 0) {
        free(p);
        return 1;
    }

    // Copia apenas os elementos diferentes de X
    size_t j = 0;
    for (size_t i = 0; i < n; i++) {
        if (*(p + i) != x) {
            *(filtrado + j) = *(p + i);
            j++;
        }
    }

    // Impressão do array filtrado
    for (size_t i = 0; i < cont; i++) {
        printf("%d ", *(filtrado + i));
    }
    printf("\n");

    // Libera a memória dos dois arrays
    free(p);
    free(filtrado);

    return 0;
}