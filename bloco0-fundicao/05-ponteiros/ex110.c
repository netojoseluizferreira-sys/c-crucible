// 110 — O Executor Genérico (void*, qsort e Callback)
// Lê um vetor de inteiros e passa esse vetor para uma função genérica,
// capaz de ordenar os dados com qsort e aplicar uma operação em cada elemento.
//
// A função executar recebe:
// - dados: ponteiro genérico para o vetor
// - n: quantidade de elementos
// - tamanho_elemento: tamanho de cada elemento em bytes
// - operacao: callback que modifica cada elemento
// - comparar: callback usado pelo qsort para ordenar os elementos
#include <stdio.h>
#include <stdlib.h>

void executar(void *dados, size_t n, size_t tamanho_elemento, void (*operacao)(void *), int (*comparar)(const void *, const void *));
void operac(void *p);
int compar(const void *a, const void *b);

int main(void){
    size_t n;

    scanf("%zu", &n);

    int dados[n];

    // Lê os valores do vetor usando aritmética de ponteiros
    for (size_t i = 0; i < n; i++) {
        scanf("%d", dados + i);
    }

    // Executa a ordenação e a operação sobre todos os elementos
    executar(dados, n, sizeof *dados, operac, compar);

    return 0;
}

// Ordena um bloco genérico de dados e aplica uma operação em cada elemento
void executar(void *dados, size_t n, size_t tamanho_elemento, void (*operacao)(void *), int (*comparar)(const void *, const void *)){
    qsort(dados, n, tamanho_elemento, comparar);

    // Percorre o vetor já ordenado, aplica a operação e imprime cada valor
    for (size_t i = 0; i < n; i++) {
        operacao((int *)dados + i);
        printf("%d ", *((int *)dados + i));
    }
}

// Operação aplicada a cada elemento: incrementa o inteiro em 1
void operac(void *p){
    *((int *)p) += 1;
}

// Comparador para qsort em ordem crescente
int compar(const void *a, const void *b){
    const int x = *(const int *)a;
    const int y = *(const int *)b;

    if (x < y) {
        return -1;
    }

    if (x > y) {
        return 1;
    }

    return 0;
}