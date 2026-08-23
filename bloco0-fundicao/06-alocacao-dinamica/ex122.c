// 122 — A Tumba dos Heróis (Array de Ponteiros para Strings)
// Lê N strings e as armazena em um array dinâmico de ponteiros.
// Para cada string, aloca exatamente o espaço necessário (comprimento + 1),
// copia a string e armazena o ponteiro no array.
// Após a impressão, toda a memória é liberada.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char **p;
    size_t N;

    scanf("%zu", &N);

    // Aloca o array de ponteiros para N strings
    p = (char **)malloc(N * sizeof(char *));
    if (p == NULL) {
        return 1;
    }

    // Buffer temporário para leitura (tamanho máximo arbitrário)
    char temp[256];

    for (size_t i = 0; i < N; i++) {
        scanf("%255s", temp);  // limita a leitura ao tamanho do buffer

        // Aloca espaço exato para a string (comprimento + '\0')
        size_t len = strlen(temp);
        p[i] = (char *)malloc((len + 1) * sizeof(char));
        if (p[i] == NULL) {
            // Libera as strings já alocadas antes de encerrar
            for (size_t j = 0; j < i; j++) {
                free(p[j]);
            }
            free(p);
            return 1;
        }

        // Copia a string do buffer para a memória alocada
        strcpy(p[i], temp);
    }

    // Impressão das strings (uma por linha)
    for (size_t i = 0; i < N; i++) {
        printf("%s\n", *(p + i));
    }

    // Liberação de toda a memória
    for (size_t i = 0; i < N; i++) {
        free(p[i]);
    }
    free(p);

    return 0;
}