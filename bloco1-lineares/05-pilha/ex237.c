// 237 — Infixa para Posfixa
// Duas pilhas independentes:
//   - Pilha de INT para avaliar a expressão posfixa (rpn) — herdada do 236.
//   - Pilha de CHAR para conversão e balanceamento (herdada do 234/235).
// Implementa inf_to_posf(NoChar **topo, char *valor) que converte uma
// expressão infixa sem parênteses para a forma posfixa.
// Precedência: * / > + -.
// O main lê uma expressão infixa e imprime a forma posfixa.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------- Pilha de INT (para RPN) ----------

typedef struct NoInt {
    int valor;
    struct NoInt *prox;
} NoInt;

NoInt *noInt_criar(int valor);
void   pushInt(NoInt **topo, int valor);
int    popInt(NoInt **topo, int *valor);
int    peekInt(NoInt *topo, int *valor);
void   imprimirInt(NoInt *topo);
void   destruirInt(NoInt **topo);

// ---------- Pilha de CHAR (para conversão e balanceamento) ----------

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
int     balanceamento(NoChar **topo, char *valor);

// ---------- RPN e conversão ----------

int rpn(NoInt **topo, char *valor);
char *inf_to_posf(NoChar **topo, char *valor);

// ==================== MAIN ====================

int main(void) {
    NoChar *topoChar = NULL;
    char valor[100];

    fgets(valor, sizeof(valor), stdin);
    int j = 0;
    while (valor[j] != '\n' && valor[j] != '\0') j++;
    valor[j] = '\0';

    printf("%s\n", inf_to_posf(&topoChar, valor));

    destruirChar(&topoChar);
    return 0;
}

// ==================== PILHA DE INT ====================

NoInt *noInt_criar(int valor) {
    NoInt *novo = (NoInt *)malloc(sizeof(NoInt));
    if (novo == NULL) return NULL;

    novo->valor = valor;
    novo->prox = NULL;
    return novo;
}

void pushInt(NoInt **topo, int valor) {
    NoInt *novo = noInt_criar(valor);
    if (novo == NULL) return;

    novo->prox = *topo;
    *topo = novo;
}

int popInt(NoInt **topo, int *valor) {
    if (topo == NULL || *topo == NULL) return 0;

    NoInt *atual = *topo;
    *valor = atual->valor;
    *topo = atual->prox;
    free(atual);
    return 1;
}

int peekInt(NoInt *topo, int *valor) {
    if (topo == NULL) return 0;
    *valor = topo->valor;
    return 1;
}

