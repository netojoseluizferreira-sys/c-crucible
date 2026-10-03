// 171 — Buscar um Valor
// Percorre a lista comparando cada valor com o alvo.
// Retorna o índice da primeira ocorrência ou -1 se não encontrar.
#include <stdio.h>
#include <stdlib.h>

// Struct do nó: guarda um valor inteiro e um ponteiro para o próximo nó
typedef struct No {
    int valor;
    struct No *prox;
} No;

// Protótipos das funções usadas
No *no_criar(int valor);
void inserir_final(No **cabeca, int valor);
void destruir_lista(No *cabeca);
int buscar(No *cabeca, int alvo);

int main(void) {
    int v, num, n2, alvo;

    // Lê a quantidade de valores e o primeiro número
    scanf("%d %d", &v, &num);

    // Cria a lista com o primeiro nó
    No *cabeca = no_criar(num);
    if (cabeca == NULL) return 1;

    // Lê os demais valores e insere no final
    for (int i = 0; i < v - 1; i++) {
        scanf("%d", &n2);
        inserir_final(&cabeca, n2);
    }

    // Imprime a lista
    No *atual = cabeca;
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->prox;
    }
    printf("nil\n");

    // Lê o valor a buscar e imprime o índice
    scanf("%d", &alvo);
    printf("%d\n", buscar(cabeca, alvo));

    // Libera toda a memória alocada
    destruir_lista(cabeca);
    return 0;
}

// Aloca um novo nó com o valor fornecido e prox = NULL
No *no_criar(int valor) {
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL) return NULL;

    novo->valor = valor;
    novo->prox = NULL;

    return novo;
}

// Insere um novo nó no FINAL da lista
void inserir_final(No **cabeca, int valor) {
    No *novo = no_criar(valor);
    if (novo == NULL) return;

    // Caso especial: lista vazia → o novo nó vira a cabeça
    if (*cabeca == NULL) {
        *cabeca = novo;
        return;
    }

    // Percorre até o último nó
    No *atual = *cabeca;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }

    // O último nó agora aponta para o novo
    atual->prox = novo;
}

// Libera todos os nós da lista
void destruir_lista(No *cabeca) {
    No *atual = cabeca;
    while (atual != NULL) {
        No *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
}

// Busca um valor na lista e retorna o índice da primeira ocorrência
// Se não encontrar, retorna -1
int buscar(No *cabeca, int alvo) {
    int indice = 0;
    No *atual = cabeca;

    while (atual != NULL) {
        if (atual->valor == alvo) {
            return indice;      // achou: retorna o índice
        }
        atual = atual->prox;    // avança para o próximo
        indice++;               // incrementa o índice
    }

    return -1;                  // percorreu tudo e não achou
}