// 173 — Remover do Final
// Remove o último nó da lista. Precisa percorrer até o penúltimo para
// ajustar seu prox para NULL. Trata lista vazia e lista com um nó.
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
    if (cabeca == NULL || *cabeca == NULL) {
        return;
    }

    No *atual = *cabeca;
    No *proximo = atual->prox;

    free(atual);

    *cabeca = proximo;
}

// Remove o último nó da lista
// lista com 2+ nós (percorre até o penúltimo, ajusta prox = NULL e libera o último)
void remover_final(No **cabeca) {
    if (cabeca == NULL || *cabeca == NULL) {
        return;  // lista vazia, nada a remover
    }

    No *atual = *cabeca;

    // Caso especial: lista com um único nó → vira lista vazia
    if (atual->prox == NULL) {
        free(atual);
        *cabeca = NULL;
        return;
    }

    // Percorre até o penúltimo nó (aquele cujo prox é o último)
    while (atual->prox->prox != NULL) {
        atual = atual->prox;
    }

    // atual agora é o penúltimo
    free(atual->prox);       // libera o último
    atual->prox = NULL;      // penúltimo vira o novo último
}