// 100 — O Desafio do Mapa Múltiplo (Ponteiros para Arrays 2D)
// Lê uma matriz 3×3 de inteiros, calcula a soma de todos os elementos
// usando exclusivamente um ponteiro simples que percorre a matriz como
// um bloco contíguo de memória, sem usar [][] para acessar os elementos.
//
// A matriz 3×3 é tratada como um array unidimensional de 9 elementos,
// acessados via aritmética de ponteiros: (i * 3) + j.
#include <stdio.h>

int main(void) {
    int matriz[9], soma = 0;

    // Leitura e soma acumulada usando apenas aritmética de ponteiros
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            scanf("%d", matriz + (i * 3) + j);       // leitura via ponteiro
            soma += *(matriz + (i * 3) + j);         // acesso via ponteiro
        }
    }

    printf("%d\n", soma);

    return 0;
}