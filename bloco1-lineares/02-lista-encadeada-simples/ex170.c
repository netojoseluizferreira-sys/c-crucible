// 170 — Contar os Nós
// Percorre a lista do início ao fim contando quantos nós existem.
// Demonstra a travessia com contador e reaproveita as operações de lista.
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
int contar(No *cabeca);

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

    // Conta os nós e imprime o total
    printf("%d\n", contar(cabeca));

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
void destruir_lista(No *cabeca) {
    No *atual = cabeca;
    while (atual != NULL) {
        No *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
}

// Conta quantos nós existem na lista
// Percorre do início ao fim incrementando um contador
int contar(No *cabeca) {
    int contagem = 0;
    No *atual = cabeca;

    while (atual != NULL) {
        No *proximo = atual->prox;  // guarda o próximo antes de avançar
        atual = proximo;             // avança para o próximo nó
        contagem += 1;               // conta o nó atual
    }

    return contagem;
}