// 029 — O Aninhador Invertido
// Imprime um padrão numérico onde a linha i contém os números de 1 até i.
// Exemplo para N=3: 1 / 12 / 123

#include <stdio.h>

int main() {
    int limite;

    scanf("%d", &limite);

    // Loop externo: controla o número da linha (1 até limite)
    for (int i = 1; i <= limite; i++){

        // Loop interno: imprime os números de 1 até i na mesma linha
        for (int j = 1; j <= i; j++) printf("%d", j);
        printf("\n");
    }

    return 0;
}