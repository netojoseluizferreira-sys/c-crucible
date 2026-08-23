// 130 — O Rito da Transmutação (realloc para Trocar Tipo)
// Aloca um array de N unsigned char, preenche com valores de 1 a N,
// realoca para um array de N int e imprime os valores convertidos.
// Usa 'array' como referência principal após o realloc.
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    size_t n;
    scanf("%zu", &n);

    // Aloca o array original como unsigned char (1 byte por elemento)
    unsigned char *array = (unsigned char *)malloc(n * sizeof(unsigned char));
    if (array == NULL) return 1;

    // Preenche o array com valores de 1 a N
    for (size_t i = 0; i < n; i++) {
        *(array + i) = (unsigned char)(i + 1);
    }

    // Realoca o bloco para n * sizeof(int) bytes
    // Usa 'temp' apenas para a realocação segura
    int *temp = (int *)realloc(array, n * sizeof(int));
    if (temp == NULL) {
        free(array);
        array = NULL;
        return 1;
    }

    // A partir daqui, 'array' é interpretado como int*
    array = (unsigned char *)temp;

    // Preenche os valores como int, lendo dos primeiros bytes preservados
    // Percorre de trás para frente para não sobrescrever dados antes de lê-los
    for (size_t i = n; i > 0; i--) {
        size_t idx = i - 1;
        // Lê o valor original (unsigned char) e converte para int
        unsigned char valor_original = *(array + idx);
        // Armazena como int na posição correspondente
        *(temp + idx) = (int)valor_original;
    }

    for (size_t i = 0; i < n; i++) {
        printf("%d ", *(temp + i));
    }
    printf("\n");

    // Libera a memória
    free(array);
    array = NULL;

    return 0;
}