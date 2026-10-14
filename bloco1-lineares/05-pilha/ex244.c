// 244 — Validar HTML Simples
// Pilha de CHAR (char por char) para balanceamento de tags HTML.
// Cada tag aberta (<a>) empilha seus caracteres na ordem inversa
// (do '>' até o '<'), para que o fechamento (</a>) possa comparar
// letra por letra.
//
// Estratégia:
//   - Ao encontrar '<':
//       - Se for '<' seguido de '/', é fechamento. Lê o nome da tag
//         até '>' ou espaço. Depois desempilha letra por letra do nome,
//         comparando com o nome lido (em ordem inversa). Por fim,
//         desempilha o '<' que foi empilhado na abertura.
//       - Senão, é abertura. Empilha '<' e depois cada caractere do
//         nome da tag até '>' ou espaço. Pula atributos até '>'.
//   - Ignora qualquer outro caractere.
//   - Ao final, a pilha deve estar vazia (toda tag aberta foi fechada).
// Retorna 1 se balanceado, 0 caso contrário.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------- Pilha de CHAR (para balanceamento HTML) ----------

typedef struct NoChar {
    char valor;
    struct NoChar *prox;
} NoChar;

NoChar *noChar_criar(char valor);
void    pushChar(NoChar **topo, char valor);
int     popChar(NoChar **topo, char *valor);
int     peekChar(NoChar *topo, char *valor);
void    imprimirChar(NoChar *topo);
void    destruirChar(NoChar **topo);
int     balanceamentoHTML(NoChar **topo, char *valor);

// ==================== MAIN ====================

int main(void) {
    NoChar *topo = NULL;
    char valor[100];

    fgets(valor, sizeof(valor), stdin);
    int j = 0;
    while (valor[j] != '\n' && valor[j] != '\0') j++;
    valor[j] = '\0';

    if (balanceamentoHTML(&topo, valor))
        printf("Balanceada\n");
    else
        printf("Nao balanceada\n");

    destruirChar(&topo);
    return 0;
}

// ==================== PILHA DE CHAR ====================

NoChar *noChar_criar(char valor) {
    NoChar *novo = (NoChar *)malloc(sizeof(NoChar));
    if (novo == NULL) return NULL;

    novo->valor = valor;
    novo->prox = NULL;
    return novo;
}

void pushChar(NoChar **topo, char valor) {
    NoChar *novo = noChar_criar(valor);
    if (novo == NULL) return;

    novo->prox = *topo;
    *topo = novo;
}

int popChar(NoChar **topo, char *valor) {
    if (topo == NULL || *topo == NULL) return 0;

    NoChar *atual = *topo;
    *valor = atual->valor;
    *topo = atual->prox;
    free(atual);
    return 1;
}

int peekChar(NoChar *topo, char *valor) {
    if (topo == NULL) return 0;
    *valor = topo->valor;
    return 1;
}

void imprimirChar(NoChar *topo) {
    NoChar *atual = topo;
    if (atual == NULL) {
        printf("PILHA CHAR VAZIA\n");
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

// ==================== BALANCEAMENTO HTML ====================

// Verifica se as tags HTML estão balanceadas.
//
// Estratégia:
//   - Percorre a string caractere a caractere.
//   - Ao encontrar '<':
//       - Se o próximo for '/', é fechamento:
//           * Lê o nome da tag até '>' ou espaço.
//           * Desempilha letra por letra do nome, comparando com o
//             nome lido (de trás para frente, porque a pilha guarda
//             os caracteres em ordem inversa).
//           * Desempilha o '<' correspondente.
//       - Senão, é abertura:
//           * Empilha '<'.
//           * Empilha cada caractere do nome até '>' ou espaço.
//           * Pula atributos até '>'.
//   - Ignora qualquer outro caractere.
//   - Ao final, a pilha deve estar vazia.
//
// Retorna 1 se balanceado, 0 caso contrário.
int balanceamentoHTML(NoChar **topo, char *valor) {
    if (topo == NULL || valor == NULL) return 0;

    int i = 0;

    while (valor[i] != '\0') {
        if (valor[i] == '<') {
            i++;

            if (valor[i] == '/') {
                // Fechamento: </tag>
                i++;
                char tag_fechamento[50];
                int j = 0;

                // Lê o nome da tag até '>' ou espaço
                while (valor[i] != '>' && valor[i] != '\0' && valor[i] != ' ') {
                    if (j < 49) tag_fechamento[j++] = valor[i];
                    i++;
                }
                tag_fechamento[j] = '\0';

                // Desempilha o nome de trás para frente
                char letra;
                for (int k = j - 1; k >= 0; k--) {
                    if (popChar(topo, &letra) == 0) return 0;
                    if (letra != tag_fechamento[k]) return 0;
                }

                // Desempilha o '<'
                if (popChar(topo, &letra) == 0 || letra != '<') return 0;

                // Pula até o '>'
                while (valor[i] != '>' && valor[i] != '\0') i++;
            }
            else {
                // Abertura: <tag>
                pushChar(topo, '<');

                // Empilha cada caractere do nome até '>' ou espaço
                while (valor[i] != '>' && valor[i] != '\0' && valor[i] != ' ') {
                    pushChar(topo, valor[i]);
                    i++;
                }

                // Pula atributos até o '>'
                while (valor[i] != '>' && valor[i] != '\0') {
                    i++;
                }
            }
        }

        if (valor[i] != '\0') {
            i++;
        }
    }

    // Se a pilha não está vazia, alguma tag ficou aberta
    if (*topo != NULL) return 0;
    return 1;
}