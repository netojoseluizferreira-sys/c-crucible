// 057 — O Elemento Ausente (Array Unidimensional)
// Dado um array de tamanho N-1 contendo números de 1 a N (exceto um),
// encontra e imprime o número ausente.
// Estratégia: para cada número j de 1 a N, verifica se j está no array.
// Se não estiver, é o ausente.
#include <stdio.h>

int main(void) {
    int tam;

    // Lê N (tamanho original)
    if (scanf("%d", &tam) != 1) return 1;

    int numeros[tam - 1];  // array com N-1 elementos

    // Lê os N-1 elementos
    for (int i = 0; i < tam - 1; i++) {
        if (scanf("%d", &numeros[i]) != 1) return 1;
    }

    // Para cada j de 1 a N, verifica se está presente
    for (int j = 1; j <= tam; j++) {
        int encontrado = 0;

        for (int i = 0; i < tam - 1; i++) {
            if (numeros[i] == j) {
                encontrado = 1;
                break;  // achou, pode parar de procurar por j
            }
        }

        // Se j não foi encontrado, é o número ausente
        if (encontrado == 0) {
            printf("%d\n", j);
            break;  // encontrou o ausente, pode parar
        }
    }

    return 0;
}