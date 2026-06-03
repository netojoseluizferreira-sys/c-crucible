// 087 — O Fosso dos Casts Amaldiçoados (Casts Complexos)
// Lê um inteiro e imprime cada byte que o compõe em hexadecimal,
// um por um, percorrendo sizeof(int) bytes.
//
// Usa um ponteiro unsigned char* apontando para o endereço do inteiro
// (cast explícito) para acessar os bytes individuais.
//
// A ordem dos bytes revela o endianness da máquina:
// - Little-endian (ex: x86): bytes menos significativos primeiro
// - Big-endian: bytes mais significativos primeiro
//
// Type punning via ponteiros: interpretar a mesma região de memória
// como tipos diferentes. É poderoso, mas dependente de plataforma.
#include <stdio.h>

int main(void) {
    int numero;

    scanf("%d", &numero);

    int *ptr = &numero;

    // Cast para unsigned char* para acessar os bytes individuais
    unsigned char *bytes = (unsigned char *)ptr;

    // Percorre cada byte do inteiro
    for (size_t i = 0; i < sizeof(numero); i++) {
        printf("%02X ", bytes[i]);
    }
    printf("\n");

    return 0;
}