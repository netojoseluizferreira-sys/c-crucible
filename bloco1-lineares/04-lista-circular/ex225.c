// 225 — Sistema de Rodízio com Prioridade e Remoção por Nome
// Lista circular dupla de guardas. Cada guarda tem nome e prioridade.
// Comandos:
//   A <nome> <prioridade> : adicionar guarda ao final
//   R                     : remover o guarda atual (cursor) e imprimir nome
//   P                     : girar a lista (passar para o próximo)
//   L                     : listar todos na ordem circular
//   B <nome>              : buscar guarda por nome e imprimir posição
//   Q                     : sair
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Nó da lista dupla circular: valor (nome) + prioridade + prox + ant
typedef struct NoDuplo {
    char valor[100];
    int prioridade;
    struct NoDuplo *prox;
    struct NoDuplo *ant;
} NoDuplo;

// Lista circular dupla: cabeca, cauda e tamanho
typedef struct ListaCircular {
    NoDuplo *cabeca;
    NoDuplo *cauda;
    int tamanho;
} ListaCircular;

// Cursor: aponta para a lista e para o nó atual
typedef struct Cursor{
    ListaCircular *lista;
    NoDuplo *atual;
} Cursor;

// Protótipos
NoDuplo *noDuplo_criar(char *valor, int prioridade);
void inserir_fim(ListaCircular *l, char *valor, int prioridade);
void imprimir(Cursor *c);
void destruir_lista(ListaCircular *l);
void cursor_avancar(Cursor **c);
int cursor_remover(Cursor **c, char *v);
void buscar(ListaCircular *l, char *alvo);
void limparTela(void);
void aguardarEnter(void);

int main(void) {
    char v[100], op;
    int k;

    // Cria a lista circular vazia
    ListaCircular *l = (ListaCircular *)malloc(sizeof(ListaCircular));
    if (l == NULL) return 1;
    l->cabeca = NULL;
    l->cauda = NULL;
    l->tamanho = 0;

    // Cursor na heap, apontando para a lista; começa sem nó atual
    Cursor *c = (Cursor *)malloc(sizeof(Cursor));
    if (c == NULL) return 1;
    c->lista = l;
    c->atual = NULL;

    // Laço principal: processa um comando por iteração
    do {
        limparTela();
        printf("A - Adicionar guarda\n");
        printf("R - Remover guarda atual\n");
        printf("P - Girar lista\n");
        printf("L - Listar todos\n");
        printf("B - Buscar por nome\n");
        printf("Q - Sair\n");
        printf("Operacao: ");
        scanf(" %c", &op);
        getchar();   // consome o '\n' deixado pelo scanf

        switch (op) {
        case 'A':
            // Lê o nome e a prioridade
            fgets(v, sizeof(v), stdin);
            int j = 0;
            while (v[j] != '\n' && v[j] != '\0') j++;
            v[j] = '\0';

            scanf("%d", &k);
            getchar();

            inserir_fim(l, v, k);

            // Se a lista tinha só o nó recém-inserido, posiciona o cursor
            if (l->cabeca != NULL && l->cabeca->prox == l->cabeca)
                c->atual = l->cabeca;
            break;

        case 'R':
            // Remove o guarda atual e imprime o nome removido
            if (cursor_remover(&c, v))
                printf("removido: %s\n", v);
            else
                printf("Nada para remover\n");
            break;

        case 'P':
            // Gira a lista: cursor avança um nó
            cursor_avancar(&c);
            break;

        case 'L':
            // Lista todos na ordem circular
            imprimir(c);
            break;

        case 'B':
            // Lê o nome a buscar e imprime posição
            fgets(v, sizeof(v), stdin);
            j = 0;
            while (v[j] != '\n' && v[j] != '\0') j++;
            v[j] = '\0';
            buscar(l, v);
            break;

        case 'Q':
            printf("Saindo...\n");
            break;

        default:
            break;
        }
        if (op != 'L') imprimir(c);
        aguardarEnter();
    } while (op != 'Q');

    free(c);
    destruir_lista(l);
    free(l);

    return 0;
}

// Aloca um nó com valor, prioridade, prox e ant = NULL
NoDuplo *noDuplo_criar(char *valor, int prioridade) {
    NoDuplo *novo = (NoDuplo *)malloc(sizeof(NoDuplo));
    if (novo == NULL) return NULL;

    strcpy(novo->valor, valor);
    novo->prioridade = prioridade;
    novo->prox = NULL;
    novo->ant = NULL;

    return novo;
}

