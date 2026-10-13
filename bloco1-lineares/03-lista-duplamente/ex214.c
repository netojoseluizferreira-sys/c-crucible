// 214 — Histórico de Navegação
// Implementa um navegador simples com lista dupla e cursor.
// Comandos:
//   A <pagina> : adicionar página no final
//   V          : voltar  (cursor retrocede)
//   F          : avançar  (cursor avança)
//   L          : listar histórico com indicador de cursor ('>')
//   Q          : sair
// Reaproveita a estrutura e as funções dos exercícios anteriores.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Nó da lista dupla: valor + ponteiro para o próximo e para o anterior
typedef struct NoDuplo {
    char valor[200];
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

// Protótipos
NoDuplo *noDuplo_criar(char *valor);
void inserir_inicio(ListaDupla *l, char *valor);
void inserir_final(ListaDupla *l, char *valor);
int  inserir_posicao(ListaDupla *l, char *valor, int pos);
void imprimir_frente(Cursor *c);
void destruir_lista(ListaDupla *l);
char *remover_inicio(ListaDupla *l);
char *remover_final(ListaDupla *l);
char *remover_posicao(ListaDupla *l, int posicao);
void cursor_inicio(Cursor **c);
void cursor_fim(Cursor **c);
void cursor_avancar(Cursor **c);
void cursor_retroceder(Cursor **c);
void cursor_remover(Cursor **c);
char *cursor_valor(Cursor *c);
void limparTela(void);
void aguardarEnter(void);

int main(void) {
    char v[200], op;
    ListaDupla *l = (ListaDupla *)malloc(sizeof(ListaDupla));
    if (l == NULL) return 1;
    l->cabeca = NULL;
    l->cauda = NULL;

    // Cursor na stack, apontando para a lista; começa sem nó atual
    Cursor *c = (Cursor *)malloc(sizeof(Cursor));
    if (c == NULL) return 1;
    c->lista = l;
    c->atual = NULL;

    // Laço principal do navegador: processa um comando por iteração
    do {
        limparTela();
        printf("A - Adicionar pagina no final\n");
        printf("V - Voltar\n");
        printf("F - Avancar\n");
        printf("L - Listar Historico\n");
        printf("Q - Sair\n");
        printf("Operacao: ");
        scanf(" %c", &op);
        getchar();   // consome o '\n' deixado pelo scanf

        switch (op) {
        case 'V':
            // Volta o cursor um nó e mostra o histórico atualizado
            cursor_retroceder(&c);
            imprimir_frente(c);
            break;

        case 'F':
            // Avança o cursor um nó e mostra o histórico atualizado
            cursor_avancar(&c);
            imprimir_frente(c);
            break;

        case 'A':
            // Lê a página inteira e remove o '\n' do final
            fgets(v, sizeof(v), stdin);
            int j = 0;
            while (v[j] != '\n' && v[j] != '\0') j++;
            v[j] = '\0';

            inserir_final(l, v);

            // Se a lista tinha só o nó recém-inserido (era vazia antes),
            // posiciona o cursor nele para o usuário já poder navegar.
            if (l->cabeca != NULL && l->cabeca->prox == NULL)
                cursor_inicio(&c);
            break;

        case 'L':
            // Lista todo o histórico, marcando o nó do cursor com '>'
            imprimir_frente(c);
            break;

        case 'Q':
            printf("Fechando navegador...\n");
            break;

        default:
            break;
        }
        aguardarEnter();
    } while (op != 'Q');

    free(c);
    destruir_lista(l);
    free(l);

    return 0;
}

// Aloca um nó com valor, prox e ant = NULL
NoDuplo *noDuplo_criar(char *valor) {
    NoDuplo *novo = (NoDuplo *)malloc(sizeof(NoDuplo));
    if (novo == NULL) return NULL;

    strcpy(novo->valor, valor);
    novo->prox = NULL;
    novo->ant = NULL;

    return novo;
}

// Insere no INÍCIO em O(1)
void inserir_inicio(ListaDupla *l, char *valor) {
    NoDuplo *novo = noDuplo_criar(valor);
    if (novo == NULL) return;

    novo->ant = NULL;
    novo->prox = l->cabeca;

    if (l->cabeca == NULL) {
        // Lista vazia: novo é o único nó
        l->cabeca = novo;
        l->cauda = novo;
    } else {
        // A ordem importa: usa l->cabeca antes de sobrescrever
        l->cabeca->ant = novo;
        l->cabeca = novo;
    }
}

// Insere no FINAL em O(1)
void inserir_final(ListaDupla *l, char *valor) {
    NoDuplo *novo = noDuplo_criar(valor);
    if (novo == NULL) return;

    novo->prox = NULL;
    novo->ant = l->cauda;

    if (l->cauda == NULL) {
        // Lista vazia: novo é o único nó
        l->cabeca = novo;
        l->cauda = novo;
    } else {
        // A ordem importa: usa l->cauda antes de sobrescrever
        l->cauda->prox = novo;
        l->cauda = novo;
    }
}

// Insere em posição específica da lista dupla (1 = ok, 0 = inválida).
int inserir_posicao(ListaDupla *l, char *valor, int pos) {
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

    // Ajusta os 4 ponteiros do meio
    novo->ant = atual;
    novo->prox = proximo;
    atual->prox = novo;
    proximo->ant = novo;

    return 1;
}

// Imprime a lista do INÍCIO ao FIM, marcando o nó do cursor com '>'.
void imprimir_frente(Cursor *c) {
    if (c == NULL || c->lista == NULL) return;

    NoDuplo *atual = c->lista->cabeca;
    if (atual == NULL) {
        printf("LISTA VAZIA\n");
        return;
    }

    while (atual != NULL) {
        if (c->atual == atual)
            printf("> %s\n", atual->valor);
        else
            printf("%s\n", atual->valor);
        atual = atual->prox;
    }
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

// Remove o primeiro nó em O(1); retorna cópia do valor ou NULL se vazia.
char *remover_inicio(ListaDupla *l) {
    if (l == NULL || l->cabeca == NULL) return NULL;

    NoDuplo *remover = l->cabeca;

    if (remover == l->cauda) {
        // Único nó: lista fica vazia
        l->cabeca = NULL;
        l->cauda = NULL;
    } else {
        // Mais de um nó: o segundo vira cabeca
        l->cabeca = remover->prox;
        l->cabeca->ant = NULL;
    }

    // Aloca espaço exato para a cópia do valor (antes do free)
    char *valor = (char *)malloc(strlen(remover->valor) + 1);
    if (valor == NULL) {
        free(remover);
        return NULL;
    }
    strcpy(valor, remover->valor);
    free(remover);
    return valor;
}

// Remove o último nó em O(1); retorna cópia do valor ou NULL se vazia.
char *remover_final(ListaDupla *l) {
    if (l == NULL || l->cauda == NULL) return NULL;

    NoDuplo *remover = l->cauda;

    if (remover == l->cabeca) {
        // Único nó: lista fica vazia
        l->cabeca = NULL;
        l->cauda = NULL;
    } else {
        // Mais de um nó: o penúltimo vira cauda
        l->cauda = remover->ant;
        l->cauda->prox = NULL;
    }

    char *valor = (char *)malloc(strlen(remover->valor) + 1);
    if (valor == NULL) {
        free(remover);
        return NULL;
    }
    strcpy(valor, remover->valor);
    free(remover);
    return valor;
}

// Remove o nó na posição e retorna cópia do valor, ou NULL se inválida.
char *remover_posicao(ListaDupla *l, int posicao) {
    NoDuplo *cabeca = l->cabeca;
    if (cabeca == NULL) return NULL;

    if (posicao <= 0) {
        return remover_inicio(l);
    }

    NoDuplo *atual = cabeca;
    int indice = 0;

    while (atual->prox != NULL && indice < posicao - 1) {
        atual = atual->prox;
        indice++;
    }

    if (atual->prox == NULL) return NULL;

    NoDuplo *remover = atual->prox;

    char *valor = (char *)malloc(strlen(remover->valor) + 1);
    if (valor == NULL) {
        return NULL;
    }
    strcpy(valor, remover->valor);

    // Religa o anterior ao próximo, pulando o removido
    atual->prox = remover->prox;
    if (remover->prox != NULL) {
        remover->prox->ant = atual;
    }

    free(remover);
    return valor;
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

// Retorna o valor do nó atual, ou NULL se o cursor for inválido.
char *cursor_valor(Cursor *c){
    if (c == NULL || c->atual == NULL) return NULL;
    return c->atual->valor;
}

// Remove o nó apontado pelo cursor e reposiciona o cursor.
// Casos:
//   - Cursor nulo/lista vazia: não faz nada
//   - Cursor no único nó: lista fica vazia, cursor = NULL
//   - Cursor no início: remove e cursor vai para o próximo
//   - Cursor no meio/fim: cursor vai para o nó ANTERIOR (mais seguro que
//     apontar para memória já liberada), depois remove
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
        // Único nó: lista vai ficar vazia
        (*c)->atual = NULL;
    }

    // Descobre o índice do nó alvo percorrendo a lista
    int indice = 0;
    NoDuplo *atual = (*c)->lista->cabeca;
    while (atual != NULL && atual != alvo) {
        atual = atual->prox;
        indice++;
    }

    // Se por algum motivo não achou, aborta
    if (atual == NULL) return;

    // Remove por posição; descarta a string retornada (editor não usa)
    char *lixo = remover_posicao((*c)->lista, indice);
    free(lixo);
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