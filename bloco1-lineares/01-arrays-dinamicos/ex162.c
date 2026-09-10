// 162 — Inserção no Final vs Início
// Mede os deslocamentos ao inserir no final (zero) e no início (tamanho atual).
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *array;
    int tamanho;
    int capacidade;
    int deslocamentos;
} Vector;

Vector *vector_criar(void);
void vetor_inserir_final(Vector **v, int num);
void vetor_inserir_comeco(Vector **v, int num);
void vector_imprimir(const Vector *v);
void vector_liberar(Vector **v);

int main(void) {
    Vector *vetor = vector_criar();
    if (vetor == NULL) return 1;

    int n, num;
    scanf("%d", &n);

    // Lê N números e insere no final (não causa deslocamentos)
    for (int i = 0; i < n; i++) {
        scanf("%d", &num);
        vetor_inserir_final(&vetor, num);
    }

    // Lê mais um número e testa inserção no final e no início
    scanf("%d", &num);
    vetor_inserir_final(&vetor, num);   // sem deslocamento
    vetor_inserir_comeco(&vetor, num);  // desloca todos os elementos

    vector_imprimir(vetor);

    vector_liberar(&vetor);
    return 0;
}

// Cria um vetor vazio com capacidade inicial 2 e contador de deslocamentos zerado
Vector *vector_criar(void) {
    Vector *vetor = (Vector *)malloc(sizeof(Vector));
    if (vetor == NULL) return NULL;

    vetor->tamanho = 0;
    vetor->capacidade = 2;
    vetor->deslocamentos = 0;

    vetor->array = (int *)calloc((size_t)vetor->capacidade, sizeof(int));
    if (vetor->array == NULL) {
        free(vetor);
        return NULL;
    }
    return vetor;
}

// Insere no final: apenas escreve na próxima posição livre
void vetor_inserir_final(Vector **v, int num) {
    if (v == NULL || *v == NULL) return;

    // Realoca se necessário (dobra a capacidade)
    if ((*v)->tamanho >= (*v)->capacidade) {
        int nova_cap = (*v)->capacidade * 2;
        size_t tamanho_bytes = (size_t)nova_cap * sizeof(int);
        int *temp = (int *)realloc((*v)->array, tamanho_bytes);
        if (temp == NULL) return;

        (*v)->array = temp;
        (*v)->capacidade = nova_cap;
    }

    // Inserção no final: nenhum deslocamento
    (*v)->array[(*v)->tamanho] = num;
    (*v)->tamanho++;
}

// Insere no início: desloca todos os elementos uma posição para a direita
void vetor_inserir_comeco(Vector **v, int num) {
    if (v == NULL || *v == NULL) return;

    // Realoca se necessário (mesma lógica do final)
    if ((*v)->tamanho >= (*v)->capacidade) {
        int nova_cap = (*v)->capacidade * 2;
        size_t tamanho_bytes = (size_t)nova_cap * sizeof(int);
        int *temp = (int *)realloc((*v)->array, tamanho_bytes);
        if (temp == NULL) return;

        (*v)->array = temp;
        (*v)->capacidade = nova_cap;
    }

    // Desloca os elementos de trás para frente
    for (int i = (*v)->tamanho - 1; i >= 0; i--) {
        (*v)->array[i + 1] = (*v)->array[i];
    }

    // Conta quantos deslocamentos foram feitos
    (*v)->deslocamentos += (*v)->tamanho;

    // Coloca o novo valor na primeira posição
    (*v)->array[0] = num;
    (*v)->tamanho++;
}

// Imprime o vetor e o total de deslocamentos acumulados
void vector_imprimir(const Vector *v) {
    if (v == NULL) return;

    printf("[");
    for (int i = 0; i < v->tamanho; i++) {
        printf("%d", v->array[i]);
        if (i < v->tamanho - 1) printf(",");
    }
    printf("]\n");

    printf("deslocamentos: %d\n", v->deslocamentos);
}

// Libera o array interno e a estrutura
void vector_liberar(Vector **v) {
    if (v == NULL || *v == NULL) return;
    free((*v)->array);
    (*v)->array = NULL;
    free(*v);
    *v = NULL;
}