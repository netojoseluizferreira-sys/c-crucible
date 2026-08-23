// 129 — A Invocação Seletiva (realloc com Condição)
// Lê N inteiros e armazena apenas os valores positivos em um array
// dinâmico. O array cresce com realloc a cada valor positivo.
// Imprime os valores armazenados e libera a memória.
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *p = NULL;
    int control;
    size_t n, tam = 0;

    scanf("%zu", &n);

    for (size_t i = 0; i < n; i++) {
        scanf("%d", &control);

        // Só armazena valores positivos
        if (control > 0) {
            // Expande o array em uma posição
            int *temp = (int *)realloc(p, (tam + 1) * sizeof(int));
            if (temp == NULL) {
                free(p);  // se falhar, libera o array anterior
                p = NULL;
                return 1;
            }
            p = temp;

            // Armazena o valor positivo
            *(p + tam) = control;
            tam++;
        }
    }

    // Impressão dos valores armazenados
    for (size_t i = 0; i < tam; i++) {
        printf("%d ", *(p + i));
    }
    printf("\n");

    // Libera e anula o ponteiro
    free(p);
    p = NULL;

    return 0;
}