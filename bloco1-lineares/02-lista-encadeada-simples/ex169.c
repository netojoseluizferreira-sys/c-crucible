// 169 — Inserir no Final
// Insere um novo nó no final da lista. Percorre até o último nó e anexa.
#include <stdio.h>
#include <stdlib.h>

// Struct do nó: guarda um valor inteiro e um ponteiro para o próximo nó
typedef struct No {
    int valor;
    struct No *prox;
} No;

// Protótipos das funções usadas
No *no_criar(int valor);
void inserir_inicio(No **cabeca, int valor);
void inserir_final(No **cabeca, int valor);
void destruir_lista(No *cabeca);

int main(void) {
    int v, num, n2;

    // Lê a quantidade de valores e o primeiro número
    scanf("%d %d", &v, &num);

    // Cria a lista com o primeiro nó
    No *cabeca = no_criar(num);
    if (cabeca == NULL) return 1;

    // Lê os demais valores e insere no final
    for (int i = 0; i < v - 1; i++) {
        scanf("%d", &n2);
        inserir_final(&cabeca, n2);
    }

    // Percorre a lista do início ao fim, imprimindo cada valor
    No *atual = cabeca;
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->prox;
    }
    printf("nil\n");

    // Libera toda a memória alocada
    destruir_lista(cabeca);
    return 0;
}

// Aloca um novo nó com o valor fornecido e prox = NULL
No *no_criar(int valor) {
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL) return NULL;

    novo->valor = valor;
    novo->prox = NULL;

    return novo;
}

// Insere um novo nó no FINAL da lista
// Percorre até o último nó (aquele cujo prox é NULL) e anexa o novo
void inserir_final(No **cabeca, int valor) {
    No *novo = no_criar(valor);
    if (novo == NULL) return;

    // Caso especial: lista vazia → o novo nó vira a cabeça
    if (*cabeca == NULL) {
        *cabeca = novo;
        return;
    }

    // Percorre até o último nó (para quando prox é NULL)
    No *atual = *cabeca;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }

    // O último nó agora aponta para o novo
    atual->prox = novo;
}

// Libera todos os nós da lista
// Guarda o próximo antes de liberar o atual para não perder a referência
void destruir_lista(No *cabeca) {
    No *atual = cabeca;
    while (atual != NULL) {
        No *proximo = atual->prox;  // guarda o próximo antes de liberar
        free(atual);                 // libera o nó atual
        atual = proximo;             // avança para o próximo
    }
}