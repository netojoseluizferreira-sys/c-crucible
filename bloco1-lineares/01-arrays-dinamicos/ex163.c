// 163 — Intercalação de Dois Vetores
// Lê dois vetores, intercala seus elementos em um terceiro vetor
// e imprime o resultado. Demonstra alocação dinâmica de novo vetor
// e controle de múltiplos índices simultâneos.
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *array;
    int tamanho;
    int capacidade;
} Vector;

Vector *vector_criar(void);
void vetor_inserir_final(Vector **v, int num);
void vector_imprimir(const Vector *v);
void vector_liberar(Vector **v);
int *merge(Vector **v, Vector **v2);

int main(void) {
    // Cria os dois vetores de entrada
    Vector *vetor = vector_criar();
    Vector *vetor2 = vector_criar();
    if (vetor == NULL || vetor2 == NULL) return 1;

    int n, m, num;
    if (scanf("%d %d", &n, &m) != 2) return 1;

    // Lê os N elementos do primeiro vetor
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &num) == 1) {
            vetor_inserir_final(&vetor, num);
        }
    }

    // Lê os M elementos do segundo vetor
    for (int i = 0; i < m; i++) {
        if (scanf("%d", &num) == 1) {
            vetor_inserir_final(&vetor2, num);
        }
    }

    // Cria o vetor que vai receber o resultado intercalado
    Vector *juntos = vector_criar();
    if (juntos == NULL) return 1;

    // Libera o array inicial do vetor de resultado (capacidade 2)
    // para substituí-lo pelo array retornado por merge
    free(juntos->array);

    // Chama o merge e verifica se a alocação foi bem-sucedida
    juntos->array = merge(&vetor, &vetor2);
    if (juntos->array == NULL) {
        // Se o merge falhou, libera os vetores e encerra
        vector_liberar(&vetor);
        vector_liberar(&vetor2);
        free(juntos);
        return 1;
    }

    // Ajusta tamanho e capacidade do vetor resultado
    juntos->tamanho = vetor->tamanho + vetor2->tamanho;
    juntos->capacidade = juntos->tamanho;

    vector_imprimir(juntos);

    // Libera toda a memória
    vector_liberar(&vetor);
    vector_liberar(&vetor2);
    vector_liberar(&juntos);
    return 0;
}

// Cria um vetor vazio com capacidade inicial 2
Vector *vector_criar(void) {
    Vector *vetor = (Vector *)malloc(sizeof(Vector));
    if (vetor == NULL) return NULL;

    vetor->tamanho = 0;
    vetor->capacidade = 2;

    vetor->array = (int *)calloc((size_t)vetor->capacidade, sizeof(int));
    if (vetor->array == NULL) {
        free(vetor);
        return NULL;
    }
    return vetor;
}

// Insere um número no final do vetor, realocando se necessário
void vetor_inserir_final(Vector **v, int num) {
    if (v == NULL || *v == NULL) return;

    // Se o vetor está cheio, dobra a capacidade
    if ((*v)->tamanho >= (*v)->capacidade) {
        int nova_cap = (*v)->capacidade * 2;
        size_t tamanho_bytes = (size_t)nova_cap * sizeof(int);
        int *temp = (int *)realloc((*v)->array, tamanho_bytes);
        if (temp == NULL) return;

        (*v)->array = temp;
        (*v)->capacidade = nova_cap;
    }

    // Escreve na próxima posição livre
    (*v)->array[(*v)->tamanho] = num;
    (*v)->tamanho++;
}

// Imprime o vetor no formato [a,b,c]
void vector_imprimir(const Vector *v) {
    if (v == NULL) return;

    printf("[");
    for (int i = 0; i < v->tamanho; i++) {
        printf("%d", v->array[i]);
        if (i < v->tamanho - 1) printf(",");
    }
    printf("]\n");
}

// Libera o array interno e a estrutura, evitando double free
void vector_liberar(Vector **v) {
    if (v == NULL || *v == NULL) return;
    free((*v)->array);
    (*v)->array = NULL;
    free(*v);
    *v = NULL;
}

// Intercala dois vetores em um novo array alocado dinamicamente
int *merge(Vector **v, Vector **v2) {
    int n = (*v)->tamanho;
    int m = (*v2)->tamanho;

    // Aloca um novo array com espaço para todos os elementos
    int *copy = (int *)malloc((size_t)(n + m) * sizeof(int));
    if (copy == NULL) return NULL;

    // Três índices: i percorre v, j percorre v2, k controla o novo array
    int i = 0, j = 0, k = 0;

    // Enquanto ambos tiverem elementos, alterna entre eles
    while (i < n && j < m) {
        copy[k++] = (*v)->array[i++];    // elemento do primeiro vetor
        copy[k++] = (*v2)->array[j++];   // elemento do segundo vetor
    }

    // Se o primeiro ainda tiver elementos, anexa o restante
    while (i < n) {
        copy[k++] = (*v)->array[i++];
    }

    // Se o segundo ainda tiver elementos, anexa o restante
    while (j < m) {
        copy[k++] = (*v2)->array[j++];
    }

    return copy;
}