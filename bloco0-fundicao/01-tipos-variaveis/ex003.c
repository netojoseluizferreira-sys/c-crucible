// 03 — A Troca Silenciosa
// Permuta os valores de duas variáveis sem usar variável auxiliar.
//
// Algoritmo: utiliza soma e subtração para trocar os valores.
// ATENÇÃO: se a + b exceder INT_MAX (overflow), o comportamento é indefinido.
#include <stdio.h>

int main() {
    int a, b;

    scanf("%d %d", &a, &b);

    // Swap sem variável auxiliar: overflow em a+b é UB
    a = a + b;
    b = a - b;
    a = a - b;

    printf("%d %d\n", a, b);
    return 0;
}