// 236 — Notação Posfixa (RPN) com duas pilhas
// Duas pilhas independentes:
//   - Pilha de INT para avaliar a expressão posfixa (rpn).
//   - Pilha de CHAR para balanceamento (herdada do 234/235).
// O main só chama rpn; o balanceamento continua disponível para uso.
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

// ---------- Pilha de CHAR (para balanceamento) ----------

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

// ---------- RPN ----------

int rpn(NoInt **topo, char *valor);

// ==================== MAIN ====================

int main(void) {
    NoInt *topoInt = NULL;
    char valor[100];

    fgets(valor, sizeof(valor), stdin);
    int j = 0;
    while (valor[j] != '\n' && valor[j] != '\0') j++;
    valor[j] = '\0';

    int resultado = rpn(&topoInt, valor);
    printf("%d\n", resultado);

    destruirInt(&topoInt);
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

// Verifica se a string está balanceada considerando (), [], {}.
// Retorna 1 se balanceado, 0 caso contrário.
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

// Avalia uma expressão posfixa usando a pilha de INT.
//
// Estratégia:
//   - Percorre a string caractere a caractere.
//   - Dígito: acumula num buffer (suporta múltiplos dígitos).
//   - Espaço ou operador: fecha o número acumulado (se houver) e
//     empilha o valor.
//   - Operador: desempilha b (direita) e a (esquerda), aplica, empilha.
//   - Ao final, deve sobrar um único valor: o resultado.
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
            // Fecha o número acumulado
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

    // Fecha o último número, se houver
    if (tem_digito) {
        pushInt(topo, num);
    }

    // Deve sobrar um único valor
    if (!popInt(topo, &res)) return 0;
    if (*topo != NULL) return 0;

    return res;
}