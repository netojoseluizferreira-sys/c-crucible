// 200 — Inserção em Posição com Quatro Ponteiros
// Insere um nó em uma posição específica da lista dupla.
// Ajusta QUATRO ponteiros: prox e ant do novo nó, prox do anterior
// e ant do próximo. Retorna 1 se inseriu, 0 se posição inválida.
#include <stdio.h>
#include <stdlib.h>

// Nó da lista dupla: valor + ponteiro para o próximo e para o anterior
typedef struct NoDuplo {
    int valor;
    struct NoDuplo *prox;
    struct NoDuplo *ant;
} NoDuplo;

// Lista dupla: guarda o primeiro e o último nó.
typedef struct ListaDupla {
    NoDuplo *cabeca;
    NoDuplo *cauda;
} ListaDupla;

// Protótipos
NoDuplo *noDuplo_criar(int valor);
void inserir_inicio(ListaDupla *l, int valor);
void inserir_final(ListaDupla *l, int valor);
int  inserir_posicao(ListaDupla *l, int valor, int pos);
void imprimir_frente(ListaDupla *l);
void destruir_lista(ListaDupla *l);

int main(void) {
    int num, v, x, pos;

    // Lê a quantidade de valores que vão compor a lista
    scanf("%d", &num);

    // Cria a lista vazia
    ListaDupla *l = (ListaDupla *)malloc(sizeof(ListaDupla));
    if (l == NULL) return 1;
    l->cabeca = NULL;
    l->cauda = NULL;

    // Lê N valores e insere no final, um a um
    for (int i = 0; i < num; i++) {
        scanf("%d", &v);
        inserir_final(l, v);
    }

    // Lê o valor a inserir (X) e a posição (P)
    scanf("%d %d", &x, &pos);

    // Tenta inserir e imprime o retorno (1 = sucesso, 0 = inválido)
    int resultado = inserir_posicao(l, x, pos);
    printf("%d\n", resultado);

    // Imprime a lista final para verificar o resultado
    imprimir_frente(l);

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

// Insere no INÍCIO em O(1)
// Lista vazia: novo é cabeca e cauda
// Lista não vazia: novo vira cabeca, antigo primeiro aponta para trás
void inserir_inicio(ListaDupla *l, int valor) {
    NoDuplo *novo = noDuplo_criar(valor);
    if (novo == NULL) return;

    // Novo é o primeiro: ninguém antes dele
    novo->ant = NULL;

    // Novo aponta para o antigo primeiro (NULL se lista vazia)
    novo->prox = l->cabeca;

    if (l->cabeca == NULL) {
        // Lista vazia: novo é o único nó
        l->cabeca = novo;
        l->cauda = novo;
    } else {
        // A ordem importa: usa l->cabeca antes de sobrescrever
        l->cabeca->ant = novo;
        l->cabeca = novo;
    }
}

// Insere no FINAL em O(1)
// Lista vazia: novo é cabeca e cauda
// Lista não vazia: novo vira cauda, antigo último aponta para frente
void inserir_final(ListaDupla *l, int valor) {
    NoDuplo *novo = noDuplo_criar(valor);
    if (novo == NULL) return;

    // Novo é o último: ninguém depois dele
    novo->prox = NULL;

    // Novo aponta para trás, para o antigo último (NULL se lista vazia)
    novo->ant = l->cauda;

    if (l->cauda == NULL) {
        // Lista vazia: novo é o único nó
        l->cabeca = novo;
        l->cauda = novo;
    } else {
        // A ordem importa: usa l->cauda antes de sobrescrever
        l->cauda->prox = novo;
        l->cauda = novo;
    }
}

// Insere em uma posição específica da lista dupla.
// Retorna 1 se inseriu, 0 se posição inválida.
//
// Casos:
//   - Lista vazia OU posição <= 0: insere no INÍCIO
//   - Posição >= tamanho da lista: insere no FINAL
//   - Caso contrário: percorre até a posição anterior e ajusta 4 ponteiros
//
// Os 4 ponteiros que precisam ser ajustados ao inserir no MEIO:
//   - novo->ant = atual       (novo aponta para trás)
//   - novo->prox = proximo    (novo aponta para frente)
//   - atual->prox = novo      (anterior aponta para frente, para o novo)
//   - proximo->ant = novo     (próximo aponta para trás, para o novo)
int inserir_posicao(ListaDupla *l, int valor, int pos) {
    // Caso 1: posição negativa não faz sentido
    if (pos < 0) return 0;

    // Caso 2: lista vazia ou posição 0 → insere no início
    if (l->cabeca == NULL || pos == 0) {
        inserir_inicio(l, valor);
        return 1;
    }

    // Caso 3: percorre até o nó ANTERIOR à posição
    // Para inserir na posição P, precisamos parar no nó da posição P-1.
    // O loop avança enquanto não chegou em P-1 E ainda tem próximo.
    NoDuplo *atual = l->cabeca;
    int i = 0;

    while (i < pos - 1 && atual->prox != NULL) {
        atual = atual->prox;
        i++;
    }

    // Caso 4: chegou ao último antes de atingir a posição → insere no final
    if (atual->prox == NULL) {
        inserir_final(l, valor);
        return 1;
    }

    // Caso 5: inserir no MEIO (entre atual e atual->prox)
    NoDuplo *novo = noDuplo_criar(valor);
    if (novo == NULL) return 0;

    NoDuplo *proximo = atual->prox;  // guarda o próximo antes de mexer

    // Ajusta os 4 ponteiros
    novo->ant = atual;       // 1) novo olha para trás
    novo->prox = proximo;    // 2) novo olha para frente
    atual->prox = novo;      // 3) anterior olha para frente (para o novo)
    proximo->ant = novo;     // 4) próximo olha para trás (para o novo)

    return 1;
}

// Imprime a lista do INÍCIO ao FIM, seguindo o ponteiro 'prox'.
void imprimir_frente(ListaDupla *l) {
    NoDuplo *atual = l->cabeca;
    if (atual == NULL) {
        printf("LISTA VAZIA\n");
        return;
    }
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->prox;
    }
    printf("NULL\n");
}

// Libera todos os nós da lista e reseta cabeca/cauda.
// Guarda o proximo antes do free para não perder a referência.
void destruir_lista(ListaDupla *l) {
    NoDuplo *atual = l->cabeca;

    while (atual != NULL) {
        NoDuplo *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    l->cabeca = NULL;
    l->cauda = NULL;
}