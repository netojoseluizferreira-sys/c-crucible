// 233 — Inverter uma Lista com Pilha
// Pilha encadeada simples (nó + topo).
// O main lê N inteiros, empilha todos, e depois desempilha tudo
// imprimindo na ordem inversa. Usa uma segunda pilha para inverter
// e comparar as duas ordens.
#include <stdio.h>
#include <stdlib.h>

// Nó da pilha: valor + ponteiro para o próximo
typedef struct No {
    int valor;
    struct No *prox;
} No;

// Protótipos
No *no_criar(int valor);
void push(No **topo, int valor);
int pop(No **topo, int *valor);
int peek(No *topo, int *valor);
void imprimir(No *topo);
void destruir_lista(No **topo);

int main(void) {
    int num, v;
    No *topo = NULL;
    No *topo2 = NULL;

    // Lê N e empilha todos
    scanf("%d", &num);
    for (int i = 0; i < num; i++) {
        scanf("%d", &v);
        push(&topo, v);
    }

    printf("Original (base -> topo): ");
    imprimir(topo);

    // Transfere da pilha original para a segunda pilha.
    // Como pop remove do topo e push insere no topo, a segunda pilha
    // fica com a ordem invertida em relação à primeira.
    while (topo != NULL) {
        if (pop(&topo, &v)) {
            push(&topo2, v);
        }
    }

    printf("Invertida (base -> topo): ");
    imprimir(topo2);

    destruir_lista(&topo);
    destruir_lista(&topo2);
    return 0;
}

// Aloca um nó com valor e prox = NULL
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

    novo->prox = *topo;
    *topo = novo;
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

// Espia o TOPO: devolve o valor sem remover.
int peek(No *topo, int *valor) {
    if (topo == NULL) return 0;

    *valor = topo->valor;

    return 1;
}

// Imprime a pilha do TOPO até a BASE no formato [a,b,c]
void imprimir(No *topo) {
    No *atual = topo;
    if (atual == NULL) {
        printf("PILHA VAZIA\n");
        return;
    }

    printf("[");
    while (atual != NULL) {
        printf("%d", atual->valor);
        atual = atual->prox;
        if (atual != NULL) printf(",");
    }
    printf("]\n");
}

// Libera todos os nós da pilha e seta *topo para NULL
void destruir_lista(No **topo) {
    if (topo == NULL || *topo == NULL) return;

    No *atual = *topo;
    while (atual != NULL) {
        No *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    *topo = NULL;
}