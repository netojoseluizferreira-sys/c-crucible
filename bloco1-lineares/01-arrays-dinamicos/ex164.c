// 164 — Interseção e União de Vetores
// Lê dois vetores, calcula a interseção e a união (ambas sem duplicatas)
// e imprime os resultados. Usa callbacks para desacoplar a inserção.
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
void uniao(Vector **v, Vector **v2, Vector **result, void (*insert)(Vector **, int));
void interseccao(Vector **v, Vector **v2, Vector **interc, void (*insert)(Vector **, int));

int main(void) {
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

    Vector *juntos = vector_criar();
    Vector *interc = vector_criar();
    if (juntos == NULL || interc == NULL) {
        vector_liberar(&vetor);
        vector_liberar(&vetor2);
        vector_liberar(&juntos);
        vector_liberar(&interc);
        return 1;
    }

    // Calcula união e interseção usando o mesmo callback de inserção
    uniao(&vetor, &vetor2, &juntos, vetor_inserir_final);
    interseccao(&vetor, &vetor2, &interc, vetor_inserir_final);

    // Imprime os resultados
    printf("Interseção: ");
    vector_imprimir(interc);
    printf("União: ");
    vector_imprimir(juntos);

    // Libera toda a memória
    vector_liberar(&vetor);
    vector_liberar(&vetor2);
    vector_liberar(&juntos);
    vector_liberar(&interc);
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

// Insere no final, realocando se necessário
void vetor_inserir_final(Vector **v, int num) {
    if (v == NULL || *v == NULL) return;

    if ((*v)->tamanho >= (*v)->capacidade) {
        int nova_cap = (*v)->capacidade * 2;
        size_t tamanho_bytes = (size_t)nova_cap * sizeof(int);
        int *temp = (int *)realloc((*v)->array, tamanho_bytes);
        if (temp == NULL) return;

        (*v)->array = temp;
        (*v)->capacidade = nova_cap;
    }

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

// Libera array e estrutura
void vector_liberar(Vector **v) {
    if (v == NULL || *v == NULL) return;
    free((*v)->array);
    (*v)->array = NULL;
    free(*v);
    *v = NULL;
}

// Calcula a união: todos os elementos, sem duplicatas
// Usa callback de inserção e verifica duplicatas comparando com o próprio result
void uniao(Vector **v, Vector **v2, Vector **result, void (*insert)(Vector **, int)) {
    // Adiciona elementos do primeiro vetor, verificando duplicatas no result
    for (int i = 0; i < (*v)->tamanho; i++) {
        int duplicado = 0;
        for (int k = 0; k < (*result)->tamanho; k++) {
            if ((*result)->array[k] == (*v)->array[i]) {
                duplicado = 1;
                break;
            }
        }
        if (!duplicado) {
            insert(result, (*v)->array[i]);
        }
    }

    // Adiciona elementos do segundo vetor, verificando duplicatas no result
    for (int i = 0; i < (*v2)->tamanho; i++) {
        int duplicado = 0;
        for (int k = 0; k < (*result)->tamanho; k++) {
            if ((*result)->array[k] == (*v2)->array[i]) {
                duplicado = 1;
                break;
            }
        }
        if (!duplicado) {
            insert(result, (*v2)->array[i]);
        }
    }
}

// Calcula a interseção: elementos comuns, sem duplicatas
// Usa callback de inserção e verifica duplicatas comparando com o próprio interc
void interseccao(Vector **v, Vector **v2, Vector **interc, void (*insert)(Vector **, int)) {
    for (int i = 0; i < (*v)->tamanho; i++) {
        for (int j = 0; j < (*v2)->tamanho; j++) {
            if ((*v)->array[i] == (*v2)->array[j]) {
                // Verifica se já está na interseção antes de inserir
                int duplicado = 0;
                for (int k = 0; k < (*interc)->tamanho; k++) {
                    if ((*interc)->array[k] == (*v)->array[i]) {
                        duplicado = 1;
                        break;
                    }
                }
                if (!duplicado) {
                    insert(interc, (*v)->array[i]);
                }
                break;
            }
        }
    }
}