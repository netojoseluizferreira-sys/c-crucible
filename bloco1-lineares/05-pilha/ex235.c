// 235 — Balanceamento com Vários Tipos
// Pilha encadeada simples (nó + topo).
// Verifica se uma string está balanceada considerando três pares:
//   (), [], {}
// Cada fechamento deve casar com a abertura do topo da pilha.
// O nó guarda o caractere de abertura para permitir a comparação.
// Retorna 1 se balanceado, 0 caso contrário.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Nó da pilha: agora guarda um char (a abertura) em vez de int
typedef struct No {
    char valor;
    struct No *prox;
} No;

// Protótipos
No *no_criar(char valor);
void push(No **topo, char valor);
int pop(No **topo, char *valor);
int peek(No *topo, char *valor);
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
No *no_criar(char valor) {
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL) return NULL;

    novo->valor = valor;
    novo->prox = NULL;

    return novo;
}

// Empilha: insere um novo nó no TOPO da pilha
void push(No **topo, char valor) {
    No *novo = no_criar(valor);
    if (novo == NULL) return;

    novo->prox = *topo;
    *topo = novo;
}

// Desempilha: remove o nó do TOPO e devolve seu valor via ponteiro
// Retorna 1 se sucesso, 0 se a pilha está vazia
int pop(No **topo, char *valor) {
    if (topo == NULL || *topo == NULL) return 0;

    No *atual = *topo;
    *valor = atual->valor;
    *topo = atual->prox;
    free(atual);

    return 1;
}

// Espia o TOPO: devolve o valor sem remover.
int peek(No *topo, char *valor) {
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
        printf("%c", atual->valor);
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

// Verifica se os parênteses, colchetes e chaves estão balanceados
// e se cada fechamento casa com a abertura correta.
//
// Estratégia:
//   - Percorre a string caractere a caractere.
//   - Ao encontrar uma abertura ('(', '[', '{'), empilha o próprio
//     caractere de abertura.
//   - Ao encontrar um fechamento (')', ']', '}'), desempilha o topo
//     e verifica se ele é a abertura correspondente:
//        ')' casa com '('
//        ']' casa com '['
//        '}' casa com '{'
//     Se a pilha estiver vazia ou a abertura for diferente, retorna 0.
//   - Outros caracteres são ignorados.
//   - Ao final, a pilha deve estar vazia. Se sobrou algo, é porque
//     alguma abertura não foi fechada -> retorna 0.
//
// Retorna 1 se balanceado, 0 caso contrário.
int balanceamento(No **topo, char *valor) {
    if (topo == NULL || valor == NULL) return 0;

    char aberto;
    int i = 0;

    while (valor[i] != '\0') {
        char c = valor[i];

        if (c == '(' || c == '[' || c == '{') {
            push(topo, c);
        }
        else if (c == ')' || c == ']' || c == '}') {
            if (pop(topo, &aberto) == 0) {
                return 0;   // fechamento sem abertura correspondente
            }

            // Verifica se a abertura casa com o fechamento
            if (c == ')' && aberto != '(') return 0;
            if (c == ']' && aberto != '[') return 0;
            if (c == '}' && aberto != '{') return 0;
        }
        i++;
    }

    // Se a pilha não está vazia, alguma abertura ficou sem fechar
    if (*topo != NULL) return 0;

    return 1;
}