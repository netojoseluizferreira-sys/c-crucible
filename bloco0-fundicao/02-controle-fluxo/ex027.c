// 027 — O Mini-Calculador Infinito
// Lê continuamente dois números e um operador (+, -, *, /) e exibe o resultado.
// Se o operador for '/' e o divisor for 0, exibe "Divisao por zero".
// O programa só termina quando o operador for 'S' (maiúsculo).
#include <stdio.h>

int main(void) {
    float num1, num2, resultado;
    char operacao;

    // Loop infinito: só sai com 'S'
    while (1) {
        scanf("%f %c %f", &num1, &operacao, &num2);

        // Condição de parada
        if (operacao == 'S') {
            return 0;
        }

        // Operações aritméticas
        if (operacao == '+') {
            resultado = num1 + num2;
            printf("%.2f\n", resultado);
        } else if (operacao == '-') {
            resultado = num1 - num2;
            printf("%.2f\n", resultado);
        } else if (operacao == '*') {
            resultado = num1 * num2;
            printf("%.2f\n", resultado);
        } else if (operacao == '/') {
            // Proteção contra divisão por zero
            if (num2 == 0) {
                printf("Divisao por zero\n");
            } else {
                resultado = num1 / num2;
                printf("%.2f\n", resultado);
            }
        } else {
            printf("Operacao invalida\n");
        }
    }

    return 0;
}