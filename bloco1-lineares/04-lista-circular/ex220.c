// 220 — Detecção de Ciclo em Lista Linear vs Circular
// Usa o algoritmo de Floyd (tartaruga e lebre) para detectar ciclo.
// A função funciona tanto para lista linear quanto circular.
// O main monta uma lista circular, verifica se tem ciclo, quebra o
// anel (cauda->prox = NULL) e verifica de novo.
#include <stdio.h>
#include <stdlib.h>

// Nó da lista dupla circular: valor + prox + ant
typedef struct NoDuplo {
    int valor;
    struct NoDuplo *prox;
    struct NoDuplo *ant;
} NoDuplo;

// Lista circular dupla: cabeca, cauda e tamanho
typedef struct ListaCircular {
    NoDuplo *cabeca;
    NoDuplo *cauda;
    int tamanho;
} ListaCircular;

// Protótipos
NoDuplo *noDuplo_criar(int valor);
void inserir_inicio(ListaCircular *l, int valor);
void inserir_fim(ListaCircular *l, int valor);
void imprimir(ListaCircular *l);
void destruir_lista(ListaCircular *l);
int tem_ciclo(ListaCircular *l);

int main(void) {
    int num, v;

    // Lê a quantidade de valores
    scanf("%d", &num);

    // Cria a lista circular vazia
    ListaCircular *l = (ListaCircular *)malloc(sizeof(ListaCircular));
    if (l == NULL) return 1;
    l->cabeca = NULL;
    l->cauda = NULL;
    l->tamanho = 0;

    // Lê N valores e insere no final
    for (int i = 0; i < num; i++) {
        scanf("%d", &v);
        inserir_fim(l, v);
    }

    imprimir(l);

    // Estado 1: lista circular (tem ciclo)
    if (tem_ciclo(l))
        printf("Ciclo detectado\n");
    else
        printf("Sem ciclo\n");

    // Quebra o ciclo: cauda->prox = NULL
    if (l->cauda != NULL)
        l->cauda->prox = NULL;

    // Estado 2: lista linear (sem ciclo)
    if (tem_ciclo(l))
        printf("Ciclo detectado\n");
    else
        printf("Sem ciclo\n");

    // Restaura o anel para a destruição funcionar
    if (l->cauda != NULL)
        l->cauda->prox = l->cabeca;

    destruir_lista(l);
    free(l);

    return 0;
}

// Aloca um nó com valor, prox e ant = NULL
NoDuplo *noDuplo_criar(int valor) {
    NoDuplo *novo = (NoDuplo *)malloc(sizeof(NoDuplo));
    if (novo == NULL) return NULL;

    novo->valor = valor;
    novo->prox = NULL;
    novo->ant = NULL;

    return novo;
}

// Insere no INÍCIO da lista circular dupla
void inserir_inicio(ListaCircular *l, int valor) {
    NoDuplo *novo = noDuplo_criar(valor);
    if (novo == NULL) return;

    if (l->cabeca == NULL) {
        novo->prox = novo;
        novo->ant = novo;
        l->cabeca = novo;
        l->cauda = novo;
    } else {
        novo->prox = l->cabeca;
        novo->ant = l->cauda;
        l->cabeca->ant = novo;
        l->cauda->prox = novo;
        l->cabeca = novo;
    }

    l->tamanho++;
}

// Insere no FINAL da lista circular dupla em O(1)
void inserir_fim(ListaCircular *l, int valor) {
    NoDuplo *novo = noDuplo_criar(valor);
    if (novo == NULL) return;

    if (l->cabeca == NULL) {
        novo->prox = novo;
        novo->ant = novo;
        l->cabeca = novo;
        l->cauda = novo;
    } else {
        l->cauda->prox = novo;
        novo->prox = l->cabeca;
        novo->ant = l->cauda;
        l->cabeca->ant = novo;
        l->cauda = novo;
    }

    l->tamanho++;
}

// Imprime uma volta completa da lista circular, começando pela cabeca
void imprimir(ListaCircular *l) {
    if (l == NULL || l->cabeca == NULL) {
        printf("LISTA VAZIA\n");
        return;
    }

    NoDuplo *atual = l->cabeca;

    printf("[");
    for (int i = 0; i < l->tamanho; i++) {
        printf("%d", atual->valor);
        if (i < l->tamanho - 1)
            printf(",");
        atual = atual->prox;
    }
    printf("]\n");
}

// Libera todos os nós da lista circular dupla
void destruir_lista(ListaCircular *l) {
    if (l == NULL || l->cabeca == NULL) return;

    NoDuplo *atual = l->cabeca;
    NoDuplo *proximo;

    do {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    } while (atual != l->cabeca);

    l->cabeca = NULL;
    l->cauda = NULL;
    l->tamanho = 0;
}

// Detecta se a lista tem ciclo usando o algoritmo de Floyd.
//
// Dois ponteiros: slow anda 1, fast anda 2.
// Se houver ciclo, fast alcança slow (slow == fast).
// Se não houver, fast chega ao NULL e o loop termina.
//
// Casos:
//   - lista vazia ou com 1 nó: não tem ciclo (fast já é NULL ou prox é NULL)
//   - lista circular: fast dá voltas e uma hora encontra slow -> 1
//   - lista linear: fast chega ao fim -> 0
int tem_ciclo(ListaCircular *l) {
    if (l == NULL || l->cabeca == NULL) return 0;

    NoDuplo *slow = l->cabeca;
    NoDuplo *fast = l->cabeca;

    while (fast != NULL && fast->prox != NULL) {
        slow = slow->prox;
        fast = fast->prox->prox;
        if (slow == fast) return 1;
    }

    return 0;
}