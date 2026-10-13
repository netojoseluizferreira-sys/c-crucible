// 222 — Inserção Ordenada em Lista Circular
// Lista circular dupla de inteiros com cabeca, cauda e tamanho.
// Implementa inserir_ordenado(ListaCircular*, int) que mantém a lista
// em ordem crescente, tratando lista vazia, inserção no início, meio
// e fim. O main lê N inteiros, insere cada um de forma ordenada e
// imprime a lista resultante.
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

int main(void) {
    int num, v;
    scanf("%d", &num);

    // Cria a lista circular vazia
    ListaCircular *l = (ListaCircular *)malloc(sizeof(ListaCircular));
    if (l == NULL) return 1;
    l->cabeca = NULL;
    l->cauda = NULL;
    l->tamanho = 0;

    // Lê N valores e insere em ordem crescente
    for (int i = 0; i < num; i++) {
        scanf("%d", &v);
        inserir_ordenado(l, v);
    }

    imprimir(l);

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
//
// Casos:
//   - Lista vazia: insere como único nó (inserir_inicio trata).
//   - Novo menor que a cabeca: insere no início (pos = 0).
//   - Novo no meio: percorre até achar o primeiro nó com valor >= novo,
//     e insere antes dele.
//   - Novo maior que todos: percorre a volta inteira e insere no final.
//
// Estratégia com cursor local:
//   - cursor_inicio: c.atual = l->cabeca
//   - avança enquanto c.atual->valor < valor E não deu a volta
//   - se c.atual é o último e ainda é menor que o novo, insere no final
//   - senão, insere na posição i (contada do início)
void inserir_ordenado(ListaCircular *l, int valor) {
    if (l == NULL) return;
    if (l->cabeca == NULL) {
        inserir_inicio(l, valor);
        return;
    }

    // Cursor local só para percorrer; não precisa alocar com malloc
    Cursor c;
    c.lista = l;
    c.atual = l->cabeca;

    int i = 0;

    // Avança enquanto o valor do nó atual for menor que o novo.
    // Quando parar, 'i' é a posição onde o novo deve ser inserido.
    while (c.atual->valor < valor && c.atual->prox != l->cabeca) {
        c.atual = c.atual->prox;
        i++;
    }

    // Se o nó atual é o último e ainda é menor que o novo, insere no final
    if (c.atual->valor < valor && c.atual->prox == l->cabeca) {
        inserir_fim(l, valor);
    } else {
        // Senão, insere antes do nó atual (na posição i)
        inserir_posicao(l, valor, i);
    }
}