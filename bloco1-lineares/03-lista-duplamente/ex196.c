// 196 — O Elo de Duas Faces
// Cria um nó de lista dupla e verifica que prox e ant começam em NULL.
#include <stdio.h>
#include <stdlib.h>

typedef struct NoDuplo {
    int valor;
    struct NoDuplo *prox;
    struct NoDuplo *ant;
} NoDuplo;

NoDuplo *noDuplo_criar(int valor);

int main(void) {
    int num;
    scanf("%d", &num);

    NoDuplo *start = noDuplo_criar(num);
    if (start == NULL) return 1;

    if (start->ant == NULL)
        printf("ant: (nil)\n");

    printf("Valor: %d\n", start->valor);

    if (start->prox == NULL)
        printf("prox: (nil)\n");

    free(start);
    return 0;
}

NoDuplo *noDuplo_criar(int valor) {
    NoDuplo *novo = (NoDuplo *)malloc(sizeof(NoDuplo));
    if (novo == NULL) return NULL;

    novo->valor = valor;
    novo->prox = NULL;
    novo->ant = NULL;

    return novo;
}