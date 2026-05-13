// 14 — O Mascarado
// Isola os 4 bits menos significativos (LSB) usando máscara 0x0F (0000 1111).
// Todo bit acima do 3º é zerado; os 4 inferiores são preservados.

#include <stdio.h>

int main() {
    unsigned int resultado, numero;

    scanf("%u", &numero);

    // AND bit a bit com 0x0F: preserva apenas os 4 LSBs
    resultado = numero & 0x0F;

    printf("%u\n", resultado);

    return 0;
}
