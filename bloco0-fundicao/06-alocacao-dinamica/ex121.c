// 121 — O Guardião do Vazio (Verificação de malloc)
// Tenta alocar um bloco de memória extremamente grande (10 bilhões de int).
// Verifica se o retorno é NULL. Se for, imprime "Falha na alocacao."
// e encerra com return 1. Caso contrário, imprime "Alocacao bem-sucedida.",
// libera a memória e encerra normalmente.
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // Tenta alocar 10 bilhões de inteiros (aproximadamente 40 GB)
    // O cast (size_t) garante que 10e9 seja tratado como tamanho
    int *p = (int *)malloc((size_t)10e9 * sizeof(int));

    // Verificação obrigatória após malloc
    if (p == NULL) {
        printf("Falha na alocacao.\n");
        return 1;
    }

    // Se chegou aqui, a alocação foi bem-sucedida (improvável)
    printf("Alocacao bem-sucedida.\n");

    // Libera a memória alocada
    free(p);

    return 0;
}