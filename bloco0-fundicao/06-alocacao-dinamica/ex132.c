// 132 — O Guardião do Tamanho (Struct com Array Dinâmico)
// Aloca dinamicamente uma struct que contém um inteiro (tamanho)
// e um ponteiro para um array de inteiros. Preenche, imprime e libera
// na ordem correta: primeiro o array interno, depois a struct.
#include <stdio.h>
#include <stdlib.h>

// Struct que representa uma legião: tamanho + array dinâmico
struct data {
    int n;       // tamanho do array
    int *dado;   // ponteiro para o array de inteiros
};

int main(void) {
    // Aloca a struct dinamicamente
    struct data *p = (struct data *)malloc(sizeof(struct data));
    if (p == NULL) {
        return 1;  // falha na alocação da struct
    }

    // Lê o tamanho do array
    scanf("%d", &p->n);

    // Aloca o array dinamicamente com n inteiros
    p->dado = (int *)malloc((size_t)(p->n) * sizeof(*(p->dado)));
    if (p->dado == NULL) {
        free(p);  // libera a struct antes de encerrar
        return 1;
    }

    // Leitura dos elementos usando aritmética de ponteiros
    for (size_t i = 0; i < (size_t)p->n; i++) {
        scanf("%d", (p->dado) + i);
    }

    // Impressão dos elementos usando aritmética de ponteiros
    for (size_t i = 0; i < (size_t)p->n; i++) {
        printf("%d ", *((p->dado) + i));
    }
    printf("\n");

    // Libera primeiro o array interno...
    free(p->dado);
    p->dado = NULL;

    // ...e depois a struct
    free(p);
    p = NULL;

    return 0;
}