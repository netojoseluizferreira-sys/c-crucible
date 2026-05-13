// 10 — O Escultor de Números Negativos
// Exibe o valor absoluto de um inteiro.
// Se o número for negativo, inverte o sinal com o operador unário -.
// Caso contrário, mantém o valor original.
#include <stdio.h>

int main() {
    int numero;

    scanf("%d", &numero);

    // Se negativo, aplica - para tornar positivo
    if (numero < 0)
        printf("%d\n", -numero);
    else
        printf("%d\n", numero);

    return 0;
}