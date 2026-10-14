// 242 — Chamadas de Função Simuladas
// Pilha encadeada de frames de chamada. Cada frame guarda o nome da
// função.
// Comandos:
//   C <funcao> : chamar função (empilhar um frame com o nome)
//   R <valor>  : retornar da função atual (desempilha e imprime
//                "Retornando de <funcao> com valor <valor>")
//   P          : imprimir a pilha de chamadas (do topo até a base)
//   Q          : sair
// O valor de retorno é lido no comando R; o frame guarda apenas o nome.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Nó da pilha: nome da função + ponteiro para o próximo
typedef struct No {
    char nome[50];
    struct No *prox;
} No;

// Protótipos
No *no_criar(char *nome);
void push(No **topo, char *nome);
int pop(No **topo, char *nome);
int peek(No *topo, char *nome);
void imprimir(No *topo);
void destruir_lista(No **topo);

int main(void) {
    char v[50];
    char op;
    int num;
    No *topo = NULL;

    do {
        printf("C <funcao> - Chamar funcao\n");
        printf("R <valor>  - Retornar da funcao atual\n");
        printf("P          - Imprimir pilha de chamadas\n");
        printf("Q          - Sair\n");
        printf("Operacao: ");
        scanf(" %c", &op);
        getchar();   // consome o '\n' deixado pelo scanf

        switch (op) {
        case 'C':
            // Lê o nome da função e empilha um frame
            fgets(v, sizeof(v), stdin);
            int j = 0;
            while (v[j] != '\n' && v[j] != '\0') j++;
            v[j] = '\0';
            push(&topo, v);
            break;

        case 'R':
            // Lê o valor de retorno e desempilha o frame do topo.
            // O valor é o que o usuário digitou no comando R;
            // o frame só guarda o nome da função.
            scanf("%d", &num);
            getchar();
            if (pop(&topo, v))
                printf("Retornando de %s com valor %d\n", v, num);
            else
                printf("Nenhuma funcao para retornar\n");
            break;

        case 'P':
            imprimir(topo);
            break;

        case 'Q':
            printf("Saindo...\n");
            break;

        default:
            break;
        }
    } while (op != 'Q');

    destruir_lista(&topo);
    return 0;
}

// Aloca um nó com nome e prox = NULL
No *no_criar(char *nome) {
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL) return NULL;

    strcpy(novo->nome, nome);
    novo->prox = NULL;

    return novo;
}

// Empilha: insere um novo frame no TOPO da pilha de chamadas
void push(No **topo, char *nome) {
    No *novo = no_criar(nome);
    if (novo == NULL) return;

    novo->prox = *topo;
    *topo = novo;
}

// Desempilha: remove o frame do TOPO e copia o nome para 'nome'.
// Retorna 1 se sucesso, 0 se a pilha estiver vazia.
int pop(No **topo, char *nome) {
    if (topo == NULL || *topo == NULL) return 0;

    No *atual = *topo;
    strcpy(nome, atual->nome);
    *topo = atual->prox;
    free(atual);

    return 1;
}

// Espia o TOPO: copia o nome sem remover.
int peek(No *topo, char *nome) {
    if (topo == NULL) return 0;

    strcpy(nome, topo->nome);
    return 1;
}

// Imprime a pilha de chamadas do TOPO até a BASE no formato [a,b,c]
void imprimir(No *topo) {
    No *atual = topo;
    if (atual == NULL) {
        printf("PILHA VAZIA\n");
        return;
    }

    printf("[");
    while (atual != NULL) {
        printf("%s", atual->nome);
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