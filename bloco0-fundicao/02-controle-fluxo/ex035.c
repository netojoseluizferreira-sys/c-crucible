// 035 — O Tabulador Louco
// Imprime todas as combinações de i, j, k (1 a 3) cuja soma seja ímpar.
// Usa continue para pular as combinações de soma par.
// Usa break criativamente para sair do loop mais interno quando k > 3 (opcional).
#include <stdio.h>

int main(void) {
    int i, j, k, soma;

    for (i = 1; i <= 3; i++) {
        for (j = 1; j <= 3; j++) {
            for (k = 1; k <= 3; k++) {
                soma = i + j + k;

                // Pula combinações com soma par
                if (soma % 2 == 0) continue;

                printf("%d %d %d\n", i, j, k);
            }
        }
    }

    return 0;
}