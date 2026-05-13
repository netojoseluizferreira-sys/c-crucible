// 02 — O Construtor de Muralhas
// Calcula o volume de um paralelepípedo retangular.
// Fórmula: volume = largura × altura × profundidade.
#include <stdio.h>

int main() {
    double largura, altura, profundidade;

    scanf("%lf %lf %lf", &largura, &altura, &profundidade);

    double volume = largura * altura * profundidade;

    printf("%.2lfm3\n", volume);

    return 0;
}