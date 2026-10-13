// 217 — Inserção no Final com O(1) e Fim Correto
// Lista circular dupla de inteiros com cabeca, cauda e tamanho.
// Implementa inserir_fim(ListaCircular*, int) em O(1).
// O main lê N inteiros, insere no final, imprime a lista na ordem
// direta (do inicio ao fim) e depois a partir do fim (uma volta
// começando pela cauda), demonstrando a circularidade.
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

int main(void) {
    int num, v;
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

    // Ordem direta: do inicio ao fim
    imprimir(l);

    // Ordem circular a partir do fim: começa na cauda, dá uma volta
    imprimir_do_fim(l);

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

// Insere no FINAL da lista circular dupla em O(1).
//
// Casos:
//   - Lista vazia: novo é o único nó; prox e ant apontam para ele mesmo.
//     cabeca = cauda = novo.
//   - Lista com 1+ nós: o novo vira cauda.
//     cauda->prox = novo          (antiga cauda aponta para o novo)
//     novo->prox  = cabeca        (novo aponta para a cabeca, fechando o anel)
//     novo->ant   = cauda         (novo aponta para trás, para a antiga cauda)
//     cabeca->ant = novo          (cabeca olha para trás, para o novo)
//     cauda = novo
//
// Só mexe em ponteiros já existentes (cabeca, cauda), sem percorrer
// a lista -> O(1).
void inserir_fim(ListaCircular *l, int valor) {
    NoDuplo *novo = noDuplo_criar(valor);
    if (novo == NULL) return;

    if (l->cabeca == NULL) {
        // Lista vazia: novo é o único nó, aponta para si mesmo nos dois sentidos
        novo->prox = novo;
        novo->ant = novo;
        l->cabeca = novo;
        l->cauda = novo;
    } else {
        // Lista com nós: novo vira cauda
        l->cauda->prox = novo;        // antiga cauda aponta para o novo
        novo->prox = l->cabeca;       // novo aponta para a cabeca (fecha o anel)
        novo->ant = l->cauda;         // novo aponta para trás, para a antiga cauda
        l->cabeca->ant = novo;        // cabeca olha para trás, para o novo
        l->cauda = novo;              // cauda passa a ser o novo
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

// Imprime uma volta completa da lista circular, começando pela cauda.
// O contador 'tamanho' garante que para depois de uma volta,
// sem depender de comparar ponteiro (evita loop infinito).
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