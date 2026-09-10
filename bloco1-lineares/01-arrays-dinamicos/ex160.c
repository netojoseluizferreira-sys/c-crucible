// 160 — Ordenação com Comparator
// Lê N Pessoas (nome, idade), armazena em um Vector e ordena por idade ou nome.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    int idade;
} Pessoa;

typedef struct {
    Pessoa *base_dados;
    int tamanho;
    int capacidade;
} Vector;

Vector *vector_criar(void);
void vetor_inserir(Vector **v, char *nome, int idade);
void vector_imprimir(const Vector *v);
void vector_liberar(Vector **v);
int compara_idade(const void *a, const void *b);
int compara_nome(const void *a, const void *b);

int main(void) {
    int n;
    char op;
    scanf("%d", &n);
    getchar();  // consome o '\n' após o número

    Vector *vetor = vector_criar();
    if (vetor == NULL) return 1;

    for (int i = 0; i < n; i++) {
        char nome[50];
        int idade;

        fgets(nome, sizeof(nome), stdin);
        size_t len = strlen(nome);
        if (nome[len - 1] == '\n') {
            nome[len - 1] = '\0';
        }

        scanf("%d", &idade);
        getchar();

        vetor_inserir(&vetor, nome, idade);
    }

    scanf(" %c", &op);

    if (op == 'i') {
        qsort(vetor->base_dados, (size_t)vetor->tamanho, sizeof(Pessoa), compara_idade);
    } else if (op == 'n') {
        qsort(vetor->base_dados, (size_t)vetor->tamanho, sizeof(Pessoa), compara_nome);
    } else {
        printf("ordenacao invalida.\n");
        vector_liberar(&vetor);
        return 1;
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

    vetor->base_dados = (Pessoa *)malloc((size_t)vetor->capacidade * sizeof(Pessoa));
    if (vetor->base_dados == NULL) {
        free(vetor);
        return NULL;
    }
    return vetor;
}

void vetor_inserir(Vector **v, char *nome, int idade) {
    if (v == NULL || *v == NULL) return;

    // Realoca se necessário
    if ((*v)->tamanho >= (*v)->capacidade) {
        int nova_cap = (*v)->capacidade * 2;
        Pessoa *temp = (Pessoa *)realloc((*v)->base_dados, (size_t)nova_cap * sizeof(Pessoa));
        if (temp == NULL) return;

        (*v)->base_dados = temp;
        (*v)->capacidade = nova_cap;
    }

    // Copia os dados diretamente para a posição correta
    strcpy((*v)->base_dados[(*v)->tamanho].nome, nome);
    (*v)->base_dados[(*v)->tamanho].idade = idade;
    (*v)->tamanho++;
}

void vector_imprimir(const Vector *v) {
    if (v == NULL) return;

    for (int i = 0; i < v->tamanho; i++) {
        printf("Nome: %s, Idade: %d\n",
               v->base_dados[i].nome,
               v->base_dados[i].idade);
    }
}

void vector_liberar(Vector **v) {
    if (v == NULL || *v == NULL) return;

    free((*v)->base_dados);
    (*v)->base_dados = NULL;
    free(*v);
    *v = NULL;
}

int compara_idade(const void *a, const void *b) {
    const Pessoa *p1 = (const Pessoa *)a;
    const Pessoa *p2 = (const Pessoa *)b;

    if (p1->idade < p2->idade) return -1;
    if (p1->idade > p2->idade) return 1;
    return 0;
}

int compara_nome(const void *a, const void *b) {
    const Pessoa *p1 = (const Pessoa *)a;
    const Pessoa *p2 = (const Pessoa *)b;

    int res_nome = strcmp((const char *)p1->nome, (const char *)p2->nome);
    
    if (res_nome != 0) {
        return res_nome;
    }
    
    if (p1->idade < p2->idade) return -1;
    if (p1->idade > p2->idade) return 1;
    return 0;
}
