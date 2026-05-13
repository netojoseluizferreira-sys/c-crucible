// 021 — O Eco Silencioso
// Lê N números reais e imprime a raiz quadrada apenas dos não-negativos.
// Números negativos são ignorados (não produzem saída).
//
// Estratégia: método de Newton-Raphson para raiz quadrada.
// Aproximação iterativa: x = (x + n/x) / 2 até convergência.
// Casos especiais: 0 e 1 retornam o próprio número.
#include <stdio.h>

int main() {
    double n;
    int quantidades;

    scanf("%d", &quantidades);

    for (int i = 0; i < quantidades; i++) {
        scanf("%lf", &n);

        // Apenas não-negativos produzem saída; negativos são ignorados
        if (n > 0) {
            double x = n;           // estimativa inicial
            double y = 1.0;
            double epsilon = 0.000001;  // precisão desejada

            // Método de Newton-Raphson: converge quadraticamente
            while (x - y > epsilon) {
                x = (x + y) / 2.0;
                y = n / x;
            }

            printf("%.6lf\n", x);
        } else if (n == 0.0 || n == 1.0) {
            // Raiz de 0 é 0; raiz de 1 é 1
            printf("%.2lf\n", n);
        }
        // n < 0: não imprime nada (ignorado)
    }

    return 0;
}