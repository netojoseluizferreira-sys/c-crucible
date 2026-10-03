// 179 — Contar Pares
// Percorre a lista contando quantos valores são pares.
// Reaproveita a travessia clássica de lista encadeada.
#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *prox;
} No;

No *no_criar(int valor);
void inserir_final(No **cabeca, int valor);
void inserir_meio(No **cabeca, int valor, int posicao);
void destruir_lista(No **cabeca);
int buscar(No *cabeca, int alvo);
void remover_inicio(No **cabeca);
void remover_final(No **cabeca);
void remover_valor(No **cabeca, int valor);
void remover_meio(No **cabeca, int posicao);
void imprimir(No *cabeca);
void inverter_lista(No **cabeca);
int contar_pares(No *cabeca);

int main(void) {
    int v, num, n2, alvo, posicao;

    scanf("%d %d", &v, &num);

    No *cabeca = no_criar(num);
    if (cabeca == NULL) return 1;

    for (int i = 0; i < v - 1; i++) {
        scanf("%d", &n2);
        inserir_final(&cabeca, n2);
    }

    remover_inicio(&cabeca);
    remover_final(&cabeca);

    imprimir(cabeca);

    scanf("%d", &alvo);
    printf("%d\n", buscar(cabeca, alvo));

    scanf("%d %d", &alvo, &posicao);
    inserir_meio(&cabeca, alvo, posicao);

    imprimir(cabeca);

    scanf("%d", &posicao);
    remover_meio(&cabeca, posicao);

    imprimir(cabeca);

    inverter_lista(&cabeca);
    imprimir(cabeca);

    // Conta os pares e imprime o total
    int pares = contar_pares(cabeca);
    printf("%d\n", pares);

    destruir_lista(&cabeca);

    imprimir(cabeca);

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

void destruir_lista(No **cabeca) {
    if (cabeca == NULL || *cabeca == NULL) return;

    No *atual = *cabeca;
    while (atual != NULL) {
        No *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    *cabeca = NULL;
}

int buscar(No *cabeca, int alvo) {
    int indice = 0;
    No *atual = cabeca;

    while (atual != NULL) {
        if (atual->valor == alvo) return indice;
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

void remover_valor(No **cabeca, int valor) {
    if (cabeca == NULL || *cabeca == NULL) return;

    No **atual = cabeca;

    while (*atual != NULL) {
        if ((*atual)->valor == valor) {
            No *remover = *atual;
            *atual = remover->prox;
            free(remover);
            return;
        }
        atual = &(*atual)->prox;
    }
}

void inserir_meio(No **cabeca, int valor, int posicao) {
    No *novo = no_criar(valor);
    if (novo == NULL) return;

    if (*cabeca == NULL || posicao <= 0) {
        novo->prox = *cabeca;
        *cabeca = novo;
        return;
    }

    No *atual = *cabeca;
    int indice = 0;

    while (atual->prox != NULL && indice < posicao - 1) {
        atual = atual->prox;
        indice++;
    }

    novo->prox = atual->prox;
    atual->prox = novo;
}

void remover_meio(No **cabeca, int posicao) {
    if (cabeca == NULL || *cabeca == NULL) return;

    if (posicao <= 0) {
        remover_inicio(cabeca);
        return;
    }

    No *atual = *cabeca;
    int indice = 0;

    while (atual->prox != NULL && indice < posicao - 1) {
        atual = atual->prox;
        indice++;
    }

    if (atual->prox == NULL) return;

    No *remover = atual->prox;
    atual->prox = remover->prox;
    free(remover);
}

void imprimir(No *cabeca) {
    No *atual = cabeca;
    if (atual == NULL) {
        printf("LISTA DESTRUIDA\n");
        return;
    }
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->prox;
    }
    printf("NULL\n");
}

void inverter_lista(No **cabeca) {
    if (cabeca == NULL || *cabeca == NULL || (*cabeca)->prox == NULL) {
        return;
    }

    No *anterior = NULL;
    No *atual = *cabeca;
    No *proximo = NULL;

    while (atual != NULL) {
        proximo = atual->prox;
        atual->prox = anterior;
        anterior = atual;
        atual = proximo;
    }

    *cabeca = anterior;
}

// Conta quantos valores pares existem na lista
// Reaproveita a travessia clássica: percorre do início ao fim
int contar_pares(No *cabeca) {
    int pares = 0;
    No *atual = cabeca;

    while (atual != NULL) {
        if (atual->valor % 2 == 0) {
            pares++;
        }
        atual = atual->prox;
    }

    return pares;
}