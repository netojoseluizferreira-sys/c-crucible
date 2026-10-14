// 234 — Parênteses Balanceados
// Pilha encadeada simples (nó + topo).
// Implementa balanceamento(No **topo, char *valor) que verifica se
// os parênteses de uma string estão balanceados:
//   - '(' empilha
//   - ')' desempilha; se a pilha estiver vazia, não está balanceado
// Ao final, a pilha deve estar vazia.
// Retorna 1 se balanceado, 0 caso contrário.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
int balanceamento(No **topo, char *valor);

int main(void) {
    No *topo = NULL;
    char valor[50];

    // Lê a string do usuário
    scanf("%s", valor);

    if (balanceamento(&topo, valor))
        printf("Balanceado\n");
    else
        printf("Nao balanceado\n");

    destruir_lista(&topo);
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

// Verifica se os parênteses da string estão balanceados.
//
// Estratégia:
//   - Percorre a string caractere a caractere.
//   - '(' empilha um valor qualquer (usamos 1 como placeholder).
//   - ')' desempilha; se a pilha estiver vazia (pop devolve 0),
//     significa que apareceu um ')' sem '(' correspondente ->
//     retorna 0 imediatamente.
//   - Outros caracteres são ignorados.
//   - Ao final, a pilha deve estar vazia. Se sobrou algo, é porque
//     algum '(' não foi fechado -> retorna 0.
//
// Retorna 1 se balanceado, 0 caso contrário.
int balanceamento(No **topo, char *valor) {
    if (topo == NULL || valor == NULL) return 0;

    int lixo;
    int i = 0;

    while (valor[i] != '\0') {
        if (valor[i] == '(') {
            push(topo, 1);
        }
        else if (valor[i] == ')') {
            if (pop(topo, &lixo) == 0) {
                return 0;   // ')' sem '(' correspondente
            }
        }
        i++;
    }

    // Se a pilha não está vazia, algum '(' ficou sem fechar
    if (*topo != NULL) return 0;

    return 1;
}