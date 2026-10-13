// 215 — Desfazer Simples com Pilha Auxiliar
// Implementa "desfazer" em uma lista dupla de inteiros usando uma pilha
// auxiliar. Cada valor removido do final é empilhado; 'U' desempilha e
// reinsere no final da lista.
// Comandos:
//   I valor : inserir no final
//   D       : remover do final (empilha o valor removido)
//   U       : desfazer último D (desempilha e insere no final)
//   L       : listar
//   Q       : sair
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Nó da lista dupla: valor + ponteiro para o próximo e para o anterior
typedef struct NoDuplo {
    int valor;
    struct NoDuplo *prox;
    struct NoDuplo *ant;
} NoDuplo;

// Lista dupla: guarda o primeiro e o último nó.
typedef struct ListaDupla {
    NoDuplo *cabeca;
    NoDuplo *cauda;
} ListaDupla;

// Cursor: aponta para a lista e para o nó atual.
typedef struct Cursor{
    ListaDupla *lista;
    NoDuplo *atual;
} Cursor;

// Nó da pilha auxiliar (lista simples)
typedef struct No {
    int valor;
    struct No *prox;
} No;

// Protótipos
NoDuplo *noDuplo_criar(int valor);
void inserir_inicio(ListaDupla *l, int valor);
void inserir_final(ListaDupla *l, int valor);
int  inserir_posicao(ListaDupla *l, int valor, int pos);
void imprimir_frente(Cursor *c);
void destruir_lista(ListaDupla *l);
int remover_inicio(ListaDupla *l, int *v);
int remover_final(ListaDupla *l, int *v);
int remover_posicao(ListaDupla *l, int posicao, int *v);
void cursor_inicio(Cursor **c);
void cursor_fim(Cursor **c);
void cursor_avancar(Cursor **c);
void cursor_retroceder(Cursor **c);
void cursor_remover(Cursor **c);
int cursor_valor(Cursor *c);
void limparTela(void);
void aguardarEnter(void);
No *no_criar(int valor);
void push(No **topo, int valor);
int pop(No **topo, int *valor);
void imprimir(No *topo);
void destruir_pilha(No **topo);

