// 059 — O Quadrado Mágico (Array Multidimensional 3×3)
// Verifica se uma matriz 3×3 é um quadrado mágico: a soma de cada
// linha, cada coluna e as duas diagonais principais é a mesma.
// Esta versão usa laços e uma função modular para validação.
#include <stdio.h>

int quadrado_magico(int matriz[3][3]);

int main(void) {
    int matriz[3][3];

    // Leitura da matriz 3×3
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            scanf("%d", &matriz[i][j]);
        }
    }

    if (quadrado_magico(matriz))
        printf("Sim\n");
    else
        printf("Nao\n");

    return 0;
}

// Verifica se a matriz 3×3 é um quadrado mágico
int quadrado_magico(int matriz[3][3]) {
    // Soma de referência: primeira linha
    int soma_ref = 0;
    for (int j = 0; j < 3; j++) {
        soma_ref += matriz[0][j];
    }

    // Verifica as 3 linhas
    for (int i = 0; i < 3; i++) {
        int soma = 0;
        for (int j = 0; j < 3; j++) {
            soma += matriz[i][j];
        }
        if (soma != soma_ref) return 0;
    }

    // Verifica as 3 colunas
    for (int j = 0; j < 3; j++) {
        int soma = 0;
        for (int i = 0; i < 3; i++) {
            soma += matriz[i][j];
        }
        if (soma != soma_ref) return 0;
    }

    // Verifica a diagonal principal (i == j)
    int soma_diag = 0;
    for (int i = 0; i < 3; i++) {
        soma_diag += matriz[i][i];
    }
    if (soma_diag != soma_ref) return 0;

    // Verifica a diagonal secundária (i + j == 2)
    soma_diag = 0;
    for (int i = 0; i < 3; i++) {
        soma_diag += matriz[i][2 - i];
    }
    if (soma_diag != soma_ref) return 0;

    return 1;  // é quadrado mágico
}