// 096 — O Julgamento das Almas (Ponteiros para Funções com qsort)
// Lê N inteiros, ordena-os em ordem crescente usando a função qsort
// da biblioteca padrão e imprime o array ordenado.
//
// A função compar() é um callback passado para qsort. Ela recebe dois
// ponteiros genéricos (const void*), faz o cast para const int* e
// retorna a diferença entre os valores. O retorno negativo, zero ou
// positivo determina a ordem dos elementos.
//
// qsort espera uma função com a assinatura:
//   int (*)(const void*, const void*)
#include <stdio.h>
#include <stdlib.h>

int compar(const void *a, const void *b);

int main(void) {
    size_t tamanho;

    scanf("%zu", &tamanho);

    int *lista = (int *)malloc(tamanho * sizeof(int));

    if (lista == NULL) return 1;

    // Leitura dos elementos usando aritmética de ponteiros
    for (size_t i = 0; i < tamanho; i++) {
        scanf("%d", lista + i);
    }

    // Ordenação via qsort com callback compar
    qsort(lista, tamanho, sizeof(int), compar);

    // Impressão dos elementos ordenados usando aritmética de ponteiros
    for (size_t i = 0; i < tamanho; i++) {
        printf("%d ", *(lista + i));
    }
    printf("\n");

    free(lista);

    return 0;
}

// Função de comparação para qsort
// Retorna negativo se *a < *b, zero se iguais, positivo se *a > *b
int compar(const void *a, const void *b) {
    // Cast de void* para int* com qualificador const
    return (*(const int *)a - *(const int *)b);
}