// 104 — O Altar do Esquecimento (Ponteiros para Funções que Retornam Ponteiros)
// Lê um inteiro N, aloca dinamicamente um array de N inteiros, preenche
// com valores de 1 a N e retorna o ponteiro para o array.
//
// A função gerar_numero() recebe um array alocado e seu tamanho,
// preenche com a sequência e retorna o ponteiro. A função array()
// encapsula a alocação dinâmica.
//
// Memória alocada: precisa ser liberada com free() após o uso.
#include <stdio.h>
#include <stdlib.h>

int *array(int n);
int *gerar_numero(int *arr, int n);

int main(void) {
    int n;

    scanf("%d", &n);

    // Aloca o array e preenche com a sequência
    int *p = gerar_numero(array(n), n);

    if (p == NULL) {
        return 1;  // falha na alocação
    }

    // Impressão dos elementos usando aritmética de ponteiros
    for (int i = 0; i < n; i++) {
        printf("%d ", *(p + i));
    }
    printf("\n");

    // Liberação da memória alocada
    free(p);

    return 0;
}

// Aloca dinamicamente um array de n inteiros e retorna o ponteiro
int *array(int n) {
    return (int *)malloc((size_t)n * sizeof(int));
}

// Preenche o array com a sequência de 1 a n e retorna o ponteiro
int *gerar_numero(int *arr, int n) {
    // Verifica se a alocação foi bem-sucedida
    if (arr == NULL) {
        return NULL;  // retorna NULL para indicar falha
    }

    // Preenche o array com valores de 1 a n
    for (int i = 0; i < n; i++) {
        *(arr + i) = 1 + i;
    }

    return arr;
}