// Insere no FINAL da lista circular dupla em O(1)
void inserir_fim(ListaCircular *l, char *valor, int prioridade) {
    NoDuplo *novo = noDuplo_criar(valor, prioridade);
    if (novo == NULL) return;

    if (l->cabeca == NULL) {
        novo->prox = novo;
        novo->ant = novo;
        l->cabeca = novo;
        l->cauda = novo;
    } else {
        l->cauda->prox = novo;
        novo->prox = l->cabeca;
        novo->ant = l->cauda;
        l->cabeca->ant = novo;
        l->cauda = novo;
    }

    l->tamanho++;
}

// Imprime uma volta completa a partir do cursor, no formato [a,b,c]
void imprimir(Cursor *c) {
    if (c == NULL || c->lista == NULL || c->lista->cabeca == NULL) {
        printf("LISTA VAZIA\n");
        return;
    }

    // Se o cursor estiver nulo, começa pela cabeca
    NoDuplo *atual = (c->atual != NULL) ? c->atual : c->lista->cabeca;

    printf("[");
    for (int i = 0; i < c->lista->tamanho; i++) {
        printf("%s %d", atual->valor, atual->prioridade);
        if (i < c->lista->tamanho - 1)
            printf(",");
        atual = atual->prox;
    }
    printf("]\n");
}

// Libera todos os nós da lista circular dupla
void destruir_lista(ListaCircular *l) {
    if (l == NULL || l->cabeca == NULL) return;

    int n = l->tamanho;
    NoDuplo *atual = l->cabeca;
    NoDuplo *proximo;

    for (int i = 0; i < n; i++) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    l->cabeca = NULL;
    l->cauda = NULL;
    l->tamanho = 0;
}

// Avança o cursor um nó. Se já estiver no fim, dá a volta (circular)
void cursor_avancar(Cursor **c) {
    if (c == NULL || *c == NULL) return;
    if ((*c)->atual == NULL) return;
    (*c)->atual = (*c)->atual->prox;
}

// Remove o nó do cursor e reposiciona. Devolve 1/0 e o nome via char*.
//
// Como o valor é string, o chamador passa um buffer (char v[100]).
// A função copia o nome antes de liberar o nó.
//
// Casos:
//   - Lista vazia ou cursor nulo: retorna 0.
//   - Único nó: lista fica vazia, cursor = NULL.
//   - Mais de um nó: religa ant->prox = prox, prox->ant = ant,
//     ajusta cabeca/cauda se o alvo for uma das pontas, e move o
//     cursor para o PRÓXIMO nó.
int cursor_remover(Cursor **c, char *v) {
    if (c == NULL || *c == NULL) return 0;
    if ((*c)->lista == NULL || (*c)->lista->cabeca == NULL) return 0;
    if ((*c)->atual == NULL) return 0;

    NoDuplo *alvo = (*c)->atual;
    ListaCircular *l = (*c)->lista;

    if (v != NULL) strcpy(v, alvo->valor);

    if (alvo == alvo->prox) {
        // Único nó
        l->cabeca = NULL;
        l->cauda = NULL;
        (*c)->atual = NULL;
    } else {
        alvo->ant->prox = alvo->prox;
        alvo->prox->ant = alvo->ant;

        if (alvo == l->cabeca) l->cabeca = alvo->prox;
        if (alvo == l->cauda) l->cauda = alvo->ant;

        (*c)->atual = alvo->prox;
    }

    free(alvo);
    l->tamanho--;
    return 1;
}

// Busca guarda por nome e imprime posição (0-based) na lista circular.
// Usa o contador 'tamanho' para não entrar em loop infinito.
void buscar(ListaCircular *l, char *alvo) {
    if (l == NULL || l->cabeca == NULL) {
        printf("LISTA VAZIA\n");
        return;
    }

    NoDuplo *atual = l->cabeca;
    int i = 0;

    for (i = 0; i < l->tamanho; i++) {
        if (strcmp(atual->valor, alvo) == 0) {
            printf("posicao: %d\n", i);
            return;
        }
        atual = atual->prox;
    }

    printf("Nome nao encontrado\n");
}

// Limpa a tela (Windows: cls, Linux/macOS: clear)
void limparTela(void) {
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