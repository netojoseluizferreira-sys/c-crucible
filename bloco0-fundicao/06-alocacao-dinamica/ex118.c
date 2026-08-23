// 118 — O Primeiro Vazamento (Alocação e Liberação Correta)
// Lê N números reais, armazena-os em um array alocado dinamicamente,
// calcula a média aritmética, imprime com 2 casas decimais e libera
// toda a memória alocada. Toda a memória usada é alocada dinamicamente.
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    size_t n;

    scanf("%zu", &n);

    // Aloca array para n valores double
    double *p = (double *)malloc(n * sizeof(double));
    if (p == NULL) {
        return 1;
    }

    // Aloca um double para acumular a soma
    double *soma = (double *)malloc(sizeof(double));
    if (soma == NULL) {
        free(p);
        return 1;
    }

    *soma = 0.0;

    // Leitura dos n valores
    for (size_t i = 0; i < n; i++) {
        scanf("%lf", p + i);
    }

    // Acumula a soma
    for (size_t i = 0; i < n; i++) {
        *soma += *(p + i);
    }

    // Calcula a média (divisão por double)
    *soma /= (double)n;

    // Impressão com 2 casas decimais
    printf("%.2lf\n", *soma);

    // Libera toda a memória alocada
    free(p);
    free(soma);

    return 0;
}