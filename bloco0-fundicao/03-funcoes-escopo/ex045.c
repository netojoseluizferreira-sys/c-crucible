// 045 — Soma dos Dígitos (Recursivo)
// Calcula a soma dos dígitos de um inteiro positivo usando recursão.
// Caso base: se o número tem apenas um dígito (num < 10), retorna ele mesmo.
// Passo recursivo: último dígito (num % 10) + soma dos dígitos restantes (num / 10).
// A leitura e a impressão ficam em main.
#include <stdio.h>

int soma_digitos(int num);

int main(void) {
    int num;

    scanf("%d", &num);

    printf("%d\n", soma_digitos(num));

    return 0;
}

int soma_digitos(int num) {
    // Caso base: número com um único dígito
    if (num < 10)
        return num;

    // Último dígito + soma recursiva do restante
    return (num % 10) + soma_digitos(num / 10);
}