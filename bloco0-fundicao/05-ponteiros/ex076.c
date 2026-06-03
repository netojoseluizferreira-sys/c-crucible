// 076 — A Fenda dos Endereços (Aritmética de Ponteiros)
// Lê N inteiros e calcula a soma de todos os elementos
// usando apenas aritmética de ponteiros (sem []).
#include <stdio.h>

int main(void) {
    int n, soma = 0;

    scanf("%d", &n);
    int arr[n];

    // Leitura e soma acumulada usando apenas aritmética de ponteiros
    for (int i = 0; i < n; i++) {
        scanf("%d", arr + i);       // leitura via ponteiro (sem [])
        soma += *(arr + i);         // acesso ao valor via ponteiro (sem [])
    }

    printf("%d\n", soma);

    return 0;
}