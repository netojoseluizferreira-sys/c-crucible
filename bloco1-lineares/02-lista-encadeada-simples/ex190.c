// 190 — Pilha com Lista Encadeada
// Implementa uma pilha (LIFO) usando lista encadeada.
// push insere no topo, pop remove do topo.
// Demonstra a especialização da lista: só operações nas extremidades.
#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *prox;
} No;

No *no_criar(int valor);
void push(No **topo, int valor);
int pop(No **topo, int *valor);
void imprimir(No *topo);
void destruir_lista(No **topo);

int main(void) {
    int v;
    char op;
    No *topo = NULL;  // pilha começa vazia

    do {
        // Mostra o menu e lê a opção
        printf("PUSH - E\nPOP - D\nVIEW - V\nEXIT - Q\nACTION: ");
        scanf(" %c", &op);
        getchar();  // consome o '\n' deixado pelo scanf

        switch (op) {
            case 'E':
                // PUSH: lê valor e empilha
                scanf(" %d", &v);
                push(&topo, v);
                printf("%d empilhado\n", v);
                break;

            case 'D':
                // POP: tenta desempilhar
                // pop retorna 1 se sucesso, 0 se pilha vazia
                if (pop(&topo, &v)) {
                    printf("%d desempilhado\n", v);
                } else {
                    printf("PILHA VAZIA\n");
                }
                break;

            case 'V':
                // VIEW: imprime a pilha do topo até a base
                imprimir(topo);
                break;

            case 'Q':
                // EXIT: libera tudo e sai
                printf("DESLIGANDO...\n");
                destruir_lista(&topo);
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

// Empilha: insere um novo nó no TOPO da pilha
// Equivalente a inserir no início da lista
void push(No **topo, int valor) {
    No *novo = no_criar(valor);
    if (novo == NULL) return;

    novo->prox = *topo;   // novo aponta para o antigo topo
    *topo = novo;         // topo passa a ser o novo nó
}

// Desempilha: remove o nó do TOPO e devolve seu valor via ponteiro
// Retorna 1 se sucesso, 0 se a pilha está vazia
// Usar ponteiro para o valor evita usar um valor mágico (tipo -1) como erro,
// já que -1 poderia ser um valor válido empilhado
int pop(No **topo, int *valor) {
    if (topo == NULL || *topo == NULL) return 0;  // falha: pilha vazia

    No *atual = *topo;      // guarda o nó do topo
    *valor = atual->valor;   // copia o valor para o caller
    *topo = atual->prox;     // topo passa a ser o próximo
    free(atual);             // libera o nó removido

    return 1;  // sucesso
}

// Imprime a pilha do topo até a base
void imprimir(No *topo) {
    No *atual = topo;
    if (atual == NULL) {
        printf("PILHA VAZIA\n");
        return;
    }
    printf("PILHA ATUAL: ");
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->prox;
    }
    printf("NULL\n");
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