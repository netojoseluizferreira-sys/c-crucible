// 230 — Contando e Destruindo
// Pilha encadeada simples (nó + topo).
// Destruir percorre a pilha, conta os nós e libera cada um.
// O main lê N, empilha, imprime a contagem, destrói a pilha e mostra
// o estado final do topo.
#include <stdio.h>
#include <stdlib.h>

// Nó da pilha: valor + ponteiro para o próximo
typedef struct No {
    int valor;
    struct No *prox;
} No;

// Protótipos
No *no_criar(int valor);
void push(No **topo, int valor);
int pop(No **topo, int *valor);
int peek(No *topo, int *valor);
void imprimir(No *topo);
void destruir_lista(No **topo, int *tam);

int main(void) {
    int num, v, tam;
    No *topo = NULL;

    // Lê N e empilha todos
    scanf("%d", &num);
    for (int i = 0; i < num; i++) {
        scanf("%d", &v);
        push(&topo, v);
    }

    imprimir(topo);

    // Destrói e conta os nós removidos
    destruir_lista(&topo, &tam);
    printf("total: %d\n", tam);

    imprimir(topo);

    // Estado final do topo
    if (topo == NULL)
        printf("topo: (nil)\n");
    else
        printf("topo: %d\n", topo->valor);

    return 0;
}

// Aloca um nó com valor e prox = NULL
No *no_criar(int valor) {
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL) return NULL;

    novo->valor = valor;
    novo->prox = NULL;

    return novo;
}

// Empilha: insere um novo nó no TOPO da pilha
void push(No **topo, int valor) {
    No *novo = no_criar(valor);
    if (novo == NULL) return;

    novo->prox = *topo;
    *topo = novo;
}

// Desempilha: remove o nó do TOPO e devolve seu valor via ponteiro
// Retorna 1 se sucesso, 0 se a pilha está vazia
int pop(No **topo, int *valor) {
    if (topo == NULL || *topo == NULL) return 0;

    No *atual = *topo;
    *valor = atual->valor;
    *topo = atual->prox;
    free(atual);

    return 1;
}

// Espia o TOPO: devolve o valor sem remover.
int peek(No *topo, int *valor) {
    if (topo == NULL) return 0;

    *valor = topo->valor;

    return 1;
}

// Imprime a pilha do TOPO até a BASE no formato [a,b,c]
void imprimir(No *topo) {
    No *atual = topo;
    if (atual == NULL) {
        printf("PILHA VAZIA\n");
        return;
    }

    printf("[");
    while (atual != NULL) {
        printf("%d", atual->valor);
        atual = atual->prox;
        if (atual != NULL) printf(",");
    }
    printf("]\n");
}

// Libera todos os nós da pilha, conta quantos foram liberados e
// seta *topo para NULL. O contador 'tam' devolve o total por ponteiro.
void destruir_lista(No **topo, int *tam) {
    if (topo == NULL || *topo == NULL) {
        if (tam != NULL) *tam = 0;
        return;
    }

    int i = 0;
    No *atual = *topo;
    while (atual != NULL) {
        No *proximo = atual->prox;
        free(atual);
        atual = proximo;
        i++;
    }
    *topo = NULL;
    if (tam != NULL) *tam = i;
}