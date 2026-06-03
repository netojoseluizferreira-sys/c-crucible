// 101 — A Transmutação de Tipos (Casts Avançados)
// Lê um número real do tipo float e imprime a representação inteira
// de seus bits, como se a mesma região de memória contivesse um inteiro.
//
// Utiliza a função memcpy para copiar os bytes do float para um
// unsigned int de forma segura e compatível com o padrão C.
// Essa técnica é uma alternativa ao "type punning" via ponteiros
// (que pode violar regras de aliasing) e é portável entre plataformas.
//
// A saída em hexadecimal revela a representação IEEE 754 do float.
#include <stdio.h>
#include <string.h>  // memcpy

int main(void) {
    float meu_float;

    scanf("%f", &meu_float);

    // Copia os bytes do float para um unsigned int de forma segura
    unsigned int bits_copiados;
    memcpy(&bits_copiados, &meu_float, sizeof(meu_float));

    // Imprime a representação hexadecimal dos bits do float
    printf("%X\n", bits_copiados);

    return 0;
}