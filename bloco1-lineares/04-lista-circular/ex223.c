// 223 — Concatenação Circular O(1) com Ajuste de Fim
// Lista circular dupla de inteiros com cabeca, cauda e tamanho.
// Implementa concatenar_circular(ListaCircular*, ListaCircular*) que
// anexa l2 ao final de l1 em O(1), religando os ponteiros do anel.
// Após a operação, l2 fica vazia e l1 contém os nós das duas listas.
// O main lê duas listas, concatena e imprime a lista resultante.
// Depois concatena uma lista vazia com a resultante (deve ser no-op)
// e imprime de novo.
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

    // Lê a primeira lista
    scanf("%d", &num);

    ListaCircular *l = (ListaCircular *)malloc(sizeof(ListaCircular));
    if (l == NULL) return 1;
    l->cabeca = NULL;
    l->cauda = NULL;
    l->tamanho = 0;

    for (int i = 0; i < num; i++) {
        scanf("%d", &v);
        inserir_ordenado(l, v);
    }

    // Lê a segunda lista
    scanf("%d", &num);

    ListaCircular *l2 = (ListaCircular *)malloc(sizeof(ListaCircular));
    if (l2 == NULL) return 1;
    l2->cabeca = NULL;
    l2->cauda = NULL;
    l2->tamanho = 0;

    for (int i = 0; i < num; i++) {
        scanf("%d", &v);
        inserir_ordenado(l2, v);
    }

    // Estado inicial das duas listas
    imprimir(l);
    imprimir(l2);

    // Concatena l2 ao final de l (O(1)); l2 fica vazia
    concatenar_circular(l, l2);

    // Lista resultante e confirmação de que l2 ficou vazia
    imprimir(l);
    imprimir(l2);

    // Concatena uma lista vazia com a resultante (deve ser no-op)
    ListaCircular *vazia = (ListaCircular *)malloc(sizeof(ListaCircular));
    if (vazia == NULL) return 1;
    vazia->cabeca = NULL;
    vazia->cauda = NULL;
    vazia->tamanho = 0;

    concatenar_circular(l, vazia);
    imprimir(l);

    free(vazia);
    free(l2);
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

    // Se chegou ao último nó, insere no final
    if (atual->prox == l->cabeca) {
        inserir_fim(l, valor);
        return 1;
    }

    NoDuplo *novo = noDuplo_criar(valor);
    if (novo == NULL) return 0;

    NoDuplo *proximo = atual->prox;

    // Ajusta os 4 ponteiros do meio
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
//
// Casos:
//   - l2 vazia: nada a fazer.
//   - l vazia: absorve l2 inteira (copia cabeca e cauda, religa o anel).
//   - Ambas não vazias: o antigo cauda->prox de l aponta para a cabeca
//     de l2; o ant->ant da cabeca de l2 aponta para a cauda de l; a cauda
//     de l passa a ser a cauda de l2; e o anel é fechado com
//     cauda->prox = cabeca e cabeca->ant = cauda.
//
// Depois de concatenar, l2 fica vazia (cabeca = cauda = NULL) para
// evitar dangling pointers e double free. O campo 'tamanho' é somado.
//
// Não percorre nenhuma lista: só ajusta ponteiros -> O(1).
void concatenar_circular(ListaCircular *l, ListaCircular *l2) {
    if (l == NULL || l2 == NULL) return;
    if (l2->cabeca == NULL) return;   // l2 vazia: nada a concatenar

    if (l->cabeca == NULL) {
        // l vazia: absorve l2 inteira
        l->cabeca = l2->cabeca;
        l->cauda = l2->cauda;
        l->cabeca->ant = l->cauda;
        l->cauda->prox = l->cabeca;
    } else {
        // l não vazia: religa as duas listas
        l->cauda->prox = l2->cabeca;
        l2->cabeca->ant = l->cauda;
        l->cauda = l2->cauda;
        l->cauda->prox = l->cabeca;
        l->cabeca->ant = l->cauda;
    }

    // Soma o tamanho e zera l2 (os nós agora pertencem a l)
    l->tamanho += l2->tamanho;
    l2->cabeca = NULL;
    l2->cauda = NULL;
    l2->tamanho = 0;
}