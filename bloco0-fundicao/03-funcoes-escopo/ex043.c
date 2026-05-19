// 043 — Fatorial Recursivo
// Calcula o fatorial de um inteiro não-negativo usando recursão.
// Caso base: 0! = 1 e 1! = 1.
// Passo recursivo: n! = n * (n-1)!
// A leitura e a impressão ficam em main.
#include <stdio.h>

int fatorial(int num);

int main(void) {
    int numero;

    scanf("%d", &numero);
    printf("%d\n", fatorial(numero));

    return 0;
}

// Função recursiva: empilha chamadas até atingir o caso base
int fatorial(int num) {
    if (num <= 1)
        return 1;                    // caso base: interrompe a recursão
    return num * fatorial(num - 1);  // passo recursivo: reduz o problema
}