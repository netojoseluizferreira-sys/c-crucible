// 13 — O Promovedor de Tipos
// Demonstra promoção implícita de int para float na multiplicação.
// O cast explícito (float)inteiro documenta a intenção e evita warnings.

#include <stdio.h>

int main(){
    int inteiro;
    float real, resultado;

    scanf("%d %f", &inteiro, &real);

    // Promoção implícita: int é convertido para float antes da multiplicação
    resultado = real * (float)inteiro;

    printf("%.1f", resultado);

    return 0;
}