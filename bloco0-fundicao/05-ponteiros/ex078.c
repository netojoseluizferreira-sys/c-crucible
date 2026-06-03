// 078 — O Cão de Guarda do Abismo (Arrays vs. Ponteiros)
// Demonstra a diferença entre um array e um ponteiro usando sizeof.
// sizeof(arr) retorna o tamanho total do array (5 * sizeof(int)).
// sizeof(p) retorna o tamanho de um ponteiro (8 bytes em 64 bits).
// sizeof(arr[0]) retorna o tamanho de um elemento (4 bytes para int).
//
// Mesmo que p = arr, sizeof(p) != sizeof(arr) porque o array carrega
// informação sobre seu tamanho total, enquanto o ponteiro é apenas
// um endereço de memória.
#include <stdio.h>

int main(void) {
    int arr[5] = {1, 2, 3, 4, 5};
    int *p = arr;

    // sizeof(arr): tamanho total do array (5 * 4 = 20 bytes)
    // sizeof(p):   tamanho de um ponteiro (8 bytes em arquitetura 64 bits)
    // sizeof(arr[0]): tamanho de um elemento int (4 bytes)
    printf("%llu\n%llu\n%llu\n", sizeof(arr), sizeof(p), sizeof(arr[0]));

    return 0;
}