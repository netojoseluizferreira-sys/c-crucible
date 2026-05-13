// 07 — O Trocador de Temperatura
// Converte uma temperatura de Celsius para Fahrenheit.
// Fórmula: F = C × 9/5 + 32.
#include <stdio.h>

int main() {
    double celsius;

    scanf("%lf", &celsius);

    double fahrenheit = celsius * 9.0 / 5.0 + 32.0;

    printf("%.1lfF\n", fahrenheit);

    return 0;
}