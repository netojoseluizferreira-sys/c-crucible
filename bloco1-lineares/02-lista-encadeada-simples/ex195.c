// 195 — Mini Sistema de Contatos
// Sistema de cadastro com lista encadeada simples.
// Cada contato tem nome (string) e telefone (int).
// Comandos: I (inserir), L (listar), B (buscar), R (remover), Q (sair).
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    char nome[50];
    int telefone;
    struct No *prox;
} No;

No *no_criar(char *nome, int telefone);
void inserir_final(No **cabeca, char *nome, int telefone);
void destruir_lista(No **cabeca);
void buscar(No *cabeca, char *alvo);
void remover_valor(No **cabeca, char *valor);
void imprimir(No *cabeca);
void trim_newline(char *str);

int main(void) {
    int telefone;
    char op;
    char nome[50];

    No *cabeca = NULL;

    do {
        // Mostra o menu
        printf("I: inserir no final\n");
        printf("L: listar todos\n");
        printf("B: buscar por nome\n");
        printf("R: remover por nome\n");
        printf("Q: sair\n");
        printf("ACAO: ");

        scanf(" %c", &op);
        getchar();  // consome o '\n' deixado pelo scanf

        // Normaliza para maiúscula
        if (op >= 'a' && op <= 'z') op -= 32;

        switch (op) {
            case 'I':
                // Inserir: lê nome e telefone
                printf("Nome: ");
                fgets(nome, sizeof(nome), stdin);
                trim_newline(nome);

                printf("Telefone: ");
                scanf("%d", &telefone);
                getchar();  // consome o '\n' deixado pelo scanf

                inserir_final(&cabeca, nome, telefone);
                break;

            case 'L':
                imprimir(cabeca);
                break;

            case 'B':
                // Buscar por nome
                printf("Nome: ");
                fgets(nome, sizeof(nome), stdin);
                trim_newline(nome);

                buscar(cabeca, nome);
                break;

            case 'R':
                // Remover por nome
                printf("Nome: ");
                fgets(nome, sizeof(nome), stdin);
                trim_newline(nome);

                remover_valor(&cabeca, nome);
                break;

            case 'Q':
                printf("DESLIGANDO...\n");
                destruir_lista(&cabeca);
                break;

            default:
                printf("OPCAO INEXISTENTE\n");
                break;
        }

    } while (op != 'Q');

    return 0;
}

// Aloca um novo nó com nome e telefone
No *no_criar(char *nome, int telefone) {
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL) return NULL;

    strcpy(novo->nome, nome);   // copia o nome para o campo
    novo->telefone = telefone;
    novo->prox = NULL;

    return novo;
}

// Insere no final
void inserir_final(No **cabeca, char *nome, int telefone) {
    No *novo = no_criar(nome, telefone);
    if (novo == NULL) return;

    if (*cabeca == NULL) {
        *cabeca = novo;
        return;
    }

    No *atual = *cabeca;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }

    atual->prox = novo;
}

// Libera toda a lista
void destruir_lista(No **cabeca) {
    if (cabeca == NULL || *cabeca == NULL) return;

    No *atual = *cabeca;
    while (atual != NULL) {
        No *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    *cabeca = NULL;
}

// Busca por nome e imprime o contato, ou mensagem de erro
// Usa strcmp para comparar strings (== compara endereços)
void buscar(No *cabeca, char *alvo) {
    No *atual = cabeca;

    while (atual != NULL) {
        if (strcmp(atual->nome, alvo) == 0) {
            printf("Nome: %s | Telefone: %d\n", atual->nome, atual->telefone);
            return;
        }
        atual = atual->prox;
    }

    printf("Nome nao encontrado\n");
}

// Remove TODAS as ocorrências de um nome
// Usa ponteiro duplo para remover sem variável "anterior"
// NÃO avança depois de remover: o próximo pode ter o mesmo nome
void remover_valor(No **cabeca, char *valor) {
    if (cabeca == NULL || *cabeca == NULL) return;

    No **atual = cabeca;

    while (*atual != NULL) {
        if (strcmp((*atual)->nome, valor) == 0) {
            No *remover = *atual;
            *atual = remover->prox;
            free(remover);
            // não avança
        } else {
            atual = &(*atual)->prox;
        }
    }
}

// Imprime todos os contatos
void imprimir(No *cabeca) {
    No *atual = cabeca;
    if (atual == NULL) {
        printf("LISTA VAZIA\n");
        return;
    }
    while (atual != NULL) {
        printf("Nome: %s | Telefone: %d\n", atual->nome, atual->telefone);
        atual = atual->prox;
    }
}

// Remove o '\n' do final da string lida com fgets
// (fgets inclui o '\n' se couber no buffer)
void trim_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}