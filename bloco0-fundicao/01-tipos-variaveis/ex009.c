// 09 — O Contador de Estouro
// Demonstra o overflow natural de unsigned char (8 bits, 0–255).
// O incremento é aplicado e o resultado trunca para o intervalo [0, 255]
// automaticamente ao armazenar em unsigned char (módulo 256).
#include <stdio.h>

int main() {
    unsigned char inicial;
    int incremento;

    scanf("%hhu %d", &inicial, &incremento);

    // A soma pode exceder 255; o cast trunca para 8 bits (módulo 256)
    inicial = (unsigned char)(inicial + incremento);

    printf("%hhu\n", inicial);

    return 0;
}