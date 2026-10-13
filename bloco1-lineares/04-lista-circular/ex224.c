// 224 — Destruição Segura com Verificação de Integridade
// Lista circular dupla de inteiros com cabeca, cauda e tamanho.
// Implementa destruir_circular(ListaCircular*) que libera todos os nós
// e zera cabeca/cauda/tamanho. Funciona para lista vazia, unitária e
// com vários nós. Usa o contador 'tamanho' para não entrar em loop
// infinito caso a lista esteja mal formada.
// O main monta uma lista, destrói e imprime o estado dos ponteiros.
// Depois cria uma lista unitária, destrói e imprime de novo.
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
int inserir_posicao(ListaCircular *l, int valor, int pos);
void inserir_ordenado(ListaCircular *l, int valor);
void concatenar_circular(ListaCircular *l, ListaCircular *l2);

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

    // Destrói e mostra o estado dos ponteiros
    destruir_lista(l);
    printf("Lista destruida\n");
    if (l->cabeca == NULL)
        printf("inicio: (nil)\n");
    else
        printf("inicio: %d\n", l->cabeca->valor);
    if (l->cauda == NULL)
        printf("fim: (nil)\n");
    else
        printf("fim: %d\n", l->cauda->valor);

    // Cria uma lista unitária e destrói de novo
    inserir_fim(l, 42);
    printf("Lista unitaria: ");
    imprimir(l);
    destruir_lista(l);
    printf("Lista unitaria destruida\n");
    if (l->cabeca == NULL)
        printf("inicio: (nil)\n");
    else
        printf("inicio: %d\n", l->cabeca->valor);
    if (l->cauda == NULL)
        printf("fim: (nil)\n");
    else
        printf("fim: %d\n", l->cauda->valor);

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

// Libera todos os nós da lista circular dupla.
//
// Estratégia:
//   - Se a lista estiver vazia, não faz nada.
//   - Guarda o tamanho original em 'n' e percorre exatamente n vezes
//     a partir da cabeca, guardando o proximo antes de liberar.
//     Usar o contador evita loop infinito se a lista estiver
//     mal formada (prox não voltando à cabeca).
//   - Ao final, zera cabeca, cauda e tamanho.
//
// Cuidado com lista unitária: o nó aponta para si mesmo (prox = ant = ele).
// O primeiro free libera o nó; o contador garante que o loop termine.
void destruir_lista(ListaCircular *l) {
    if (l == NULL || l->cabeca == NULL) return;

    int n = l->tamanho;
    NoDuplo *atual = l->cabeca;
    NoDuplo *proximo;

    for (int i = 0; i < n; i++) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

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
void josephus(Cursor *c, int k) {
    if (c == NULL || c->lista == NULL || c->lista->cabeca == NULL) return;

    int tam = c->lista->tamanho - 1;
    int removidos[tam > 0 ? tam : 1];
    int i = 0;
    int sobrevivente = -1;

    while (c->lista->cabeca != c->lista->cauda) {
        for (int j = 0; j < k - 1; j++) {
            cursor_avancar(&c);
        }

        cursor_remover(&c, removidos + i);
        i++;
    }

    if (c->lista->cabeca != NULL)
        sobrevivente = c->lista->cabeca->valor;

    printf("Removidos: ");
    for (int j = 0; j < i; j++) {
        printf("%d ", removidos[j]);
    }

    printf("\nSobrevivente: %d\n", sobrevivente);
}

// Insere em posição específica da lista circular dupla (1 = ok, 0 = inválida).
int inserir_posicao(ListaCircular *l, int valor, int pos) {
    if (pos < 0) return 0;

    if (l->cabeca == NULL || pos == 0) {
        inserir_inicio(l, valor);
        return 1;
    }

    NoDuplo *atual = l->cabeca;
    int i = 0;

    while (i < pos - 1 && atual->prox != l->cabeca) {
        atual = atual->prox;
        i++;
    }

    if (atual->prox == l->cabeca) {
        inserir_fim(l, valor);
        return 1;
    }

    NoDuplo *novo = noDuplo_criar(valor);
    if (novo == NULL) return 0;

    NoDuplo *proximo = atual->prox;

    novo->ant = atual;
    novo->prox = proximo;
    atual->prox = novo;
    proximo->ant = novo;

    l->tamanho++;
    return 1;
}

// Insere valor mantendo a ordem crescente na lista circular dupla.
void inserir_ordenado(ListaCircular *l, int valor) {
    if (l == NULL) return;
    if (l->cabeca == NULL) {
        inserir_inicio(l, valor);
        return;
    }

    Cursor c;
    c.lista = l;
    c.atual = l->cabeca;

    int i = 0;

    while (c.atual->valor < valor && c.atual->prox != l->cabeca) {
        c.atual = c.atual->prox;
        i++;
    }

    if (c.atual->valor < valor && c.atual->prox == l->cabeca) {
        inserir_fim(l, valor);
    } else {
        inserir_posicao(l, valor, i);
    }
}

// Concatena l2 ao final de l em O(1), religando os ponteiros do anel.
void concatenar_circular(ListaCircular *l, ListaCircular *l2) {
    if (l == NULL || l2 == NULL) return;
    if (l2->cabeca == NULL) return;

    if (l->cabeca == NULL) {
        l->cabeca = l2->cabeca;
        l->cauda = l2->cauda;
        l->cabeca->ant = l->cauda;
        l->cauda->prox = l->cabeca;
    } else {
        l->cauda->prox = l2->cabeca;
        l2->cabeca->ant = l->cauda;
        l->cauda = l2->cauda;
        l->cauda->prox = l->cabeca;
        l->cabeca->ant = l->cauda;
    }

    l->tamanho += l2->tamanho;
    l2->cabeca = NULL;
    l2->cauda = NULL;
    l2->tamanho = 0;
}