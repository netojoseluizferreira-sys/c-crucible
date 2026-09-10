// 156 — Map e Transformação
// Aplica uma função a cada elemento do vetor.
// O callback recebe o valor e a operação desejada.
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *array;
    int tamanho;
    int capacidade;
} Vector;

Vector *vector_criar(void);
void vetor_inserir(Vector **v, int num);
void vector_imprimir(const Vector *v);
void vector_liberar(Vector **v);
void vector_map(Vector **v, int (*funcao)(int, char), char operacao);
int map(int num, char op);

int main(void) {
    char op;
    int n, num;

    // Lê a quantidade de números e a operação (ex: "4 d")
    scanf("%d %c", &n, &op);

    Vector *vetor = vector_criar();
    if (vetor == NULL) return 1;

    // Lê os n números e insere no vetor
    for (int i = 0; i < n; i++) {
        scanf("%d", &num);
        vetor_inserir(&vetor, num);
    }

    // Aplica a transformação escolhida em todos os elementos
    vector_map(&vetor, map, op);

    // Exibe o vetor transformado
    vector_imprimir(vetor);

    // Libera a memória
    vector_liberar(&vetor);
    return 0;
}

// Cria um vetor vazio com capacidade inicial 1
Vector *vector_criar(void) {
    Vector *vetor = (Vector *)malloc(sizeof(Vector));
    if (vetor == NULL) return NULL;

    vetor->tamanho = 0;
    vetor->capacidade = 1;

    // calloc inicia o array com zeros
    vetor->array = (int *)calloc((size_t)vetor->capacidade, sizeof(int));
    if (vetor->array == NULL) {
        free(vetor);
        return NULL;
    }
    return vetor;
}

// Insere um número no final do vetor, realocando se preciso
void vetor_inserir(Vector **v, int num) {
    if (v == NULL || *v == NULL) return;

    // Se o vetor está cheio, dobra a capacidade
    if ((*v)->tamanho >= (*v)->capacidade) {
        int nova_cap = (*v)->capacidade * 2;

        size_t tamanho_bytes = (size_t)nova_cap * sizeof(int);
        int *temp = (int *)realloc((*v)->array, tamanho_bytes);
        if (temp == NULL) return;  // se falhar, mantém o original

        (*v)->array = temp;
        (*v)->capacidade = nova_cap;
    }

    // Insere o valor na posição correspondente ao tamanho atual
    (*v)->array[(*v)->tamanho] = num;
    (*v)->tamanho++;
}

// Imprime o vetor no formato [a, b, c]
void vector_imprimir(const Vector *v) {
    if (v == NULL) return;

    printf("[");
    for (int i = 0; i < v->tamanho; i++) {
        printf("%d", v->array[i]);
        if (i < v->tamanho - 1) printf(", ");
    }
    printf("]\n");
}

// Libera o array interno e a estrutura
void vector_liberar(Vector **v) {
    if (v == NULL || *v == NULL) return;
    free((*v)->array);
    (*v)->array = NULL;  // evita double free
    free(*v);
    *v = NULL;
}

// Aplica a função callback a cada elemento do vetor (modificação in-place)
void vector_map(Vector **v, int (*funcao)(int, char), char operacao) {
    for (int i = 0; i < (*v)->tamanho; i++) {
        (*v)->array[i] = funcao((*v)->array[i], operacao);
    }
}

// Função de transformação: recebe um número e a operação (d/q/n)
int map(int num, char op) {
    if (op == 'd' || op == 'D') { 
        return num * 2;         // dobro
    }
    else if (op == 'q' || op == 'Q') { 
        return num * num;       // quadrado
    }
    else if (op == 'n' || op == 'N') {
        return num * (-1);      // negativo
    }
    else {
        return num;             // operação desconhecida: não altera
    }
}