int main(void) {
    int v;
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

    // Pilha auxiliar (topo = NULL = vazia)
    No *topo = NULL;

    // Laço principal: processa um comando por iteração
    do {
        limparTela();
        printf("I - Inserir valor\n");
        printf("D - Remover do final\n");
        printf("U - Desfazer\n");
        printf("L - Listar\n");
        printf("Q - Sair\n");
        printf("Operacao: ");
        scanf(" %c", &op);
        getchar();   // consome o '\n' deixado pelo scanf

        switch (op) {
        case 'I':
            // Lê o valor e insere no final da lista
            scanf("%d", &v);
            getchar();   // consome o '\n' do valor
            inserir_final(l, v);
            break;

        case 'D':
            // Remove do final e empilha o valor removido.
            // remover_final devolve 1 se removeu, 0 se lista vazia.
            if (remover_final(c->lista, &v))
                push(&topo, v);
            break;

        case 'U':
            // Desfaz: desempilha e reinsere no final da lista
            if (pop(&topo, &v))
                inserir_final(c->lista, v);
            else
                printf("Nada para ser desfeito\n");
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

    // Libera tudo
    destruir_pilha(&topo);
    free(c);
    destruir_lista(l);
    free(l);

    return 0;
}

// Aloca um nó com valor, prox e ant = NULL
NoDuplo *noDuplo_criar(int valor) {
    NoDuplo *novo = (NoDuplo *)malloc(sizeof(NoDuplo));
    if (novo == NULL) return NULL;

    novo->valor = valor;
    novo->prox = NULL;
    novo->ant = NULL;

    return novo;
}

// Insere no INÍCIO em O(1)
void inserir_inicio(ListaDupla *l, int valor) {
    NoDuplo *novo = noDuplo_criar(valor);
    if (novo == NULL) return;

    novo->ant = NULL;
    novo->prox = l->cabeca;

    if (l->cabeca == NULL) {
        l->cabeca = novo;
        l->cauda = novo;
    } else {
        l->cabeca->ant = novo;
        l->cabeca = novo;
    }
}

// Insere no FINAL em O(1)
void inserir_final(ListaDupla *l, int valor) {
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

// Insere em posição específica da lista dupla (1 = ok, 0 = inválida).
int inserir_posicao(ListaDupla *l, int valor, int pos) {
    if (pos < 0) return 0;

    if (l->cabeca == NULL || pos == 0) {
        inserir_inicio(l, valor);
        return 1;
    }

    NoDuplo *atual = l->cabeca;
    int i = 0;

    while (i < pos - 1 && atual->prox != NULL) {
        atual = atual->prox;
        i++;
    }

    if (atual->prox == NULL) {
        inserir_final(l, valor);
        return 1;
    }

    NoDuplo *novo = noDuplo_criar(valor);
    if (novo == NULL) return 0;

    NoDuplo *proximo = atual->prox;

    novo->ant = atual;
    novo->prox = proximo;
    atual->prox = novo;
    proximo->ant = novo;

    return 1;
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
            printf(">%d", atual->valor);
        else
            printf("%d", atual->valor);

        if (atual->prox != NULL)
            printf(",");
        atual = atual->prox;
    }
    printf("]\n");
}

// Libera todos os nós e reseta cabeca/cauda
void destruir_lista(ListaDupla *l) {
    NoDuplo *atual = l->cabeca;

    while (atual != NULL) {
        NoDuplo *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    l->cabeca = NULL;
    l->cauda = NULL;
}

// Remove o primeiro nó em O(1).
// Devolve 1 em sucesso (com *v preenchido) e 0 se a lista estiver vazia.
// Mesmo estilo do pop: usar variável de saída em vez de valor mágico,
// porque -1 poderia ser um valor válido na lista.
int remover_inicio(ListaDupla *l, int *v) {
    if (l == NULL || l->cabeca == NULL) return 0;

    NoDuplo *remover = l->cabeca;

    if (remover == l->cauda) {
        l->cabeca = NULL;
        l->cauda = NULL;
    } else {
        l->cabeca = remover->prox;
        l->cabeca->ant = NULL;
    }

    if (v != NULL) *v = remover->valor;
    free(remover);
    return 1;
}

// Remove o último nó em O(1).
// Devolve 1 em sucesso (com *v preenchido) e 0 se a lista estiver vazia.
// Mesmo estilo do pop: usar variável de saída em vez de valor mágico,
// porque -1 poderia ser um valor válido na lista.
int remover_final(ListaDupla *l, int *v) {
    if (l == NULL || l->cauda == NULL) return 0;

    NoDuplo *remover = l->cauda;

    if (remover == l->cabeca) {
        l->cabeca = NULL;
        l->cauda = NULL;
    } else {
        l->cauda = remover->ant;
        l->cauda->prox = NULL;
    }

    if (v != NULL) *v = remover->valor;
    free(remover);
    return 1;
}

// Remove o nó na posição.
// Devolve 1 em sucesso (com *v preenchido) e 0 se posição inválida.
int remover_posicao(ListaDupla *l, int posicao, int *v) {
    NoDuplo *cabeca = l->cabeca;
    if (cabeca == NULL) return 0;

    if (posicao <= 0) {
        return remover_inicio(l, v);
    }

    NoDuplo *atual = cabeca;
    int indice = 0;

    while (atual->prox != NULL && indice < posicao - 1) {
        atual = atual->prox;
        indice++;
    }

    if (atual->prox == NULL) return 0;

    NoDuplo *remover = atual->prox;
    if (v != NULL) *v = remover->valor;

    atual->prox = remover->prox;
    if (remover->prox != NULL) {
        remover->prox->ant = atual;
    }

    free(remover);
    return 1;
}

// Posiciona o cursor no primeiro nó da lista.
void cursor_inicio(Cursor **c){
    if (c == NULL || *c == NULL) return;
    if ((*c)->lista == NULL || (*c)->lista->cabeca == NULL) return;
    (*c)->atual = (*c)->lista->cabeca;
}

// Posiciona o cursor no último nó da lista.
void cursor_fim(Cursor **c){
    if (c == NULL || *c == NULL) return;
    if ((*c)->lista == NULL || (*c)->lista->cauda == NULL) return;
    (*c)->atual = (*c)->lista->cauda;
}

// Avança o cursor um nó. Se já estiver no fim, não muda.
void cursor_avancar(Cursor **c){
    if (c == NULL || *c == NULL) return;
    if ((*c)->atual == NULL) return;
    if ((*c)->atual->prox != NULL){
        (*c)->atual = (*c)->atual->prox;
    }
}

// Retrocede o cursor um nó. Se já estiver no início, não muda.
void cursor_retroceder(Cursor **c){
    if (c == NULL || *c == NULL) return;
    if ((*c)->atual == NULL) return;
    if ((*c)->atual->ant != NULL){
        (*c)->atual = (*c)->atual->ant;
    }
}

// Retorna o valor do nó atual, ou -1 se o cursor for inválido.
int cursor_valor(Cursor *c){
    if (c == NULL || c->atual == NULL) return -1;
    return c->atual->valor;
}

// Remove o nó apontado pelo cursor e reposiciona o cursor.
void cursor_remover(Cursor **c){
    if (c == NULL || *c == NULL) return;
    if ((*c)->lista == NULL || (*c)->lista->cabeca == NULL) return;
    if ((*c)->atual == NULL) return;

    NoDuplo *alvo = (*c)->atual;

    // Decide o próximo cursor ANTES de remover (evita dangling pointer)
    if (alvo->ant != NULL) {
        (*c)->atual = alvo->ant;
    } else if (alvo->prox != NULL) {
        (*c)->atual = alvo->prox;
    } else {
        (*c)->atual = NULL;
    }

    // Descobre o índice do nó alvo percorrendo a lista
    int indice = 0;
    NoDuplo *atual = (*c)->lista->cabeca;
    while (atual != NULL && atual != alvo) {
        atual = atual->prox;
        indice++;
    }

    if (atual == NULL) return;

    // Remove por posição; descarta o valor retornado
    int lixo;
    remover_posicao((*c)->lista, indice, &lixo);
}

// Limpa a tela (Windows: cls, Linux/macOS: clear)
void limparTela(void){
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}

// Pausa até o usuário pressionar ENTER (trata EOF para não travar)
void aguardarEnter(void) {
    printf("Pressione ENTER para continuar...");

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

// Cria um nó da pilha auxiliar
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

    novo->prox = *topo;   // novo aponta para o antigo topo
    *topo = novo;         // topo passa a ser o novo nó
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
void destruir_pilha(No **topo) {
    if (topo == NULL || *topo == NULL) return;

    No *atual = *topo;
    while (atual != NULL) {
        No *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    *topo = NULL;
}