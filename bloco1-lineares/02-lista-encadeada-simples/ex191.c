// 191 — Fila com Lista Encadeada (versão eficiente)
// Implementa uma fila (FIFO) com ponteiros para início E fim.
// enfileirar insere no final em O(1) graças ao ponteiro fim.
// desenfileirar remove do início em O(1).
// Primeiro que entra é o primeiro que sai.
#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *prox;
} No;

// Struct da fila: guarda início e fim
// - inicio: primeiro nó (de onde removemos)
// - fim: último nó (onde inserimos)
// Ambos NULL quando a fila está vazia
typedef struct {
    No *inicio;
    No *fim;
} Fila;

No *no_criar(int valor);
void enfileirar(Fila *f, int valor);
int desenfileirar(Fila *f, int *valor);
void imprimir(Fila *f);
void destruir_fila(Fila *f);

int main(void) {
    int v;
    char op;
    Fila f = { NULL, NULL };  // fila começa vazia

    do {
        // Mostra o menu e lê a opção
        printf("enfileirar - E\ndesenfileirar - D\nVIEW - V\nEXIT - Q\nACTION: ");
        scanf(" %c", &op);
        getchar();  // consome o '\n' deixado pelo scanf

        switch (op) {
            case 'E':
                // ENFILEIRAR: lê valor e coloca no fim da fila
                scanf(" %d", &v);
                enfileirar(&f, v);
                printf("%d enfileirado\n", v);
                break;

            case 'D':
                // DESENFILEIRAR: tenta remover do início
                // Retorna 1 se sucesso, 0 se fila vazia
                if (desenfileirar(&f, &v)) {
                    printf("%d desenfileirado\n", v);
                } else {
                    printf("FILA VAZIA\n");
                }
                break;

            case 'V':
                // VIEW: imprime a fila do início ao fim
                imprimir(&f);
                break;

            case 'Q':
                // EXIT: libera tudo e sai
                printf("DESLIGANDO...\n");
                destruir_fila(&f);
                break;

            default:
                printf("OPERACAO INVALIDA\n");
                break;
        }

    } while (op != 'Q');

    return 0;
}

// Aloca um novo nó
No *no_criar(int valor) {
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL) return NULL;

    novo->valor = valor;
    novo->prox = NULL;

    return novo;
}

// ENFILEIRAR: insere um novo nó no FINAL da fila em O(1)
// O ponteiro f->fim permite ir direto ao último nó
// sem percorrer a lista toda
void enfileirar(Fila *f, int valor) {
    No *novo = no_criar(valor);
    if (novo == NULL) return;

    if (f->inicio == NULL) {
        // Fila vazia: o novo nó é início e fim ao mesmo tempo
        f->inicio = novo;
        f->fim = novo;
    } else {
        // Fila não vazia: anexa o novo depois do atual fim
        f->fim->prox = novo;  // último nó aponta para o novo
        f->fim = novo;        // fim passa a ser o novo
    }
}

// DESENFILEIRAR: remove o nó do INÍCIO em O(1)
// Devolve o valor via ponteiro
// Retorna 1 se sucesso, 0 se a fila está vazia
int desenfileirar(Fila *f, int *valor) {
    if (f == NULL || f->inicio == NULL) return 0;  // fila vazia

    No *atual = f->inicio;      // guarda o nó do início
    *valor = atual->valor;       // copia o valor para o caller
    f->inicio = atual->prox;     // início passa a ser o próximo
    free(atual);                 // libera o nó removido

    // Se o início virou NULL, a fila ficou vazia → fim também NULL
    // Sem isso, f->fim continuaria apontando para memória liberada
    if (f->inicio == NULL) {
        f->fim = NULL;
    }

    return 1;
}

// Imprime a fila do início até o fim
void imprimir(Fila *f) {
    if (f == NULL || f->inicio == NULL) {
        printf("FILA VAZIA\n");
        return;
    }
    printf("FILA ATUAL: ");
    No *atual = f->inicio;
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->prox;
    }
    printf("NULL\n");
}

// Libera todos os nós da fila e reseta início e fim
void destruir_fila(Fila *f) {
    if (f == NULL) return;

    No *atual = f->inicio;
    while (atual != NULL) {
        No *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    f->inicio = NULL;
    f->fim = NULL;
}