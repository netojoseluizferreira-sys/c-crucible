// 216 — O Anel Primordial (Criação e Inserção no Início)
// Lista circular dupla de inteiros com cabeca, cauda e tamanho.
// Implementa inserir_inicio(ListaCircular*, int).
// Se a lista está vazia, o novo nó é o único e aponta para si mesmo
// nos dois sentidos (prox e ant).
// Senão, o novo vira a cabeca: ele aponta para a antiga cabeca e para
// a cauda, a antiga cabeca aponta para trás para o novo, e a cauda
// aponta para frente para o novo (fechando o anel).
// O main lê N inteiros, insere no início, imprime uma volta completa
// e destrói a lista.
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
void imprimir(ListaCircular *l);
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

    // Lê N valores e insere no início
    for (int i = 0; i < num; i++) {
        scanf("%d", &v);
        inserir_inicio(l, v);
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

// Insere no INÍCIO da lista circular dupla.
//
// Casos:
//   - Lista vazia: novo é o único nó; prox e ant apontam para ele mesmo.
//     cabeca = cauda = novo.
//   - Lista com 1+ nós: o novo vira cabeca.
//     novo->prox = antiga cabeca
//     novo->ant  = cauda (porque é circular)
//     antiga cabeca->ant = novo
//     cauda->prox = novo (fecha o anel)
//     cabeca = novo
void inserir_inicio(ListaCircular *l, int valor) {
    NoDuplo *novo = noDuplo_criar(valor);
    if (novo == NULL) return;

    if (l->cabeca == NULL) {
        // Lista vazia: novo é o único nó, aponta para si mesmo nos dois sentidos
        novo->prox = novo;
        novo->ant = novo;
        l->cabeca = novo;
        l->cauda = novo;
    } else {
        // Lista com nós: novo vira cabeca
        novo->prox = l->cabeca;       // novo aponta para a antiga cabeca
        novo->ant = l->cauda;         // novo aponta para trás, para a cauda
        l->cabeca->ant = novo;        // antiga cabeca olha para trás, para o novo
        l->cauda->prox = novo;        // cauda aponta para frente, para o novo (fecha o anel)
        l->cabeca = novo;             // cabeca passa a ser o novo
    }

    l->tamanho++;
}

// Imprime uma volta completa da lista circular dupla.
// Usa o contador 'tamanho' para parar com segurança, sem depender
// de comparar ponteiro (evita loop infinito se a lista estiver
// mal formada ou se alguém mexer na condição).
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
// Guarda o proximo antes do free e para quando volta à cabeca.
void destruir_lista(ListaCircular *l) {
    if (l == NULL || l->cabeca == NULL) return;

    NoDuplo *atual = l->cabeca;
    NoDuplo *proximo;

    do {
        proximo = atual->prox;   // guarda antes de liberar
        free(atual);
        atual = proximo;
    } while (atual != l->cabeca);

    l->cabeca = NULL;
    l->cauda = NULL;
    l->tamanho = 0;
}