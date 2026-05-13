// 08 — O Maquinador de Máscaras
// Verifica se o 3º bit (posição 3, considerando LSB = 0) está ligado.
// Estratégia: desloca o número 3 posições à direita e isola o LSB com & 1.
#include <stdio.h>

int main() {
    int numero;

    scanf("%d", &numero);

    // Shift right 3 + AND 1: isola o bit da posição 3
    if ((numero >> 3) & 1)
        printf("1\n");
    else
        printf("0\n");

    return 0;
}