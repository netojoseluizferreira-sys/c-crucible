// 183 — Merge de Listas Ordenadas
// Mescla duas listas ordenadas em uma terceira lista ordenada.
// Copia os valores, sem compartilhar nós entre as listas.
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
No *copiar(No *cabeca);
void concatenar(No **cabeca1, No *cabeca2);
int tem_ciclo(No *cabeca);
No *mesclar(No *l1, No *l2);

int main(void) {
    int n1, n2, v;

    // Lê a primeira lista ordenada
    No *cabeca = NULL;
    No *cabeca2 = NULL;
    scanf("%d", &n1);
    for (int i = 0; i < n1; i++) {
        scanf("%d", &v);
        inserir_final(&cabeca, v);
    }

    // Lê a segunda lista ordenada
    scanf("%d", &n2);
    for (int i = 0; i < n2; i++) {
        scanf("%d", &v);
        inserir_final(&cabeca2, v);
    }

    imprimir(cabeca);
    imprimir(cabeca2);

    // Mescla as duas listas em uma terceira
    No *mesclado = mesclar(cabeca, cabeca2);

    // Destrói as originais — a mesclada é independente
    destruir_lista(&cabeca);
    destruir_lista(&cabeca2);

    imprimir(mesclado);
    destruir_lista(&mesclado);

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

No *copiar(No *cabeca) {
    No *copia = NULL;

    No *atual = cabeca;
    while (atual != NULL) {
        inserir_final(&copia, atual->valor);
        atual = atual->prox;
    }

    return copia;
}

void concatenar(No **cabeca1, No *cabeca2) {
    No *atual = cabeca2;

    while (atual != NULL) {
        inserir_final(cabeca1, atual->valor);
        atual = atual->prox;
    }
}

int tem_ciclo(No *cabeca) {
    No *slow = cabeca;
    No *fast = cabeca;

    while (fast != NULL && fast->prox != NULL) {
        slow = slow->prox;
        fast = fast->prox->prox;
        if (slow == fast) return 1;
    }

    return 0;
}

// Mescla duas listas ordenadas em uma terceira, preservando a ordem
// Usa dois ponteiros (atual1, atual2) para percorrer as duas listas
// Compara os valores e insere o menor na lista resultado
// Quando uma lista acaba, anexa o restante da outra
No *mesclar(No *l1, No *l2) {
    No *copia = NULL;      // lista resultado (vazia)
    No *atual1 = l1;        // percorre a primeira lista
    No *atual2 = l2;        // percorre a segunda lista

    // Enquanto houver elementos nas duas listas, compara e insere o menor
    while (atual1 != NULL && atual2 != NULL) {
        if (atual1->valor < atual2->valor) {
            inserir_final(&copia, atual1->valor);  // primeiro é menor
            atual1 = atual1->prox;
        } else {
            inserir_final(&copia, atual2->valor);  // segundo é menor (ou igual)
            atual2 = atual2->prox;
        }
    }

    // Se a primeira ainda tem elementos, anexa o restante
    while (atual1 != NULL) {
        inserir_final(&copia, atual1->valor);
        atual1 = atual1->prox;
    }

    // Se a segunda ainda tem elementos, anexa o restante
    while (atual2 != NULL) {
        inserir_final(&copia, atual2->valor);
        atual2 = atual2->prox;
    }

    return copia;
}