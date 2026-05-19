// 046 — Potência Recursiva
// Calcula base^expoente usando recursão.
// Caso base: qualquer número elevado a 0 é 1. 1 elevado a qualquer coisa é 1.
// Passo recursivo: base * base^(expoente-1)
// A leitura e a impressão ficam em main.
#include <stdio.h>

int potencia(int base, int expoente);

int main(void) {
    int base, expoente;

    scanf("%d %d", &base, &expoente);

    printf("%d\n", potencia(base, expoente));

    return 0;
}

int potencia(int base, int expoente) {
    // Caso base: expoente 0 ou base 1 encerram a recursão
    if (base == 1 || expoente == 0)
        return 1;

    // Passo recursivo: reduz o expoente em 1 a cada chamada
    return base * potencia(base, expoente - 1);
}