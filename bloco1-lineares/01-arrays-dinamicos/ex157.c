// 157 — Reduce e Agregação
// Reduz o vetor a um único valor usando uma função callback.
// O callback decide a operação com base no caractere recebido.
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *array;
    int tamanho;
    int capacidade;
} Vector;

Vector *vector_criar(void);
void vetor_inserir(Vector **v, int num);
void vector_liberar(Vector **v);
void vector_reduce(Vector **v, int (*funcao)(int, int *, char), char operacao);
int reduce(int tam, int *v, char op);

int main(void) {
    char op;
    int n, num;

    // Lê a quantidade de números e a operação (ex: "4 +")
    scanf("%d %c", &n, &op);

    Vector *vetor = vector_criar();
    if (vetor == NULL) return 1;

    // Lê os n números e insere no vetor
    for (int i = 0; i < n; i++) {
        scanf("%d", &num);
        vetor_inserir(&vetor, num);
    }

    // Aplica a redução e imprime o resultado
    vector_reduce(&vetor, reduce, op);

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

// Insere um número no final do vetor, realocando se necessário
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

// Libera o array interno e a estrutura
void vector_liberar(Vector **v) {
    if (v == NULL || *v == NULL) return;
    free((*v)->array);
    (*v)->array = NULL;  // evita double free
    free(*v);
    *v = NULL;
}

// Aplica a redução e imprime o resultado formatado
void vector_reduce(Vector **v, int (*funcao)(int, int *, char), char operacao) {
    printf("\n'%c': %d\n", operacao, funcao((*v)->tamanho, (*v)->array, operacao));
}

// Função de agregação: recebe o tamanho, o array e a operação (+, *, m)
int reduce(int tam, int *v, char op) {
    int aux = 0;

    if (op == '+') { 
        // Soma todos os elementos
        for (int i = 0; i < tam; i++) {
            aux += v[i];
        }
        return aux;
    }
    else if (op == '*') { 
        // Produto de todos os elementos (inicia em 1)
        aux = 1;
        for (int i = 0; i < tam; i++) {
            aux *= v[i];
        }
        return aux;
    }
    else if (op == 'm' || op == 'M') {
        // Máximo: assume o primeiro e compara com os demais
        aux = v[0];
        for (int i = 1; i < tam; i++) {
            if (v[i] >= aux) {
                aux = v[i];
            }
        }
        return aux;
    }
    else {
        return aux;  // operação desconhecida: retorna 0
    }
}