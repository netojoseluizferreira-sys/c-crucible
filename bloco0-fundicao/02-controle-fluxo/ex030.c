// 030 — O Deslocador de Bits (Loop sem Corpo)
// Calcula quantos shifts left são necessários para que o valor ultrapasse 1000.
// O loop não possui corpo: todo o trabalho é feito no cabeçalho do for.
// n <<= 1 dobra o valor a cada iteração (multiplicação por 2).
// O loop para quando n > 1000, entregando o primeiro valor que excede o limite.
#include <stdio.h>

int main(void) {
    int n, shifts;

    scanf("%d", &n);

    // Corpo vazio: o incremento e a condição fazem todo o trabalho
    for (shifts = 0; n <= 1000; n <<= 1, shifts++);

    printf("%d shifts, %d\n", shifts, n);

    return 0;
}