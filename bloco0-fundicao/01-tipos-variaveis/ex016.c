// 16 — O Deslocador
// Multiplica o número por 8 usando shift left de 3 posições.
// Cada shift left equivale a multiplicar por 2.
// 3 shifts = 2³ = 8.
//
// Atenção: o overflow de inteiro com sinal é comportamento indefinido.
// Para entradas cujo valor * 8 exceda INT_MAX, o resultado é imprevisível.

#include <stdio.h>

int main(){
    int numero;

    scanf("%d", &numero);

    numero = (numero << 3);
    printf("%d", numero);

    return 0;
}