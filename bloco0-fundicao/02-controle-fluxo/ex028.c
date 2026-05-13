// 028 — O Eco Múltiplo
// Lê 5 inteiros e imprime o dobro de cada um.
// Fluxo controlado exclusivamente por if e goto (sem for, while, do-while).
#include <stdio.h>

int main(void) {
    int num;
    int contador = 0;

ler:
    if (contador == 5) {
        return 0;           // fim: 5 números já processados
    }
    scanf("%d", &num);
    printf("%d\n", num * 2);
    contador++;
    goto ler;               // volta para o label 'ler'
}