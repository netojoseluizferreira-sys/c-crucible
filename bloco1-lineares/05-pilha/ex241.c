// 241 — Undo/Redo com Múltiplos Níveis
// Lista dupla de strings (linhas de texto) com pilha auxiliar de undo.
// Comandos:
//   I texto : inserir texto no final
//   D       : remover do final (empilha a string removida no undo)
//   U       : desfazer o último D (desempilha e reinsere no final)
//   L       : listar
//   Q       : sair
// Permite múltiplos D seguidos e múltiplos U seguidos: cada D empilha
// um valor, cada U desempilha um. Se U for chamado com a pilha vazia,
// imprime "Nada para desfazer".
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 100

// Nó da lista dupla: string alocada + prox + ant
typedef struct NoDuplo {
    char *valor;
    struct NoDuplo *prox;
    struct NoDuplo *ant;
} NoDuplo;

// Lista dupla: cabeca e cauda
typedef struct ListaDupla {
    NoDuplo *cabeca;
    NoDuplo *cauda;
} ListaDupla;

// Cursor: aponta para a lista e para o nó atual
typedef struct Cursor{
    ListaDupla *lista;
    NoDuplo *atual;
} Cursor;

// Nó da pilha auxiliar (lista simples de strings)
typedef struct No {
    char *valor;
    struct No *prox;
} No;

// Protótipos
NoDuplo *noDuplo_criar(char *valor);
void inserir_final(ListaDupla *l, char *valor);
void imprimir_frente(Cursor *c);
void destruir_lista(ListaDupla *l);
int remover_final(ListaDupla *l, char *v);
void limparTela(void);
void aguardarEnter(void);
No *no_criar(char *valor);
void push(No **topo, char *valor);
int pop(No **topo, char *valor);
void destruir_pilha(No **topo);

int main(void) {
    char v[TAM];
    char op;
    ListaDupla *l = (ListaDupla *)malloc(sizeof(ListaDupla));
    if (l == NULL) return 1;
    l->cabeca = NULL;
    l->cauda = NULL;

    // Cursor na heap, apontando para a lista; começa sem nó atual
    Cursor *c = (Cursor *)malloc(sizeof(Cursor));
    if (c == NULL) return 1;
    c->lista = l;
    c->atual = NULL;

    // Pilha auxiliar de undo (topo = NULL = vazia)
    No *topo = NULL;

    do {
        limparTela();
        printf("I - Inserir texto\n");
        printf("D - Remover do final\n");
        printf("U - Desfazer\n");
        printf("L - Listar\n");
        printf("Q - Sair\n");
        printf("Operacao: ");
        scanf(" %c", &op);
        getchar();   // consome o '\n' deixado pelo scanf

        switch (op) {
        case 'I':
            // Lê a linha inteira e remove o '\n' do final
            fgets(v, sizeof(v), stdin);
            int j = 0;
            while (v[j] != '\n' && v[j] != '\0') j++;
            v[j] = '\0';
            inserir_final(l, v);
            break;

        case 'D':
            // Remove do final e empilha a string removida.
            // Vários D seguidos empilham vários valores.
            if (remover_final(c->lista, v))
                push(&topo, v);
            break;

        case 'U':
            // Desfaz o último D: desempilha e reinsere no final.
            // Vários U seguidos desempilham na ordem inversa.
            if (pop(&topo, v))
                inserir_final(c->lista, v);
            else
                printf("Nada para desfazer\n");
            break;

        case 'L':
            imprimir_frente(c);
            break;

        case 'Q':
            printf("Saindo...\n");
            break;

        default:
            break;
        }
        if (op != 'L') imprimir_frente(c);
        aguardarEnter();
    } while (op != 'Q');

    destruir_pilha(&topo);
    free(c);
    destruir_lista(l);
    free(l);

    return 0;
}

// Aloca um nó e copia a string para dentro dele
NoDuplo *noDuplo_criar(char *valor) {
    NoDuplo *novo = (NoDuplo *)malloc(sizeof(NoDuplo));
    if (novo == NULL) return NULL;

    novo->valor = (char *)malloc(strlen(valor) + 1);
    if (novo->valor == NULL) {
        free(novo);
        return NULL;
    }
    strcpy(novo->valor, valor);

    novo->prox = NULL;
    novo->ant = NULL;

    return novo;
}

// Insere no FINAL em O(1)
void inserir_final(ListaDupla *l, char *valor) {
    NoDuplo *novo = noDuplo_criar(valor);
    if (novo == NULL) return;

    novo->prox = NULL;
    novo->ant = l->cauda;

    if (l->cauda == NULL) {
        l->cabeca = novo;
        l->cauda = novo;
    } else {
        l->cauda->prox = novo;
        l->cauda = novo;
    }
}

// Imprime a lista no formato [a,b,c], marcando o nó do cursor com '>'
void imprimir_frente(Cursor *c) {
    if (c == NULL || c->lista == NULL) return;

    NoDuplo *atual = c->lista->cabeca;
    if (atual == NULL) {
        printf("LISTA VAZIA\n");
        return;
    }

    printf("[");
    while (atual != NULL) {
        if (c->atual == atual)
            printf(">%s", atual->valor);
        else
            printf("%s", atual->valor);

        if (atual->prox != NULL)
            printf(",");
        atual = atual->prox;
    }
    printf("]\n");
}

// Libera todos os nós (e as strings) e reseta cabeca/cauda
void destruir_lista(ListaDupla *l) {
    NoDuplo *atual = l->cabeca;

    while (atual != NULL) {
        NoDuplo *proximo = atual->prox;
        free(atual->valor);   // libera a string
        free(atual);          // libera o nó
        atual = proximo;
    }

    l->cabeca = NULL;
    l->cauda = NULL;
}

// Remove o último nó. Copia a string para 'v' antes de liberar.
int remover_final(ListaDupla *l, char *v) {
    if (l == NULL || l->cauda == NULL) return 0;

    NoDuplo *remover = l->cauda;

    if (remover == l->cabeca) {
        l->cabeca = NULL;
        l->cauda = NULL;
    } else {
        l->cauda = remover->ant;
        l->cauda->prox = NULL;
    }

    if (v != NULL) strcpy(v, remover->valor);
    free(remover->valor);
    free(remover);
    return 1;
}

// Limpa a tela
void limparTela(void){
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

// Cria um nó da pilha auxiliar, copiando a string
No *no_criar(char *valor) {
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL) return NULL;

    novo->valor = (char *)malloc(strlen(valor) + 1);
    if (novo->valor == NULL) {
        free(novo);
        return NULL;
    }
    strcpy(novo->valor, valor);

    novo->prox = NULL;
    return novo;
}

// Empilha: insere um novo nó no TOPO da pilha (copia a string)
void push(No **topo, char *valor) {
    No *novo = no_criar(valor);
    if (novo == NULL) return;

    novo->prox = *topo;
    *topo = novo;
}

// Desempilha: remove o nó do TOPO e copia a string para 'valor'
int pop(No **topo, char *valor) {
    if (topo == NULL || *topo == NULL) return 0;

    No *atual = *topo;
    strcpy(valor, atual->valor);   // copia antes de liberar
    *topo = atual->prox;

    free(atual->valor);
    free(atual);

    return 1;
}

// Libera todos os nós da pilha (e as strings) e seta *topo para NULL
void destruir_pilha(No **topo) {
    if (topo == NULL || *topo == NULL) return;

    No *atual = *topo;
    while (atual != NULL) {
        No *proximo = atual->prox;
        free(atual->valor);   // libera a string
        free(atual);          // libera o nó
        atual = proximo;
    }
    *topo = NULL;
}