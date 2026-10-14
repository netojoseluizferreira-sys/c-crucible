// 243 — Pilha de Strings
// Pilha encadeada de strings (char[100]). Cada nó guarda uma palavra.
// O main lê N palavras, empilha todas e depois desempilha imprimindo
// na ordem inversa. 'pop' copia a string para o buffer do chamador
// antes de liberar o nó.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Nó da pilha de strings: valor[100] + prox
typedef struct NoChar {
    char valor[100];
    struct NoChar *prox;
} NoChar;

// Protótipos
NoChar *noChar_criar(char *valor);
void    pushChar(NoChar **topo, char *valor);
int     popChar(NoChar **topo, char *valor);
int     peekChar(NoChar *topo, char *valor);
void    imprimirChar(NoChar *topo);
void    destruirChar(NoChar **topo);

int main(void) {
    NoChar *topoChar = NULL;
    char valor[100];
    int num;

    // Lê N e empilha N palavras
    scanf("%d", &num);
    getchar();   // consome o '\n' deixado pelo scanf

    for (int i = 0; i < num; i++) {
        fgets(valor, sizeof(valor), stdin);
        int j = 0;
        while (valor[j] != '\n' && valor[j] != '\0') j++;
        valor[j] = '\0';

        pushChar(&topoChar, valor);
    }

    // Desempilha e imprime na ordem inversa
    printf("Invertida: ");
    while (popChar(&topoChar, valor)) {
        printf("%s ", valor);
    }
    printf("\n");

    // Estado final (deve estar vazia)
    imprimirChar(topoChar);
    destruirChar(&topoChar);

    return 0;
}

// Aloca um nó e copia a string para dentro dele
NoChar *noChar_criar(char *valor) {
    NoChar *novo = (NoChar *)malloc(sizeof(NoChar));
    if (novo == NULL) return NULL;

    strcpy(novo->valor, valor);
    novo->prox = NULL;
    return novo;
}

// Empilha: insere um novo nó no TOPO da pilha
void pushChar(NoChar **topo, char *valor) {
    NoChar *novo = noChar_criar(valor);
    if (novo == NULL) return;

    novo->prox = *topo;
    *topo = novo;
}

// Desempilha: remove o nó do TOPO e copia a string para 'valor'
int popChar(NoChar **topo, char *valor) {
    if (topo == NULL || *topo == NULL) return 0;

    NoChar *atual = *topo;
    strcpy(valor, atual->valor);
    *topo = atual->prox;
    free(atual);
    return 1;
}

// Espia o TOPO: copia a string sem remover.
int peekChar(NoChar *topo, char *valor) {
    if (topo == NULL) return 0;
    strcpy(valor, topo->valor);
    return 1;
}

// Imprime a pilha do TOPO até a BASE
void imprimirChar(NoChar *topo) {
    NoChar *atual = topo;
    if (atual == NULL) {
        printf("PILHA CHAR VAZIA\n");
        return;
    }
    while (atual != NULL) {
        printf("%s ", atual->valor);
        atual = atual->prox;
    }
    printf("\n");
}

// Libera todos os nós da pilha e seta *topo para NULL
void destruirChar(NoChar **topo) {
    if (topo == NULL || *topo == NULL) return;

    NoChar *atual = *topo;
    while (atual != NULL) {
        NoChar *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    *topo = NULL;
}