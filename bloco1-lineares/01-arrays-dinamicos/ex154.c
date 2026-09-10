// 154 — Mesclagem Inteligente
// Mescla dois vetores ordenados em um novo vetor, sem duplicatas.
// Demonstra merge de mergesort com remoção de duplicatas.
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *dados;
    int tamanho;
    int capacidade;
} Vector;

Vector *vector_criar(int capacidade);
void vector_liberar(Vector **v);
Vector *vector_merge(const Vector *v1, const Vector *v2);

int main(void) {
    size_t n1, n2;
    scanf("%zu %zu", &n1, &n2);

    // Cria os dois vetores com capacidade exata para os dados
    Vector *lista1 = vector_criar((int)n1);
    Vector *lista2 = vector_criar((int)n2);

    // Lê os valores do primeiro vetor
    for (size_t i = 0; i < n1; i++) {
        scanf("%d", &lista1->dados[i]);
        lista1->tamanho += 1;  // incrementa o tamanho a cada inserção
    }

    // Lê os valores do segundo vetor
    for (size_t i = 0; i < n2; i++) {
        scanf("%d", &lista2->dados[i]);
        lista2->tamanho += 1;
    }

    // Chama o merge — retorna um novo vetor ordenado e sem duplicatas
    Vector *resultado = vector_merge(lista1, lista2);

    // Imprime o vetor resultante
    printf("[");
    for (int i = 0; i < resultado->tamanho; i++) {
        printf("%d", resultado->dados[i]);
        if (i < resultado->tamanho - 1) printf(", ");
    }
    printf("]\n");

    // Libera todas as memórias alocadas
    vector_liberar(&lista1);
    vector_liberar(&lista2);
    vector_liberar(&resultado);

    return 0;
}

Vector *vector_criar(int capacidade) {
    // Aloca a struct Vector
    Vector *vetor = (Vector *)malloc(sizeof(Vector));
    if (vetor == NULL) return NULL;

    // Inicializa tamanho como 0 (vetor vazio) e capacidade como pedido
    vetor->tamanho = 0;
    vetor->capacidade = capacidade;

    // Aloca o array interno com calloc (tudo zerado)
    vetor->dados = (int *)calloc((size_t)capacidade, sizeof(int));
    if (vetor->dados == NULL) {
        free(vetor);  // se falhar, libera a struct e retorna NULL
        return NULL;
    }

    return vetor;
}

void vector_liberar(Vector **v) {
    // Proteção: se o ponteiro ou a struct já for NULL, não faz nada
    if (v == NULL || *v == NULL) return;

    // Libera o array interno e anula para evitar double free
    free((*v)->dados);
    (*v)->dados = NULL;

    // Libera a struct e anula o ponteiro
    free(*v);
    *v = NULL;
}

Vector *vector_merge(const Vector *v1, const Vector *v2) {
    // Capacidade máxima possível = soma dos tamanhos (pior caso sem duplicatas)
    int capacidade_max = v1->tamanho + v2->tamanho;
    Vector *resultado = vector_criar(capacidade_max);
    if (resultado == NULL) return NULL;

    // Índices: i percorre v1, j percorre v2, k controla o resultado
    int i = 0, j = 0, k = 0;

    // Enquanto houver elementos em AMBOS os vetores
    while (i < v1->tamanho && j < v2->tamanho) {
        if (v1->dados[i] < v2->dados[j]) {
            // v1 tem o menor valor
            // Só insere se não for duplicata do último já inserido
            if (k == 0 || resultado->dados[k - 1] != v1->dados[i]) {
                resultado->dados[k++] = v1->dados[i];
            }
            i++;  // avança no v1
        } else if (v2->dados[j] < v1->dados[i]) {
            // v2 tem o menor valor
            if (k == 0 || resultado->dados[k - 1] != v2->dados[j]) {
                resultado->dados[k++] = v2->dados[j];
            }
            j++;  // avança no v2
        } else {
            // São iguais: insere uma única vez e avança os DOIS
            if (k == 0 || resultado->dados[k - 1] != v1->dados[i]) {
                resultado->dados[k++] = v1->dados[i];
            }
            i++;
            j++;
        }
    }

    // Copia o restante de v1 (quando v2 acabou)
    while (i < v1->tamanho) {
        if (k == 0 || resultado->dados[k - 1] != v1->dados[i]) {
            resultado->dados[k++] = v1->dados[i];
        }
        i++;
    }

    // Copia o restante de v2 (quando v1 acabou)
    while (j < v2->tamanho) {
        if (k == 0 || resultado->dados[k - 1] != v2->dados[j]) {
            resultado->dados[k++] = v2->dados[j];
        }
        j++;
    }

    // Atualiza o tamanho real do resultado
    resultado->tamanho = k;
    return resultado;
}

/*
 * Análise de Complexidade:
 * 
 * vector_merge:
 *   - Tempo: O(n1 + n2) — percorre ambos uma única vez
 *   - Espaço: O(n1 + n2) — aloca novo vetor
 * 
 * Remoção de duplicatas: O(1) por elemento (verifica contra o último inserido)
 * 
 * A condição `resultado->dados[k - 1] != valor` só funciona porque
 * os vetores de entrada são ORDENADOS, então duplicatas ficam adjacentes.
 */