// 036 — O Dobro e o Triplo
// Duas funções independentes: dobro() e triplo().
// Cada uma recebe um valor double e retorna o resultado da operação.
// A leitura e a impressão ficam em main.
#include <stdio.h>

// Protótipos das funções (exigidos por -Wmissing-prototypes)
double dobro(double num);
double triplo(double num);

int main(void) {
    double valor;

    scanf("%lf", &valor);

    printf("%.0lf %.0lf\n", dobro(valor), triplo(valor));

    return 0;
}

double dobro(double num) {
    return num * 2.0;
}

double triplo(double num) {
    return num * 3.0;
}