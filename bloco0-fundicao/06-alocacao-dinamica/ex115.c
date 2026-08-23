// 115 — O Encolhimento do Abismo (realloc para Reduzir)
// Lê N inteiros para um array dinâmico, reduz-o para M elementos
// (M ≤ N) com realloc, preservando os primeiros M elementos.
// Demonstra o uso seguro de realloc para redução de tamanho.
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    size_t N, M;

    // Leitura do tamanho inicial
    scanf("%zu", &N);

    // Alocação dinâmica do array com N inteiros
    int *p = (int *)malloc(N * sizeof(int));

    if (p == NULL) {
        return 1;  // falha na alocação inicial
    }

    // Leitura dos N elementos usando aritmética de ponteiros
    for (size_t i = 0; i < N; i++) {
        scanf("%d", p + i);
    }

    // Leitura do novo tamanho M (M ≤ N, conforme enunciado)
    scanf("%zu", &M);

    // Redução do array com realloc (uso seguro com ponteiro temporário)
    int *temp = (int *)realloc(p, M * sizeof(int));

    if (temp == NULL && M > 0) {
        // Se realloc falhar, o bloco original ainda é válido
        free(p);
        return 1;  // falha na realocação
    }

    // Se M == 0, realloc pode retornar NULL (comportamento válido)
    if (M > 0) {
        p = temp;
    }

    // Impressão dos M primeiros elementos (preservados após a redução)
    for (size_t i = 0; i < M; i++) {
        printf("%d ", *(p + i));
    }
    printf("\n");

    // Liberação da memória
    free(p);

    return 0;
}