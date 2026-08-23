// 120 — O Punhal Inofensivo (Anulando Ponteiros Após free)
// Aloca dinamicamente um inteiro, atribui 42, imprime, libera a memória
// e anula o ponteiro. Verifica se a anulação foi bem-sucedida.
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // Aloca espaço para um inteiro
    int *p = (int *)malloc(sizeof(int));
    if (p == NULL) {
        return 1;  // falha na alocação
    }

    // Atribui valor e imprime antes de liberar
    *p = 42;
    printf("%d\n", *p);

    // Libera a memória e anula o ponteiro
    free(p);
    p = NULL;

    // Verifica se a anulação foi bem-sucedida
    if (p == NULL) {
        printf("Ponteiro anulado com sucesso.\n");
    } else {
        printf("Erro: ponteiro nao anulado.\n");
    }

    return 0;
}