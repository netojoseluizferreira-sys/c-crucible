// 176 — Remover em Posição
// Remove o nó na posição indicada (0-indexada), ajustando os ponteiros.
// Trata lista vazia, posição inválida, remoção no início e no meio.
#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *prox;
} No;

No *no_criar(int valor);
void inserir_final(No **cabeca, int valor);
void inserir_meio(No **cabeca, int valor, int posicao);
void destruir_lista(No *cabeca);
int buscar(No *cabeca, int alvo);
void remover_inicio(No **cabeca);
void remover_final(No **cabeca);
void remover_valor(No **cabeca, int valor);
void remover_meio(No **cabeca, int posicao);
void imprimir(No *cabeca);

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

    // Nova operação: remover em posição
    scanf("%d", &posicao);
    remover_meio(&cabeca, posicao);

    imprimir(cabeca);

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

// Remove o nó na posição indicada (0-indexada)
// Casos:
//   - lista vazia: nada a fazer
//   - posicao <= 0: remove o primeiro (reaproveita remover_inicio)
//   - posicao >= tamanho: percorre até o último e remove
//   - caso contrário: percorre até o anterior e pula o nó removido
void remover_meio(No **cabeca, int posicao) {
    // Caso 1: lista vazia
    if (cabeca == NULL || *cabeca == NULL) return;

    // Caso 2: remover do início (posição 0 ou negativa)
    if (posicao <= 0) {
        remover_inicio(cabeca);
        return;                 
    }

    // Caso 3: percorre até o nó ANTERIOR à posição
    No *atual = *cabeca;
    int indice = 0;

    while (atual->prox != NULL && indice < posicao - 1) {
        atual = atual->prox;
        indice++;
    }

    // Se atual->prox for NULL, a posição está além do fim → nada a remover
    if (atual->prox == NULL) return;

    // Remove o nó depois de 'atual'
    No *remover = atual->prox;      // guarda o nó a ser removido
    atual->prox = remover->prox;    // pula o nó removido
    free(remover);                   // libera a memória
}

void imprimir(No *cabeca) {
    No *atual = cabeca;
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->prox;
    }
    printf("NULL\n");
}