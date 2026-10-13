// 219 — Remoção do Início com Retorno e Atualização de Fim
// Lista circular dupla de inteiros com cabeca, cauda e tamanho.
// Implementa remover_inicio(ListaCircular*, int*) que remove o nó
// apontado pela cabeca e devolve o valor removido via ponteiro.
// Retorna 1 em sucesso, 0 se a lista estiver vazia.
// O main lê N, monta a lista no final, remove tudo do início,
// empilhando os valores removidos, e mostra a pilha de removidos
// e o estado final dos ponteiros.
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

// Nó da pilha auxiliar (lista simples)
typedef struct No {
    int valor;
    struct No *prox;
} No;

// Protótipos
NoDuplo *noDuplo_criar(int valor);
void inserir_inicio(ListaCircular *l, int valor);
void inserir_fim(ListaCircular *l, int valor);
void imprimir(ListaCircular *l);
void destruir_lista(ListaCircular *l);
int remover_inicio(ListaCircular *l, int *v);
No *no_criar(int valor);
void push(No **topo, int valor);
int pop(No **topo, int *valor);
void imprimir_pilha(No *topo);
void destruir_pilha(No **topo);

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

    // Pilha auxiliar de removidos
    No *topo = NULL;

    // Lê N valores e insere no final
    for (int i = 0; i < num; i++) {
        scanf("%d", &v);
        inserir_fim(l, v);
    }

    // Estado inicial
    imprimir(l);

    // Remove do início até esvaziar, empilhando os removidos
    while (remover_inicio(l, &v)) {
        push(&topo, v);
    }

    // Pilha de removidos (do último removido para o primeiro)
    printf("Removidos: ");
    imprimir_pilha(topo);

    // Lista deve estar vazia
    imprimir(l);

    // Estado final dos ponteiros
    if (l->cabeca == NULL)
        printf("inicio: (nil)\n");
    else
        printf("inicio: %d\n", l->cabeca->valor);

    if (l->cauda == NULL)
        printf("fim: (nil)\n");
    else
        printf("fim: %d\n", l->cauda->valor);

    free(l);
    destruir_pilha(&topo);

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

// Remove o nó do INÍCIO da lista circular dupla.
//
// Devolve 1 em sucesso (com *v preenchido) e 0 se a lista estiver vazia.
// Mesmo estilo do pop: usar variável de saída em vez de valor mágico,
// porque -1 poderia ser um valor válido na lista.
//
// Casos:
//   - Lista vazia: retorna 0.
//   - Lista com 1 nó: o único nó é removido; cabeca = cauda = NULL.
//   - Lista com 2+ nós: o segundo nó vira cabeca; a cauda continua
//     sendo a mesma, mas precisa religar:
//       nova cabeca->ant = cauda
//       cauda->prox = nova cabeca  (fecha o anel)
int remover_inicio(ListaCircular *l, int *v) {
    if (l == NULL || l->cabeca == NULL) return 0;

    NoDuplo *remover = l->cabeca;

    if (remover == l->cauda) {
        // Único nó: a lista fica vazia
        l->cabeca = NULL;
        l->cauda = NULL;
    } else {
        // Mais de um nó: o segundo vira cabeca
        l->cabeca = remover->prox;
        l->cabeca->ant = l->cauda;   // nova cabeca olha para trás, para a cauda
        l->cauda->prox = l->cabeca;  // cauda aponta para frente, para a nova cabeca (fecha o anel)
    }

    if (v != NULL) *v = remover->valor;
    free(remover);
    l->tamanho--;
    return 1;
}

// Cria um nó da pilha auxiliar
No *no_criar(int valor) {
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL) return NULL;

    novo->valor = valor;
    novo->prox = NULL;

    return novo;
}

// Empilha: insere um novo nó no TOPO da pilha
void push(No **topo, int valor) {
    No *novo = no_criar(valor);
    if (novo == NULL) return;

    novo->prox = *topo;   // novo aponta para o antigo topo
    *topo = novo;         // topo passa a ser o novo nó
}

// Desempilha: remove o nó do TOPO e devolve seu valor via ponteiro
// Retorna 1 se sucesso, 0 se a pilha está vazia
int pop(No **topo, int *valor) {
    if (topo == NULL || *topo == NULL) return 0;

    No *atual = *topo;
    *valor = atual->valor;
    *topo = atual->prox;
    free(atual);

    return 1;
}

// Imprime a pilha do topo até a base
void imprimir_pilha(No *topo) {
    No *atual = topo;
    if (atual == NULL) {
        printf("PILHA VAZIA\n");
        return;
    }
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->prox;
    }
    printf("NULL\n");
}

// Libera todos os nós da pilha e seta *topo para NULL
void destruir_pilha(No **topo) {
    if (topo == NULL || *topo == NULL) return;

    No *atual = *topo;
    while (atual != NULL) {
        No *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    *topo = NULL;
}