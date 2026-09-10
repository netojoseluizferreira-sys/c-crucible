// 151 — O Vector Turbinado
// Cria um Vector, reserva capacidade N de uma vez e insere N valores.
// Demonstra a diferença entre tamanho (ocupados) e capacidade (disponíveis).
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *dados;
    int tamanho;
    int capacidade;
} Vector;

Vector *vector_criar(void);
void vector_reservar(Vector **v, int nova_capacidade);
void vector_liberar(Vector **v);

int main(void) {
    int n;
    scanf("%d", &n);

    Vector *vetor = vector_criar();
    if (vetor == NULL) {
        printf("Erro ao criar vector.\n");
        return 1;
    }

    vector_reservar(&vetor, n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &vetor->dados[i]);
        vetor->tamanho += 1;
    }

    printf("tamanho: %d\ncapacidade: %d\n", vetor->tamanho, vetor->capacidade);

    vector_liberar(&vetor);
    return 0;
}

Vector *vector_criar(void) {
    Vector *vetor = (Vector *)malloc(sizeof(Vector));
    if (vetor == NULL) return NULL;

    vetor->tamanho = 0;
    vetor->capacidade = 2;

    vetor->dados = (int *)calloc((size_t)vetor->capacidade, sizeof(int));
    if (vetor->dados == NULL) {
        free(vetor);
        return NULL;
    }

    return vetor;
}

void vector_reservar(Vector **v, int nova_capacidade) {
    if (nova_capacidade <= (*v)->capacidade) return;

    // Salva a capacidade antiga antes de atualizar
    int capacidade_antiga = (*v)->capacidade;

    // Tenta realocar PRIMEIRO (sem perder dados se falhar)
    int *temp = (int *)realloc((*v)->dados, (size_t)nova_capacidade * sizeof(int));
    if (temp == NULL) return;  // falhou, mantém estado original

    // Sucesso: atualiza ponteiro e capacidade
    (*v)->dados = temp;
    (*v)->capacidade = nova_capacidade;

    // Inicializa as novas posições com zero
    for (int i = capacidade_antiga; i < nova_capacidade; i++) {
        (*v)->dados[i] = 0;
    }
}

void vector_liberar(Vector **v) {
    if (v == NULL || *v == NULL) return;

    free((*v)->dados);
    (*v)->dados = NULL;
    free(*v);
    *v = NULL;
}

/*
 * Análise de Complexidade:
 * 
 * vector_criar: O(1) — aloca struct e array inicial
 * vector_reservar: O(n) — realoca e inicializa novas posições
 * vector_liberar: O(1) — libera array e struct
 * 
 * A reserva antecipada melhora o desempenho porque:
 * - Sem reserva: cada inserção pode realocar → O(n²) total
 * - Com reserva: realoca UMA vez → O(n) total
 */