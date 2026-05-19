// 052 — MDC Recursivo (Euclides)
// Calcula o Máximo Divisor Comum de dois inteiros positivos
// usando o algoritmo de Euclides recursivo.
// Caso base: MDC(a, 0) = a.
// Passo recursivo: MDC(a, b) = MDC(b, a % b).
// O resultado é armazenado na variável global 'resultado'.
#include <stdio.h>

void mdc(int a, int b);

int resultado;  // variável global para armazenar o MDC

int main(void) {
    int a, b;

    scanf("%d %d", &a, &b);

    mdc(a, b);
    printf("%d\n", resultado);

    return 0;
}

void mdc(int a, int b) {
    // Caso base: quando b é zero, a é o MDC
    if (b == 0) {
        resultado = a;
        return;
    }
    // Passo recursivo: MDC(b, a % b)
    mdc(b, a % b);
}