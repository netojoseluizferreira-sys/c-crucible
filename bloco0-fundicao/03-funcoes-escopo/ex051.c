// 051 — Conversão de Temperatura (Função com switch)
// Função void converter_temperatura() recebe um valor, uma escala de origem
// ('C' ou 'F') e um ponteiro para armazenar o resultado convertido.
// A leitura e a validação da escala ficam em main.
// A função usa switch para mapear as escalas.
#include <stdio.h>

void converter_temperatura(double temperatura, char tipo, double *resultado);

int main(void) {
    double temperatura, resultado = 0.0;
    char tipo;

    scanf("%lf %c", &temperatura, &tipo);

    // Valida a escala antes de chamar a função
    if (tipo == 'C' || tipo == 'F') {
        converter_temperatura(temperatura, tipo, &resultado);
        printf("%.2lf\n", resultado);
        return 0;
    } else {
        printf("Inválido\n");
        return 1;
    }
}

void converter_temperatura(double temperatura, char tipo, double *resultado) {
    *resultado = 0.0;  // inicializa o ponteiro de saída

    // Switch para mapear as escalas
    switch (tipo) {
        case 'F':
            // Fahrenheit → Celsius: C = (F - 32) × 5/9
            *resultado = (temperatura - 32.0) * (5.0 / 9.0);
            break;
        case 'C':
            // Celsius → Fahrenheit: F = C × 9/5 + 32
            *resultado = temperatura * (9.0 / 5.0) + 32.0;
            break;
        // default não é necessário: main já validou a escala
    }
}