// 172 — Remover do Início
// Remove o primeiro nó da lista, ajustando a cabeça para o segundo nó.
// Demonstra o cuidado com lista vazia e liberação correta do nó removido.
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
void remover_inicio(No **cabeca);

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

    // Remove o primeiro nó
    remover_inicio(&cabeca);

    // Imprime a lista após a remoção
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
int buscar(No *cabeca, int alvo) {
    int indice = 0;
    No *atual = cabeca;

    while (atual != NULL) {
        if (atual->valor == alvo) {
            return indice;
        }
        atual = atual->prox;
        indice++;
    }

    return -1;
}

// Remove o primeiro nó da lista
// A cabeça passa a ser o segundo nó; o primeiro é liberado com free
void remover_inicio(No **cabeca) {
    // Proteção: se o ponteiro para a cabeça for NULL ou a lista estiver vazia, não faz nada
    if (cabeca == NULL || *cabeca == NULL) {
        return;
    }

    // Guarda o nó que será removido (o atual primeiro)
    No *atual = *cabeca;

    // Guarda o próximo nó (que será a nova cabeça)
    No *proximo = atual->prox;

    // Libera o nó removido
    free(atual);

    // Atualiza a cabeça para o próximo nó
    *cabeca = proximo;
}