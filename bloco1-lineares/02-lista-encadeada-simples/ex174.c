// 174 — Remover por Valor
// Remove a primeira ocorrência de um valor usando ponteiro duplo.
// Percorre a lista com No **atual para poder pular o nó sem guardar o anterior.
#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *prox;
} No;

No *no_criar(int valor);
void inserir_final(No **cabeca, int valor);
void destruir_lista(No *cabeca);
int buscar(No *cabeca, int alvo);
void remover_inicio(No **cabeca);
void remover_final(No **cabeca);
void remover_valor(No **cabeca, int valor);

int main(void) {
    int v, num, n2, alvo;

    scanf("%d %d", &v, &num);

    No *cabeca = no_criar(num);
    if (cabeca == NULL) return 1;

    for (int i = 0; i < v - 1; i++) {
        scanf("%d", &n2);
        inserir_final(&cabeca, n2);
    }

    remover_inicio(&cabeca);
    remover_final(&cabeca);

    No *atual = cabeca;
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->prox;
    }
    printf("nil\n");

    scanf("%d", &alvo);
    printf("%d\n", buscar(cabeca, alvo));

    remover_valor(&cabeca, alvo);

    atual = cabeca;
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

void inserir_final(No **cabeca, int valor) {
    No *novo = no_criar(valor);
    if (novo == NULL) return;

    if (*cabeca == NULL) {
        *cabeca = novo;
        return;
    }

    No *atual = *cabeca;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }

    atual->prox = novo;
}

void destruir_lista(No *cabeca) {
    No *atual = cabeca;
    while (atual != NULL) {
        No *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
}

int buscar(No *cabeca, int alvo) {
    int indice = 0;
    No *atual = cabeca;

    while (atual != NULL) {
        if (atual->valor == alvo) {
            return indice;
        }
        atual = atual->prox;
        indice++;
    }

    return -1;
}

void remover_inicio(No **cabeca) {
    if (cabeca == NULL || *cabeca == NULL) return;

    No *atual = *cabeca;
    No *proximo = atual->prox;

    free(atual);
    *cabeca = proximo;
}

void remover_final(No **cabeca) {
    if (cabeca == NULL || *cabeca == NULL) return;

    No *atual = *cabeca;

    if (atual->prox == NULL) {
        free(atual);
        *cabeca = NULL;
        return;
    }

    while (atual->prox->prox != NULL) {
        atual = atual->prox;
    }

    free(atual->prox);
    atual->prox = NULL;
}

// Remove a primeira ocorrência do valor usando ponteiro duplo
// No **atual aponta para o ponteiro que aponta para o nó atual
// Assim, *atual = (*atual)->prox pula o nó sem precisar de "anterior"
void remover_valor(No **cabeca, int valor) {
    if (cabeca == NULL || *cabeca == NULL) return;

    // atual aponta para o ponteiro que aponta para o nó atual
    // Começa apontando para o próprio cabeca (No **)
    No **atual = cabeca;

    // Percorre enquanto houver nó
    while (*atual != NULL) {
        if ((*atual)->valor == valor) {
            // Achou: guarda o nó a ser removido
            No *remover = *atual;

            // Faz o ponteiro que apontava para o removido apontar para o próximo
            // Isso "pula" o nó removido da lista
            *atual = remover->prox;

            // Libera o nó removido
            free(remover);

            // Sai da função: remove só a primeira ocorrência
            return;
        }

        // Avança: atual agora aponta para o ponteiro prox do nó atual
        atual = &(*atual)->prox;
    }
}