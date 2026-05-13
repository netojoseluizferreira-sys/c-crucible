// 026 — O Impressor Trapezoidal
// Imprime um padrão de asteriscos onde cada linha i tem i asteriscos,
// até o número N informado. Só executa se N for par.
//
// Se N for ímpar, exibe "N deve ser par" e encerra.
#include <stdio.h>

int main(void) {
    int num;

    scanf("%d", &num);

    // Apenas números pares produzem o padrão
    if (num % 2 == 0) {
        for (int i = 1; i <= num; i++) {
            // Imprime i asteriscos na linha atual
            for (int j = 0; j < i; j++) {
                printf("*");
            }
            printf("\n");
        }
    } else {
        printf("N deve ser par\n");
    }

    return 0;
}