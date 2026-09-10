// 165 — Cadastro de Alunos com Busca e Ordenação
// Sistema de cadastro usando Vector de structs.
// Comandos: I (inserir), L (listar), B (buscar por nome),
//           R (remover por nome), O (ordenar por nome), Q (sair).
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    int matricula;
} Aluno;

typedef struct {
    Aluno *base_dados;
    int tamanho;
    int capacidade;
} Vector;

// Protótipos
Vector *vector_criar(void);
void vetor_inserir(Vector **v, char *nome, int matricula);
void vector_imprimir(const Vector *v);
void vector_liberar(Vector **v);
int buscar_por_nome(const Vector *v, const char *nome);
void remover_por_nome(Vector **v, const char *nome);
void quicksort(Aluno *lista, int inicio, int fim);

int main(void) {
    Vector *vetor = vector_criar();
    if (vetor == NULL) return 1;

    char op;
    do {
        scanf(" %c", &op);

        if (op == 'I') {
            // Inserir novo aluno
            char nome[50];
            int matricula;
            scanf("%s", nome);
            scanf("%d", &matricula);
            getchar();  // consome o '\n' deixado pelo scanf
            vetor_inserir(&vetor, nome, matricula);

        } else if (op == 'L') {
            // Listar todos os alunos cadastrados
            vector_imprimir(vetor);

        } else if (op == 'B') {
            // Buscar aluno por nome
            char nome[50];
            scanf("%s", nome);
            getchar();

            int indice = buscar_por_nome(vetor, nome);
            if (indice != -1) {
                printf("indice: %d\n", indice);
                printf("Nome: %s, Idade: %d\n",
                       vetor->base_dados[indice].nome,
                       vetor->base_dados[indice].matricula);
            } else {
                printf("registro nao encontrado\n");
            }

        } else if (op == 'R') {
            // Remover aluno(s) por nome
            char nome[50];
            scanf("%s", nome);
            getchar();
            remover_por_nome(&vetor, nome);

        } else if (op == 'O') {
            // Ordenar o vetor por nome (quicksort in-place)
            if (vetor->tamanho > 0)
                quicksort(vetor->base_dados, 0, vetor->tamanho - 1);

        } else if (op != 'Q') {
            printf("operacao invalida.\n");
        }

    } while (op != 'Q');

    vector_liberar(&vetor);
    return 0;
}

// Cria um vetor vazio com capacidade inicial 2
Vector *vector_criar(void) {
    Vector *vetor = (Vector *)malloc(sizeof(Vector));
    if (vetor == NULL) return NULL;

    vetor->tamanho = 0;
    vetor->capacidade = 2;

    vetor->base_dados = (Aluno *)malloc((size_t)vetor->capacidade * sizeof(Aluno));
    if (vetor->base_dados == NULL) {
        free(vetor);
        return NULL;
    }
    return vetor;
}

// Insere um novo aluno no final, realocando se necessário
void vetor_inserir(Vector **v, char *nome, int matricula) {
    if (v == NULL || *v == NULL) return;

    // Dobra a capacidade se estiver cheio
    if ((*v)->tamanho >= (*v)->capacidade) {
        int nova_cap = (*v)->capacidade * 2;
        Aluno *temp = (Aluno *)realloc((*v)->base_dados, (size_t)nova_cap * sizeof(Aluno));
        if (temp == NULL) return;

        (*v)->base_dados = temp;
        (*v)->capacidade = nova_cap;
    }

    // Copia nome e matrícula para a próxima posição livre
    strcpy((*v)->base_dados[(*v)->tamanho].nome, nome);
    (*v)->base_dados[(*v)->tamanho].matricula = matricula;
    (*v)->tamanho++;
}

// Imprime todos os registros no formato [i] nome matricula
void vector_imprimir(const Vector *v) {
    if (v == NULL) return;

    for (int i = 0; i < v->tamanho; i++) {
        printf("[%d] %s %d\n", i, v->base_dados[i].nome, v->base_dados[i].matricula);
    }
}

// Libera o array interno e a estrutura
void vector_liberar(Vector **v) {
    if (v == NULL || *v == NULL) return;

    free((*v)->base_dados);
    (*v)->base_dados = NULL;
    free(*v);
    *v = NULL;
}

// Busca linear por nome, retorna o índice ou -1
int buscar_por_nome(const Vector *v, const char *nome) {
    if (v == NULL) return -1;

    for (int i = 0; i < v->tamanho; i++) {
        if (strcmp(v->base_dados[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

// Remove todos os registros com o nome fornecido
void remover_por_nome(Vector **v, const char *nome) {
    if (v == NULL || *v == NULL) return;

    int removidos = 0;
    for (int i = 0; i < (*v)->tamanho; i++) {
        if (strcmp((*v)->base_dados[i].nome, nome) == 0) {
            // Desloca os seguintes uma posição para a esquerda
            for (int j = i; j < (*v)->tamanho - 1; j++) {
                (*v)->base_dados[j] = (*v)->base_dados[j + 1];
            }
            (*v)->tamanho--;
            i--;  // revalida a posição atual (pode haver outro com mesmo nome)
            removidos++;
        }
    }

    if (removidos > 0) {
        printf("registro(s) removido(s): %d\n", removidos);
    } else {
        printf("registro nao encontrado\n");
    }
}

// Quicksort in-place para ordenar por nome (ordem alfabética)
void quicksort(Aluno *lista, int inicio, int fim) {
    if (inicio >= fim)
        return;

    // Pivô copiado (struct), não como ponteiro para a posição
    Aluno pivo_aluno = lista[fim];
    int i = inicio - 1;
    Aluno aux;

    // Particiona: menores ou iguais ao pivô vão para a esquerda
    for (int j = inicio; j < fim; j++) {
        if (strcmp(lista[j].nome, pivo_aluno.nome) <= 0) {
            i++;
            aux = lista[i];
            lista[i] = lista[j];
            lista[j] = aux;
        }
    }

    // Coloca o pivô na posição correta
    aux = lista[fim];
    lista[fim] = lista[i + 1];
    lista[i + 1] = aux;

    int pivo_pos = i + 1;

    // Recursão nas duas metades
    quicksort(lista, inicio, pivo_pos - 1);
    quicksort(lista, pivo_pos + 1, fim);
}