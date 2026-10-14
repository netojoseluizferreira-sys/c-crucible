// 245 — Calculadora com Memória (Mini Projeto)
// Pilha encadeada de inteiros que funciona como calculadora.
// Comandos:
//   E X : empilhar X
//   +   : desempilha dois, soma, empilha
//   -   : desempilha dois, subtrai (a - b), empilha
//   *   : desempilha dois, multiplica, empilha
//   /   : desempilha dois, divide (a / b), empilha
//   T   : imprime o topo sem remover
//   L   : lista a pilha inteira
//   Q   : sair
// O main processa os comandos e imprime conforme T e L.
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
void limparTela(void);
void aguardarEnter(void);

int main(void) {
    int v, a, b, res;
    char op;
    No *topo = NULL;

    do {
        limparTela();
        printf("E X - Empilhar X\n");
        printf("+   - Somar\n");
        printf("-   - Subtrair\n");
        printf("*   - Multiplicar\n");
        printf("/   - Dividir\n");
        printf("T   - Ver topo\n");
        printf("L   - Listar pilha\n");
        printf("Q   - Sair\n");
        printf("Acao: ");
        scanf(" %c", &op);
        getchar();   // consome o '\n' deixado pelo scanf

        switch (op) {
        case 'E':
            scanf("%d", &v);
            getchar();   // consome o '\n' do valor
            push(&topo, v);
            break;

        case '+':
            // Desempilha b (topo) e a (abaixo), soma e empilha
            if (pop(&topo, &b)) {
                if (pop(&topo, &a)) {
                    res = a + b;
                    push(&topo, res);
                } else {
                    push(&topo, b);   // devolve o que saiu
                    printf("Valores insuficientes\n");
                }
            } else {
                printf("Pilha vazia\n");
            }
            break;

        case '-':
            // Desempilha b (topo) e a (abaixo), faz a - b e empilha
            if (pop(&topo, &b)) {
                if (pop(&topo, &a)) {
                    res = a - b;
                    push(&topo, res);
                } else {
                    push(&topo, b);
                    printf("Valores insuficientes\n");
                }
            } else {
                printf("Pilha vazia\n");
            }
            break;

        case '*':
            // Desempilha b (topo) e a (abaixo), multiplica e empilha
            if (pop(&topo, &b)) {
                if (pop(&topo, &a)) {
                    res = a * b;   // corrigido: era a + b
                    push(&topo, res);
                } else {
                    push(&topo, b);
                    printf("Valores insuficientes\n");
                }
            } else {
                printf("Pilha vazia\n");
            }
            break;

        case '/':
            // Desempilha b (topo) e a (abaixo), faz a / b e empilha
            if (pop(&topo, &b)) {
                if (pop(&topo, &a)) {
                    if (b == 0) {
                        printf("Divisao por 0\n");
                        push(&topo, a);   // devolve os dois operandos
                        push(&topo, b);
                        break;
                    }
                    res = a / b;
                    push(&topo, res);
                } else {
                    push(&topo, b);
                    printf("Valores insuficientes\n");
                }
            } else {
                printf("Pilha vazia\n");
            }
            break;

        case 'T':
            if (peek(topo, &v))
                printf("%d\n", v);
            else
                printf("Pilha vazia\n");
            break;

        case 'L':
            imprimir(topo);
            break;

        case 'Q':
            printf("Saindo...\n");
            break;

        default:
            printf("Operacao invalida\n");
            break;
        }
        if(op != 'L') imprimir(topo);
        aguardarEnter();
    } while (op != 'Q');

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

// Limpa a tela (Windows: cls, Linux/macOS: clear)
void limparTela(void) {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}

// Pausa até ENTER
void aguardarEnter(void) {
    printf("Pressione ENTER para continuar...");

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}