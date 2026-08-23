// 114 — A Expansão do Domínio (realloc Básico)
// Lê N inteiros para um array dinâmico, expande-o para M elementos
// com realloc e preenche as novas posições com zeros.
// Demonstra o uso seguro de realloc com verificação e inicialização.
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

    // Leitura do novo tamanho M
    scanf("%zu", &M);

    // Expansão (ou redução) do array com realloc
    int *temp = (int *)realloc(p, M * sizeof(int));

    if (temp == NULL) {
        // Se realloc falhar, o bloco original ainda é válido
        free(p);
        return 1;  // falha na realocação
    }

    p = temp;

    // Inicializa as novas posições com zero (se M > N)
    for (size_t i = N; i < M; i++) {
        *(p + i) = 0;
    }

    // Impressão do array resultante usando aritmética de ponteiros
    for (size_t i = 0; i < M; i++) {
        printf("%d ", *(p + i));
    }
    printf("\n");

    // Liberação da memória
    free(p);

    return 0;
}