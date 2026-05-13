// 20 — O Bit Mais Significativo
// Encontra o MSB (Most Significant Bit) de um inteiro sem sinal de 32 bits.
// Retorna o valor decimal do MSB, não a posição.
//
// Algoritmo: desloca o número para a direita até que reste apenas 1.
// Conta quantos shifts foram necessários e depois usa 1 << posicao
// para reconstruir o valor do MSB.
//
// Exemplos:
//   10 (1010) → MSB é 8 (bit 3)
//   1  (0001) → MSB é 1 (bit 0)
//   255 (11111111) → MSB é 128 (bit 7)

#include <stdio.h>

int main() {
    unsigned int num;
    if (scanf("%u", &num) != 1) return 1;

    // Trata o caso especial: zero não tem nenhum bit ativo
    if (num == 0) {
        printf("Sem bits ativos (0)\n");
        return 0;
    }

    // Desloca até sobrar apenas o bit mais significativo = 1
    int posicao = 0;
    unsigned int temp = num;
    while (temp > 1) {
        temp >>= 1;
        posicao++;
    }

    // Reconstrói o valor do MSB: 1 deslocado para a posição encontrada
    printf("%u\n", 1U << posicao);
    return 0;
}
