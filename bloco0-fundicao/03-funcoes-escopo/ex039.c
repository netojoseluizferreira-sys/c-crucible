// 039 — Inverter Sinal com Procedimento
// Função void inverter() recebe um ponteiro para inteiro e transforma
// o valor no seu oposto (negativo vira positivo e vice-versa).
// A leitura e a impressão ficam em main.
#include <stdio.h>

void inverter(int *p);

int main(void) {
    int num;

    scanf("%d", &num);

    inverter(&num);           // passa o endereço diretamente, sem variável auxiliar

    printf("%d\n", num);

    return 0;
}

void inverter(int *p) {
    *p = -*p;                 // operador unário - no valor apontado
}