// 182 — Detectar Ciclo (Floyd)
// Usa o algoritmo de Floyd (tartaruga e lebre) para verificar
// se a lista possui um ciclo. Retorna 1 se tem ciclo, 0 caso contrário.
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

int main(void) {
    int v;

    No *cabeca = NULL;
    for (int i = 0; i < 5; i++) {
        scanf("%d", &v);
        inserir_final(&cabeca, v);
    }

    imprimir(cabeca);

    // Cria um ciclo artificial: o último nó aponta para o segundo
    cabeca->prox->prox->prox->prox->prox = cabeca->prox;

    if (tem_ciclo(cabeca) == 1) printf("Ciclo detectado\n");

    // Quebra o ciclo
    cabeca->prox->prox->prox->prox->prox = NULL;

    if (tem_ciclo(cabeca) == 0) printf("Sem ciclo\n");

    imprimir(cabeca);

    destruir_lista(&cabeca);

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

// Detecta ciclo na lista usando o algoritmo de Floyd (tartaruga e lebre)
// slow (tartaruga) avança 1 nó por vez
// fast (lebre) avança 2 nós por vez
// Se houver ciclo, uma hora eles se encontram
// Se não houver, fast chega ao fim (NULL) e o loop para
int tem_ciclo(No *cabeca) {
    No *slow = cabeca;
    No *fast = cabeca;

    while (fast != NULL && fast->prox != NULL) {
        slow = slow->prox;          // anda 1
        fast = fast->prox->prox;    // anda 2

        if (slow == fast) return 1; // se encontrou, tem ciclo
    }

    return 0;                       // chegou ao fim sem encontrar → sem ciclo
}