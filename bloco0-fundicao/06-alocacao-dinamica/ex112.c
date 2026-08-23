// 112 — A Legião de Almas (malloc para Arrays)
// Aloca dinamicamente um array de N inteiros, armazena os valores lidos,
// imprime-os na ordem inversa e libera toda a memória.
// Demonstra alocação dinâmica para tamanho determinado em tempo de execução.
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *p = (int *)malloc(sizeof(int));

    // Verifica se a alocação do inteiro foi bem-sucedida
    if (p == NULL) {
        return 1;  // falha na alocação
    }

    // Lê o tamanho do array
    scanf("%d", p);

    // Aloca o array dinamicamente com o tamanho lido
    int *arr = (int *)malloc((size_t)(*p) * sizeof(int));

    // Verifica se a alocação do array foi bem-sucedida
    if (arr == NULL) {
        free(p);   // libera o inteiro alocado antes de sair
        return 1;  // falha na alocação
    }

    // Leitura dos elementos usando aritmética de ponteiros
    for (int i = 0; i < *p; i++) {
        scanf("%d", arr + i);
    }

    // Impressão na ordem inversa usando aritmética de ponteiros
    for (int i = *p - 1; i >= 0; i--) {
        printf("%d ", *(arr + i));
    }
    printf("\n");

    // Libera toda a memória alocada
    free(p);
    free(arr);

    return 0;
}