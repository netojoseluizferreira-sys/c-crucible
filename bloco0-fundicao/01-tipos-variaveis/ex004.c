// 04 — O Raio do Círculo
// Calcula a área de um círculo: A = π × r².
// Utiliza π ≈ 3.14159 (precisão de 5 casas decimais).
#include <stdio.h>

int main(void) {
    double raio;
    const double PI = 3.14159;  // constante com precisão definida

    scanf("%lf", &raio);

    double area = raio * raio * PI;

    printf("%.2lf\n", area);

    return 0;
}