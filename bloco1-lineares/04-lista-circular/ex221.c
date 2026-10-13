// 221 — Josephus com Lista Circular e Passo Variável
// Lista circular dupla de inteiros com cabeca, cauda e tamanho.
// Implementa josephus(Cursor*, int k) que simula a eliminação
// a cada k passos, imprimindo os eliminados e o sobrevivente.
// O main lê N, monta a lista circular 1..N, lê k e chama josephus.
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

// Cursor: aponta para a lista e para o nó atual
typedef struct Cursor{
    ListaCircular *lista;
    NoDuplo *atual;
} Cursor;

// Protótipos
NoDuplo *noDuplo_criar(int valor);
void inserir_inicio(ListaCircular *l, int valor);
void inserir_fim(ListaCircular *l, int valor);
void imprimir(ListaCircular *l);
void destruir_lista(ListaCircular *l);
void cursor_avancar(Cursor **c);
int cursor_remover(Cursor **c, int *v);
void josephus(Cursor *c, int k);

int main(void) {
    int num, k;

    // Lê N (quantidade de pessoas) e k (passo)
    scanf("%d", &num);
    scanf("%d", &k);

    // Cria a lista circular vazia
    ListaCircular *l = (ListaCircular *)malloc(sizeof(ListaCircular));
    if (l == NULL) return 1;
    l->cabeca = NULL;
    l->cauda = NULL;
    l->tamanho = 0;

    // Monta a lista circular 1..N inserindo no final
    for (int i = 1; i <= num; i++) {
        inserir_fim(l, i);
    }

    // Cursor apontando para a cabeca (pessoa 1)
    Cursor c;
    c.lista = l;
    c.atual = l->cabeca;

    // Simula Josephus
    josephus(&c, k);

    // Libera o que sobrou (a lista fica com 1 nó)
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

// Avança o cursor um nó. Se já estiver no fim, dá a volta (circular)
void cursor_avancar(Cursor **c) {
    if (c == NULL || *c == NULL) return;
    if ((*c)->atual == NULL) return;
    (*c)->atual = (*c)->atual->prox;
}

// Remove o nó do cursor e reposiciona. Mesmo estilo do pop: 1/0 + saída.
//
// Para lista circular dupla:
//   - Se o alvo é o único nó: cabeca = cauda = NULL, atual = NULL.
//   - Senão: religa ant->prox = prox e prox->ant = ant, ajustando
//     cabeca/cauda se o alvo for uma das pontas.
//   - O cursor passa a apontar para o PRÓXIMO nó do removido
//     (conveniente para Josephus).
int cursor_remover(Cursor **c, int *v) {
    if (c == NULL || *c == NULL) return 0;
    if ((*c)->lista == NULL || (*c)->lista->cabeca == NULL) return 0;
    if ((*c)->atual == NULL) return 0;

    NoDuplo *alvo = (*c)->atual;
    ListaCircular *l = (*c)->lista;

    if (v != NULL) *v = alvo->valor;

    if (alvo == alvo->prox) {
        // Único nó
        l->cabeca = NULL;
        l->cauda = NULL;
        (*c)->atual = NULL;
    } else {
        alvo->ant->prox = alvo->prox;
        alvo->prox->ant = alvo->ant;

        if (alvo == l->cabeca) l->cabeca = alvo->prox;
        if (alvo == l->cauda) l->cauda = alvo->ant;

        (*c)->atual = alvo->prox;   // cursor vai para o próximo
    }

    free(alvo);
    l->tamanho--;
    return 1;
}

// Simula Josephus: elimina a cada k passos até sobrar 1.
//
// Estratégia:
//   - Enquanto houver mais de 1 nó:
//       * avança k-1 vezes (o k-ésimo é o eliminado)
//         Obs.: como o cursor já está no nó atual, avançar k-1 vezes
//         faz o cursor parar no k-ésimo nó contando a partir do atual.
//       * remove o nó do cursor (a função já move o cursor para o próximo)
//       * guarda o valor removido no vetor de removidos
//   - Ao final, o nó que sobrou é o sobrevivente.
//
// O vetor de removidos é alocado na stack com tamanho (N-1).
void josephus(Cursor *c, int k) {
    if (c == NULL || c->lista == NULL || c->lista->cabeca == NULL) return;

    int tam = c->lista->tamanho - 1;
    int removidos[tam > 0 ? tam : 1];
    int i = 0;
    int sobrevivente = -1;

    while (c->lista->cabeca != c->lista->cauda) {
        // Avança k-1 passos: o cursor para no k-ésimo nó
        for (int j = 0; j < k - 1; j++) {
            cursor_avancar(&c);
        }

        // Remove o nó atual
        cursor_remover(&c, removidos + i);
        i++;
    }

    // Sobrou 1 nó
    if (c->lista->cabeca != NULL)
        sobrevivente = c->lista->cabeca->valor;

    printf("Removidos: ");
    for (int j = 0; j < i; j++) {
        printf("%d ", removidos[j]);
    }

    printf("\nSobrevivente: %d\n", sobrevivente);
}