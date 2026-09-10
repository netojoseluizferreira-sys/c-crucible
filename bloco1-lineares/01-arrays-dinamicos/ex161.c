// 161 — Mini Banco de Dados em Memória
// Sistema de cadastro usando Vector de structs.
// Comandos: I (inserir), L (listar), B (buscar por nome), R (remover por nome), Q (sair).
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    int idade;
    float nota;
} Pessoa;

typedef struct {
    Pessoa *base_dados;
    int tamanho;
    int capacidade;
} Vector;

// Protótipos
Vector *vector_criar(void);
void vetor_inserir(Vector **v, char *nome, int idade, float nota);
void vector_imprimir(const Vector *v);
void vector_liberar(Vector **v);
int buscar_por_nome(const Vector *v, const char *nome);
void remover_por_nome(Vector **v, const char *nome);

int main(void) {
    Vector *vetor = vector_criar();
    if (vetor == NULL) return 1;

    char op;
    do {
        scanf(" %c", &op);  // espaço antes para ignorar whitespace

        if (op == 'I') {
            // Inserir novo registro
            char nome[50];
            int idade;
            float nota;

            scanf("%s", nome);          // lê nome sem espaços
            scanf("%d %f", &idade, &nota);
            getchar();                  // consome o '\n'

            vetor_inserir(&vetor, nome, idade, nota);

        } else if (op == 'L') {
            // Listar todos os registros
            vector_imprimir(vetor);

        } else if (op == 'B') {
            // Buscar por nome
            char nome[50];
            scanf("%s", nome);
            getchar();

            int indice = buscar_por_nome(vetor, nome);
            if (indice != -1) {
                printf("indice: %d\n", indice);
                printf("Nome: %s, Idade: %d, Nota: %.1f\n",
                       vetor->base_dados[indice].nome,
                       vetor->base_dados[indice].idade,
                       vetor->base_dados[indice].nota);
            } else {
                printf("registro nao encontrado\n");
            }

        } else if (op == 'R') {
            // Remover por nome
            char nome[50];
            scanf("%s", nome);
            getchar();

            remover_por_nome(&vetor, nome);

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

    vetor->base_dados = (Pessoa *)malloc((size_t)vetor->capacidade * sizeof(Pessoa));
    if (vetor->base_dados == NULL) {
        free(vetor);
        return NULL;
    }
    return vetor;
}

// Insere um novo registro no final do vetor, realocando se necessário
void vetor_inserir(Vector **v, char *nome, int idade, float nota) {
    if (v == NULL || *v == NULL) return;

    // Se o vetor está cheio, dobra a capacidade
    if ((*v)->tamanho >= (*v)->capacidade) {
        int nova_cap = (*v)->capacidade * 2;
        Pessoa *temp = (Pessoa *)realloc((*v)->base_dados, (size_t)nova_cap * sizeof(Pessoa));
        if (temp == NULL) return;  // falha na realocação, mantém estado atual

        (*v)->base_dados = temp;
        (*v)->capacidade = nova_cap;
    }

    // Copia os dados para a posição correspondente
    strcpy((*v)->base_dados[(*v)->tamanho].nome, nome);
    (*v)->base_dados[(*v)->tamanho].idade = idade;
    (*v)->base_dados[(*v)->tamanho].nota = nota;
    (*v)->tamanho++;
}

// Imprime todos os registros do vetor
void vector_imprimir(const Vector *v) {
    if (v == NULL) return;

    for (int i = 0; i < v->tamanho; i++) {
        printf("[%d] %s %d %.1f\n",
               i,
               v->base_dados[i].nome,
               v->base_dados[i].idade,
               v->base_dados[i].nota);
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

// Busca por nome, retorna o índice da primeira ocorrência ou -1
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
            // Desloca os elementos seguintes uma posição para a esquerda
            for (int j = i; j < (*v)->tamanho - 1; j++) {
                (*v)->base_dados[j] = (*v)->base_dados[j + 1];
            }
            (*v)->tamanho--;
            i--;  // verifica se o próximo elemento também é igual
            removidos++;
        }
    }

    if (removidos > 0) {
        printf("registro(s) removido(s): %d\n", removidos);
    } else {
        printf("registro nao encontrado\n");
    }
}