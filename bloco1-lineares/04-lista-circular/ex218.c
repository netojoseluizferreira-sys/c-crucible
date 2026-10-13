// 218 — Percurso Seguro e Contagem sem Loop Infinito
// Lista circular dupla de inteiros com cabeca, cauda e tamanho.
// Implementa contar_circular(ListaCircular*) que retorna o número
// de nós percorrendo a lista circular até voltar à cabeca.
// O main lê N, monta a lista no final, mostra a contagem e a lista.
// Depois destrói a lista e mostra a contagem novamente (deve ser 0).
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
void imprimir_do_fim(ListaCircular *l);
void destruir_lista(ListaCircular *l);
int contar_circular(ListaCircular *l);

int main(void) {
    int num, v, total;

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

    // Contagem antes de destruir
    total = contar_circular(l);
    if (total == -1)
        printf("Erro na contagem\n");
    else
        printf("total: %d\n", total);

    // Lista formatada
    imprimir(l);

    // Destrói tudo
    destruir_lista(l);

    // Contagem depois de destruir: deve ser 0
    total = contar_circular(l);
    if (total == -1)
        printf("Erro na contagem\n");
    else
        printf("total: %d\n", total);

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

// Imprime uma volta completa da lista circular, começando pela cauda
void imprimir_do_fim(ListaCircular *l) {
    if (l == NULL || l->cauda == NULL) {
        printf("LISTA VAZIA\n");
        return;
    }

    NoDuplo *atual = l->cauda;

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

// Conta os nós da lista circular percorrendo uma volta completa.
//
// Estratégia:
//   - Se a lista estiver vazia (cabeca == NULL), retorna 0.
//   - Senão, percorre com while a partir da cabeca, contando cada
//     nó, até voltar à cabeca. Para quando atual == cabeca novamente.
//   - Ao final, compara com o campo 'tamanho' para detectar
//     inconsistência: se a contagem bateu, retorna o total;
//     se não, retorna -1.
//
// A condição de parada do while é essencial (atual != cabeca) impede loop infinito.
int contar_circular(ListaCircular *l) {
    if (l == NULL || l->cabeca == NULL) return 0;

    int i = 1;
    NoDuplo *atual = l->cabeca;

    while (atual->prox != l->cabeca) {
        i++;
        atual = atual->prox;
    }

    if (i == l->tamanho) return i;
    else return -1;
}