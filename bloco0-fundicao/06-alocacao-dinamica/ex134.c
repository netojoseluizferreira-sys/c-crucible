// 134 — O Arsenal Genérico (void* com Alocação Dinâmica)
// Cria uma função genérica que aloca um array de n elementos, cada um
// com tamanho_elemento bytes, e inicializa todas as posições copiando
// os bytes do valor_inicial com memcpy. Retorna void*.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função genérica: aloca e inicializa um array de n elementos
void *criar_array(size_t tamanho_elemento, int n, void *valor_inicial);

int main(void) {
    int valor = 42;
    int n;

    scanf("%d", &n);

    // Cria um array de n inteiros inicializados com 42
    int *array = (int *)criar_array(sizeof(int), n, &valor);
    if (array == NULL) {
        return 1;  // falha na alocação
    }

    // Impressão dos valores
    for (size_t i = 0; i < (size_t)n; i++) {
        printf("%d ", *(array + i));
    }
    printf("\n");

    // Libera a memória alocada
    free(array);
    array = NULL;

    return 0;
}

// Aloca um array genérico e inicializa cada posição com valor_inicial
void *criar_array(size_t tamanho_elemento, int n, void *valor_inicial) {
    // Aloca n elementos de tamanho_elemento bytes cada
    void *arr = malloc((size_t)n * tamanho_elemento);
    if (arr == NULL) {
        return NULL;  // falha na alocação
    }

    // Para cada elemento, copia os bytes do valor_inicial
    // Converte para char* para avançar byte a byte
    unsigned char *destino = (unsigned char *)arr;
    unsigned char *origem = (unsigned char *)valor_inicial;

    for (size_t i = 0; i < (size_t)n; i++) {
        memcpy(destino + (i * tamanho_elemento), origem, tamanho_elemento);
    }

    return arr;
}