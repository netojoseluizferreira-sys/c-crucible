// 01 — O Vendedor de Bits
// Calcula 2^potencia usando apenas multiplicações sucessivas.
// O tipo unsigned short (16 bits, 0–65535) comporta até 2^10 = 1024 sem overflow.
//
// Limitação: o enunciado pedia potências de 0 a 10; qualquer valor fora
// desse intervalo é truncado para os limites [0, 10].
#include <stdio.h>

int main() {
    unsigned short armazenamento = 1u;
    int potencia;

    scanf("%d", &potencia);

    // Força o intervalo válido [0, 10]
    if (potencia > 10) {
        potencia = 10;
    } else if (potencia < 0) {
        potencia = 0;
    }

    // Multiplica por 2 a cada iteração: 2^potencia
    while (potencia > 0) {
        armazenamento = (unsigned short)(armazenamento * 2u);
        potencia--;
    }

    printf("%huGB\n", armazenamento);

    return 0;
}