void imprimirInt(NoInt *topo) {
    NoInt *atual = topo;
    if (atual == NULL) {
        printf("PILHA INT VAZIA\n");
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

void destruirInt(NoInt **topo) {
    if (topo == NULL || *topo == NULL) return;

    NoInt *atual = *topo;
    while (atual != NULL) {
        NoInt *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    *topo = NULL;
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

// ==================== BALANCEAMENTO ====================

int balanceamento(NoChar **topo, char *valor) {
    if (topo == NULL || valor == NULL) return 0;

    char aberto;
    int i = 0;

    while (valor[i] != '\0') {
        char c = valor[i];

        if (c == '(' || c == '[' || c == '{') {
            pushChar(topo, c);
        }
        else if (c == ')' || c == ']' || c == '}') {
            if (popChar(topo, &aberto) == 0) return 0;

            if (c == ')' && aberto != '(') return 0;
            if (c == ']' && aberto != '[') return 0;
            if (c == '}' && aberto != '{') return 0;
        }
        i++;
    }

    if (*topo != NULL) return 0;
    return 1;
}

// ==================== RPN ====================

int rpn(NoInt **topo, char *valor) {
    if (topo == NULL || valor == NULL) return 0;

    int i = 0;
    int num = 0;
    int tem_digito = 0;
    int a, b, res;

    while (valor[i] != '\0') {
        char c = valor[i];

        if (c >= '0' && c <= '9') {
            num = num * 10 + (c - '0');
            tem_digito = 1;
        }
        else {
            if (tem_digito) {
                pushInt(topo, num);
                num = 0;
                tem_digito = 0;
            }

            if (c == '+' || c == '-' || c == '*' || c == '/') {
                if (!popInt(topo, &b)) return 0;
                if (!popInt(topo, &a)) return 0;

                switch (c) {
                    case '+': res = a + b; break;
                    case '-': res = a - b; break;
                    case '*': res = a * b; break;
                    case '/':
                        if (b == 0) return 0;
                        res = a / b;
                        break;
                }

                pushInt(topo, res);
            }
        }
        i++;
    }

    if (tem_digito) {
        pushInt(topo, num);
    }

    if (!popInt(topo, &res)) return 0;
    if (*topo != NULL) return 0;

    return res;
}

// ==================== INFIXA → POSFIXA ====================

// Converte uma expressão infixa sem parênteses para posfixa.
//
// Estratégia:
//   - Percorre a string caractere a caractere.
//   - Dígito: copia o número completo direto para a saída (com espaço).
//   - Operador: enquanto o topo da pilha tiver precedência >= ao atual,
//     desempilha para a saída. Depois empilha o operador atual.
//   - Ao final, desempilha tudo o que sobrou.
//
// Precedência:
//   * e / têm precedência maior que + e -.
//   O loop de desempilhamento compara o topo com o operador atual:
//     - topo * ou / sempre desempilha (precedência >= qualquer um)
//     - topo + ou - só desempilha se o atual também for + ou -
//
// Retorna uma string alocada dinamicamente com a expressão posfixa.
// O chamador deve liberar com free().
char *inf_to_posf(NoChar **topo, char *valor) {
    if (valor == NULL) return NULL;

    // Aloca espaço para o resultado. Cada operando vira "N " e cada
    // operador vira "op ", então 2x o tamanho da entrada é suficiente.
    int tam = 0;
    while (valor[tam] != '\0') tam++;

    char *res = (char *)malloc((size_t)(tam * 2 + 1) * sizeof(char));
    if (res == NULL) return NULL;

    int i = 0, j = 0;

    while (valor[i] != '\0') {
        char c = valor[i];

        // Ignora espaços em branco na entrada
        if (c == ' ' || c == '\t') {
            i++;
            continue;
        }

        // 1. Dígito: copia o número completo direto para a saída
        if (c >= '0' && c <= '9') {
            while (valor[i] >= '0' && valor[i] <= '9') {
                res[j++] = valor[i++];
            }
            res[j++] = ' ';
            i--;   // compensa o i++ do while externo
        }
        // 2. Parêntese aberto: vai direto para a pilha
        else if (c == '(') {
            pushChar(topo, c);
        }
        // 3. Parêntese fechado: desempilha até o '('
        else if (c == ')') {
            char op;
            while (*topo != NULL && (*topo)->valor != '(') {
                popChar(topo, &op);
                res[j++] = op;
                res[j++] = ' ';
            }
            if (*topo != NULL) {
                popChar(topo, &op);   // remove o '('
            }
        }
        // 4. Operador: desempilha os de precedência maior ou igual
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (*topo != NULL && (*topo)->valor != '(') {
                char t = (*topo)->valor;

                // Precedência: topo desempilha se for >= ao atual
                if ((t == '*' || t == '/') ||
                    ((t == '+' || t == '-') && (c == '+' || c == '-'))) {
                    char op_topo;
                    popChar(topo, &op_topo);
                    res[j++] = op_topo;
                    res[j++] = ' ';
                } else {
                    break;
                }
            }
            pushChar(topo, c);
        }
        i++;
    }

    // 5. Esvazia o que sobrou na pilha
    char op_restante;
    while (*topo != NULL) {
        popChar(topo, &op_restante);
        res[j++] = op_restante;
        res[j++] = ' ';
    }

    // Remove o último espaço e finaliza
    if (j > 0 && res[j-1] == ' ') {
        res[j-1] = '\0';
    } else {
        res[j] = '\0';
    }

    return res;
}