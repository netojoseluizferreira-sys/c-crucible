// 041 — Par ou Ímpar com Função
// Função eh_par() recebe um inteiro e imprime "Par" ou "Impar".
// Usa operador bitwise & para testar o LSB: se for 0, é par.
// A leitura fica em main, a impressão fica na função.
#include <stdio.h>

void eh_par(int num);

int main(void) {
    int valor;

    scanf("%d", &valor);

    eh_par(valor);

    return 0;
}

void eh_par(int num) {
    if ((num & 1) == 0)
        printf("Par\n");
    else
        printf("Impar\n");
}