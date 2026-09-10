// 152 — Inserção Ordenada com Contagem
// Insere valores em ordem crescente, contando quantos deslocamentos
// foram necessários. Demonstra inserção ordenada em array dinâmico.
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *array;
    int tamanho;
    int capacidade;
    int deslocamentos;
} Vector;

Vector *vector_criar(void);
void vetor_inserir_ordenado(Vector **v, int num);
void vector_imprimir(const Vector *v);
void vector_liberar(Vector **v);

int main(void) {
    Vector *vetor = vector_criar();
    if (vetor == NULL) return 1;

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int num;
        scanf("%d", &num);
        vetor_inserir_ordenado(&vetor, num);
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
    vetor->deslocamentos = 0;

    vetor->array = (int *)calloc((size_t)vetor->capacidade, sizeof(int));
    if (vetor->array == NULL) {
        free(vetor);
        return NULL;
    }
    return vetor;
}

void vetor_inserir_ordenado(Vector **v, int num) {
    if (v == NULL || *v == NULL) return;

    // Realoca se necessário
    if ((*v)->tamanho >= (*v)->capacidade) {
        int nova_cap = (*v)->capacidade * 2;

        size_t tamanho_bytes = (size_t)nova_cap * sizeof(int);
        int *temp = (int *)realloc((*v)->array, tamanho_bytes);
        if (temp == NULL) return;

        (*v)->array = temp;
        (*v)->capacidade = nova_cap;
    }

    // Encontra a posição correta e desloca os maiores para a direita
    int i = (*v)->tamanho - 1;

    while (i >= 0 && (*v)->array[i] > num) {
        (*v)->array[i + 1] = (*v)->array[i];
        (*v)->deslocamentos++;
        i--;
    }

    // Insere o novo valor na posição correta
    (*v)->array[i + 1] = num;
    (*v)->tamanho++;
}

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

void vector_liberar(Vector **v) {
    if (v == NULL || *v == NULL) return;
    free((*v)->array);
    (*v)->array = NULL;
    free(*v);
    *v = NULL;
}

/*
 * Análise de Complexidade:
 * 
 * vetor_inserir_ordenado:
 *   - Pior caso: O(n) — quando o valor é o menor, desloca todos
 *   - Caso médio: O(n/2) = O(n) — desloca metade
 *   - Melhor caso: O(1) — quando o valor é o maior, não desloca nada
 * 
 * Realocação: O(n) no pior caso, O(1) amortizado
 * 
 * A realocação dobrando a capacidade garante que o custo total
 * de N inserções seja O(n), não O(n²).
 */