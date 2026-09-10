// 159 — Vector de Registros
// Lê N registros (nome, idade, nota), armazena em um Vector e imprime.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    int idade;
    float nota;
} Registro;

typedef struct {
    Registro *base_dados;
    int tamanho;
    int capacidade;
} Vector;

Vector *vector_criar(void);
void vetor_inserir(Vector **v, char *nome, int idade, float nota);
void vector_imprimir(const Vector *v);
void vector_liberar(Vector **v);

int main(void) {
    int n;
    scanf("%d", &n);
    getchar();  // consome o '\n' após o número

    Vector *vetor = vector_criar();
    if (vetor == NULL) return 1;

    for (int i = 0; i < n; i++) {
        char nome[50];
        int idade;
        float nota;

        fgets(nome, sizeof(nome), stdin);
        size_t len = strlen(nome);
        if (nome[len - 1] == '\n') {
            nome[len - 1] = '\0';
        }

        scanf("%d %f", &idade, &nota);
        getchar();  // consome o '\n' após a nota

        vetor_inserir(&vetor, nome, idade, nota);
    }

    vector_imprimir(vetor);
    vector_liberar(&vetor);
    return 0;
}

Vector *vector_criar(void) {
    Vector *vetor = (Vector *)malloc(sizeof(Vector));
    if (vetor == NULL) return NULL;

    vetor->tamanho = 0;
    vetor->capacidade = 2;

    vetor->base_dados = (Registro *)malloc((size_t)vetor->capacidade * sizeof(Registro));
    if (vetor->base_dados == NULL) {
        free(vetor);
        return NULL;
    }
    return vetor;
}

void vetor_inserir(Vector **v, char *nome, int idade, float nota) {
    if (v == NULL || *v == NULL) return;

    // Realoca se necessário
    if ((*v)->tamanho >= (*v)->capacidade) {
        int nova_cap = (*v)->capacidade * 2;
        Registro *temp = (Registro *)realloc((*v)->base_dados, (size_t)nova_cap * sizeof(Registro));
        if (temp == NULL) return;

        (*v)->base_dados = temp;
        (*v)->capacidade = nova_cap;
    }

    // Copia os dados diretamente para a posição correta
    strcpy((*v)->base_dados[(*v)->tamanho].nome, nome);
    (*v)->base_dados[(*v)->tamanho].idade = idade;
    (*v)->base_dados[(*v)->tamanho].nota = nota;
    (*v)->tamanho++;
}

void vector_imprimir(const Vector *v) {
    if (v == NULL) return;

    for (int i = 0; i < v->tamanho; i++) {
        printf("Nome: %s, Idade: %d, Nota: %.1f\n",
               v->base_dados[i].nome,
               v->base_dados[i].idade,
               v->base_dados[i].nota);
    }
}

void vector_liberar(Vector **v) {
    if (v == NULL || *v == NULL) return;

    free((*v)->base_dados);
    (*v)->base_dados = NULL;
    free(*v);
    *v = NULL;
}