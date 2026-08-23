// 111 — O Primeiro Sussurro (malloc Básico)
// Aloca dinamicamente memória para um único inteiro, armazena um valor
// lido da entrada, imprime o valor e libera a memória.
// Primeiro contato com alocação dinâmica: cada malloc deve ter seu free.
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // Aloca espaço para exatamente um inteiro no heap
    int *p = (int *)malloc(sizeof(int));

    // Verifica se a alocação foi bem-sucedida
    if (p == NULL) {
        return 1;  // falha na alocação
    }

    // Leitura e impressão via ponteiro
    scanf("%d", p);
    printf("%d\n", *p);

    // Libera a memória alocada
    free(p);

    return 0;
}