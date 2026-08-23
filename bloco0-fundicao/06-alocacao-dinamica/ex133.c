// 133 — O Acumulador de Almas (Array Dinâmico com Expansão)
// Lê inteiros até -1, expandindo o array dinamicamente com realloc
// a cada novo valor. Imprime os valores armazenados e libera a memória.
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    size_t i = 0;
    int *p = NULL;
    int control;

    while (1) {
        scanf("%d", &control);

        if (control == -1) {
            break;
        }

        // Expande o array em uma posição usando realloc
        // Usa ponteiro temporário para tratamento seguro de falha
        int *temp = (int *)realloc(p, (i + 1) * sizeof(int));
        if (temp == NULL) {
            free(p);   // se falhar, libera o array anterior
            p = NULL;
            return 1;
        }
        p = temp;

        // Armazena o valor na nova posição
        *(p + i) = control;
        i++;
    }

    // Imprime os valores armazenados
    for (size_t j = 0; j < i; j++) {
        printf("%d ", *(p + j));
    }
    printf("\n");

    // Libera a memória e anula o ponteiro
    free(p);
    p = NULL;

    return 0;
}