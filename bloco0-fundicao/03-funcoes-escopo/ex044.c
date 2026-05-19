// 044 — Fibonacci Recursivo
// Calcula o n-ésimo termo da sequência de Fibonacci usando recursão.
// Caso base: F(0) = 0, F(1) = 1.
// Passo recursivo: F(n) = F(n-1) + F(n-2).
// A leitura e a impressão ficam em main.
//
// Atenção: esta implementação tem complexidade exponencial O(2^n).
// Cada chamada gera duas novas chamadas, criando uma árvore binária
// de recursão com muitas chamadas repetidas. Para n > 40, fica inviável.
// Soluções eficientes usam programação dinâmica ou iteração.
#include <stdio.h>

int fibonacci(int termos);

int main(void) {
    int termos;

    scanf("%d", &termos);

    printf("%d\n", fibonacci(termos));

    return 0;
}

int fibonacci(int termos) {
    // Caso base: F(0) = 0, F(1) = 1
    if (termos <= 1)
        return termos;

    // Passo recursivo: F(n) = F(n-1) + F(n-2)
    return fibonacci(termos - 1) + fibonacci(termos - 2);
}