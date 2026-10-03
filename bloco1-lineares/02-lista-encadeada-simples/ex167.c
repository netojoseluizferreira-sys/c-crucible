// 167 — Inserir no Início
// Insere um novo nó no início da lista. O novo nó vira a nova cabeça.
#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *prox;
} No;

No *no_criar(int valor);
void inserir_inicio(No **cabeca, int valor);
void destruir_lista(No *cabeca);

int main(void) {
    int num, n2;
    scanf("%d", &num);

    No *cabeca = no_criar(num);
    if (cabeca == NULL) return 1;

    scanf("%d", &n2);
    inserir_inicio(&cabeca, n2);

    No *atual = cabeca;
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->prox;
    }
    printf("nil\n");

    destruir_lista(cabeca);
    return 0;
}

No *no_criar(int valor) {
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL) return NULL;

    novo->valor = valor;
    novo->prox = NULL;

    return novo;
}

void inserir_inicio(No **cabeca, int valor) {
    No *novo = no_criar(valor);
    if (novo == NULL) return;

    novo->prox = *cabeca;   // novo aponta para o antigo primeiro
    *cabeca = novo;         // cabeça agora é o novo nó
}

void destruir_lista(No *cabeca) {
    No *atual = cabeca;
    while (atual != NULL) {
        No *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
}