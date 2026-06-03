// 083 — O Altar do Sacrifício (Ponteiros para Ponteiros III)
// Lê L linhas e C colunas, aloca dinamicamente uma matriz L×C
// usando ponteiro duplo (int **): cada linha é um array independente.
// Preenche com valores lidos, imprime e libera a memória.
//
// Esta abordagem demonstra indireção dupla:
// - matriz[i] é um ponteiro para a linha i
// - *(*(matriz + i) + j) acessa o elemento via aritmética de ponteiros
// - A liberação ocorre na ordem inversa da alocação: linhas primeiro, depois a matriz.
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    size_t l, c;

    scanf("%zu %zu", &l, &c);

    // Alocação do array de ponteiros para as linhas
    int **matriz = (int **)malloc(l * sizeof(*matriz));

    if (matriz == NULL) {
        return 1;  // falha na alocação do array de ponteiros
    }

    // Alocação de cada linha e leitura dos elementos
    for (size_t i = 0; i < l; i++) {
        // Aloca a linha i (um array de c inteiros)
        *(matriz + i) = (int *)malloc(c * sizeof(**matriz));

        if (*(matriz + i) == NULL) {
            // Falha na alocação: libera todas as linhas já alocadas
            // e o array de ponteiros antes de encerrar
            while (i > 0U) {
                i--;
                free(*(matriz + i));  // libera a linha i
            }
            free(matriz);  // libera o array de ponteiros
            return 1;
        }

        // Leitura dos elementos da linha i
        for (size_t j = 0; j < c; j++) {
            scanf("%d", *(matriz + i) + j);  // *(matriz + i) é a linha i
        }
    }

    // Impressão formatada usando dupla indireção
    for (size_t i = 0; i < l; i++) {
        printf("[ ");
        for (size_t j = 0; j < c; j++) {
            // *(matriz + i) é a linha i
            // *(*(matriz + i) + j) é o elemento na coluna j dessa linha
            printf("%d ", *(*(matriz + i) + j));
        }
        printf("]\n");
    }

    // Liberação: primeiro cada linha, depois o array de ponteiros
    for (size_t i = 0; i < l; i++) {
        free(*(matriz + i));  // libera a linha i
    }
    free(matriz);  // libera o array de ponteiros

    return 0;
}