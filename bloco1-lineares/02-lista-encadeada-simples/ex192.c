// 192 — Palíndromo com Pilha
// Verifica se a lista é palíndromo usando uma pilha auxiliar.
// Estratégia: empilha a PRIMEIRA metade, depois compara com a segunda.
#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *prox;
} No;

No *no_criar(int valor);
void push(No **topo, int valor);
int pop(No **topo, int *valor);
void imprimir(No *topo);
void destruir_lista(No **topo);
int eh_palindromo(No *cabeca);

int main(void) {
    int n, valor;
    No *pilha_principal = NULL;

    // Lê a quantidade de elementos
    if (scanf("%d", &n) != 1) return 0;

    // Lê os N valores e empilha (topo = último lido)
    for (int i = 0; i < n; i++) {
        scanf("%d", &valor);
        push(&pilha_principal, valor);
    }

    // Verifica se é palíndromo
    if (eh_palindromo(pilha_principal)) {
        printf("Palindromo\n");
    } else {
        printf("Nao palindromo\n");
    }

    destruir_lista(&pilha_principal);

    return 0;
}

// Aloca um novo nó
No *no_criar(int valor) {
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL) return NULL;

    novo->valor = valor;
    novo->prox = NULL;

    return novo;
}

// Empilha: insere no TOPO (início da lista)
void push(No **topo, int valor) {
    No *novo = no_criar(valor);
    if (novo == NULL) return;

    novo->prox = *topo;
    *topo = novo;
}

// Desempilha: remove do TOPO; devolve valor via ponteiro (1 = sucesso, 0 = vazia)
int pop(No **topo, int *valor) {
    if (topo == NULL || *topo == NULL) return 0;

    No *atual = *topo;
    *valor = atual->valor;
    *topo = atual->prox;
    free(atual);

    return 1;
}

// Imprime do topo até a base
void imprimir(No *topo) {
    No *atual = topo;
    if (atual == NULL) {
        printf("PILHA VAZIA\n");
        return;
    }
    printf("PILHA ATUAL: ");
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->prox;
    }
    printf("NULL\n");
}

// Libera todos os nós
void destruir_lista(No **topo) {
    if (topo == NULL || *topo == NULL) return;

    No *atual = *topo;
    while (atual != NULL) {
        No *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    *topo = NULL;
}

// Verifica se a lista é palíndromo
// Empilha a primeira metade, pula o meio (se ímpar) e compara com a segunda
int eh_palindromo(No *cabeca) {
    if (cabeca == NULL || cabeca->prox == NULL) return 1;

    // Conta os nós
    int total = 0;
    No *atual = cabeca;
    while (atual != NULL) {
        total++;
        atual = atual->prox;
    }

    // Empilha a primeira metade
    No *aux = NULL;
    atual = cabeca;
    int metade = total / 2;

    for (int i = 0; i < metade; i++) {
        push(&aux, atual->valor);
        atual = atual->prox;
    }

    // Se ímpar, pula o nó do meio
    if (total % 2 != 0) {
        atual = atual->prox;
    }

    // Compara a pilha (ordem inversa) com a segunda metade
    int v;
    while (atual != NULL) {
        pop(&aux, &v);
        if (atual->valor != v) {
            destruir_lista(&aux);
            return 0;
        }
        atual = atual->prox;
    }

    destruir_lista(&aux);
    return 1;
}