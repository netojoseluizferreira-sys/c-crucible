// 042 — Área e Perímetro do Círculo
// Função void calcular_circulo() recebe o raio e dois ponteiros para double.
// Armazena a área e o perímetro nos endereços apontados.
// A leitura e a impressão ficam em main.
// Usa π = 3.14159.
#include <stdio.h>

void calcular_circulo(double raio, double *area, double *perimetro);

int main(void) {
    double raio, area, perimetro;

    scanf("%lf", &raio);

    calcular_circulo(raio, &area, &perimetro);

    printf("%.2lf %.2lf\n", area, perimetro);

    return 0;
}

void calcular_circulo(double raio, double *area, double *perimetro) {
    const double PI = 3.14159;
    *area = raio * raio * PI;
    *perimetro = 2.0 * raio * PI;
}