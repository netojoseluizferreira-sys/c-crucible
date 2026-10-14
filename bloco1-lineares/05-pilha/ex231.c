// 231 — Pilha com Array Estático
// Pilha com array de capacidade fixa (100).
// Implementa push que recusa quando cheia, pop e peek.
// O main lê comandos 'E X' (empilhar), 'D' (desempilhar), 'T' (ver topo).
// 'E' com pilha cheia imprime "Cheia". 'D' com pilha vazia imprime
// "Pilha vazia". Ao final, imprime a pilha.
#include <stdio.h>
#include <stdlib.h>

#define CAP 100

// Pilha com array estático: dados + topo (índice do próximo livre)
typedef struct {
    int dados[CAP];
    int topo;
} Pilha;

// Protótipos
void pilha_iniciar(Pilha *p);
int  esta_vazia(Pilha *p);
int  esta_cheia(Pilha *p);
void push(Pilha *p, int valor);
int  pop(Pilha *p, int *valor);
int  peek(Pilha *p, int *valor);
void imprimir(Pilha *p);

int main(void) {
    int v;
    char op;
    Pilha p;

    pilha_iniciar(&p);

    do {
        printf("E - Empilhar\nD - Desempilhar\nT - Ver topo\nQ - Sair\nAcao: ");
        scanf(" %c", &op);
        getchar();   // consome o '\n' deixado pelo scanf

        switch (op) {
        case 'E':
            scanf("%d", &v);
            getchar();   // consome o '\n' do valor
            if (esta_cheia(&p))
                printf("Cheia\n");
            else
                push(&p, v);
            break;

        case 'D':
            if (pop(&p, &v))
                printf("%d\n", v);
            else
                printf("Pilha vazia\n");
            break;

        case 'T':
            if (peek(&p, &v))
                printf("%d\n", v);
            else
                printf("Pilha vazia\n");
            break;

        case 'Q':
            printf("Imprimindo pilha: ");
            break;

        default:
            printf("Operacao invalida\n");
            break;
        }
    } while (op != 'Q');

    imprimir(&p);
    printf("Fechando...\n");

    return 0;
}

// Inicia a pilha: topo = 0 (vazia)
void pilha_iniciar(Pilha *p) {
    p->topo = 0;
}

// Retorna 1 se a pilha estiver vazia, 0 caso contrário
int esta_vazia(Pilha *p) {
    return p->topo == 0;
}

// Retorna 1 se a pilha estiver cheia, 0 caso contrário
int esta_cheia(Pilha *p) {
    return p->topo == CAP;
}

// Empilha: escreve no topo e avança o índice.
// Só deve ser chamada após verificar esta_cheia.
void push(Pilha *p, int valor) {
    p->dados[p->topo] = valor;
    p->topo++;
}

// Desempilha: recua o topo e devolve o valor via ponteiro.
// Retorna 1 em sucesso, 0 se a pilha estiver vazia.
int pop(Pilha *p, int *valor) {
    if (esta_vazia(p)) return 0;

    p->topo--;
    *valor = p->dados[p->topo];
    return 1;
}

// Espia o topo sem remover. Retorna 1 em sucesso, 0 se vazia.
int peek(Pilha *p, int *valor) {
    if (esta_vazia(p)) return 0;

    *valor = p->dados[p->topo - 1];
    return 1;
}

// Imprime a pilha do TOPO até a BASE no formato [a,b,c]
void imprimir(Pilha *p) {
    if (esta_vazia(p)) {
        printf("PILHA VAZIA\n");
        return;
    }

    printf("[");
    for (int i = p->topo - 1; i >= 0; i--) {
        printf("%d", p->dados[i]);
        if (i > 0) printf(",");
    }
    printf("]\n");
}