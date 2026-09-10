// 155 — Busca Binária e Inserção Estratégica
// Insere valores em ordem crescente, usando busca binária para encontrar
// a posição correta e deslocando os elementos maiores para a direita.
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *array;
    int tamanho;
    int capacidade;
} Vector;

Vector *vector_criar(void);
void vetor_inserir_ordenado(Vector **v, int num);
void vector_imprimir(const Vector *v);
void vector_liberar(Vector **v);

int main(void) {
    int n, num;
    scanf("%d", &n);
    Vector *vetor = vector_criar();
    if (vetor == NULL) return 1;

    for (int i = 0; i < n; i++) {
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
    vetor->capacidade = 1;

    vetor->array = (int *)calloc((size_t)vetor->capacidade, sizeof(int));
    if (vetor->array == NULL) {
        free(vetor);
        return NULL;
    }
    return vetor;
}

void vetor_inserir_ordenado(Vector **v, int num) {
    if (v == NULL || *v == NULL) return;

    // Realoca se necessário (dobra a capacidade)
    if ((*v)->tamanho >= (*v)->capacidade) {
        int nova_cap = (*v)->capacidade * 2;

        size_t tamanho_bytes = (size_t)nova_cap * sizeof(int);
        int *temp = (int *)realloc((*v)->array, tamanho_bytes);
        if (temp == NULL) return;  // se falhar, mantém estado original

        (*v)->array = temp;
        (*v)->capacidade = nova_cap;
    }

    // Busca binária para encontrar a posição de inserção
    int low = 0;
    int high = (*v)->tamanho - 1;
    int mid;

    while (low <= high) {
        mid = (low + high) / 2;
        if ((*v)->array[mid] < num) {
            // num deve ficar à direita de mid
            low = mid + 1;
        } else {
            // num deve ficar à esquerda de mid (ou substituir)
            high = mid - 1;
        }
    }

    // 'low' agora é a posição onde num deve ser inserido

    // Desloca os elementos maiores para a direita (de trás para frente)
    for (int i = (*v)->tamanho - 1; i >= low; i--) {
        (*v)->array[i + 1] = (*v)->array[i];
    }

    // Insere o novo valor na posição correta
    (*v)->array[low] = num;
    (*v)->tamanho++;
}

void vector_imprimir(const Vector *v) {
    if (v == NULL) return;

    printf("[");
    for (int i = 0; i < v->tamanho; i++) {
        printf("%d", v->array[i]);
        if (i < v->tamanho - 1) printf(", ");
    }
    printf("]\n");
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
 *   - Busca binária: O(log n) — divide o espaço pela metade a cada passo
 *   - Deslocamento: O(n) — move os elementos maiores para a direita
 *   - Total: O(n) — o deslocamento domina a complexidade
 * 
 * A realocação dobrando a capacidade garante O(1) amortizado para as inserções.
 */