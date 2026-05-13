// 05 — O Relojoeiro Binário
// Converte hora e minuto (0–23, 0–59) para uma representação binária decimal.
// Exemplo: 10 vira 1010 (impresso com 8 dígitos: 00001010).
//
// Algoritmo: extrai cada bit (LSB primeiro) e acumula em um número decimal
// onde cada casa decimal representa um bit visual.
// O fator posicional (1, 10, 100, ...) posiciona cada bit na casa correta.
#include <stdio.h>

int main() {
    long long bin_hora = 0, bin_minuto = 0;
    int hora, minuto;

    scanf("%d %d", &hora, &minuto);

    // Converte hora para binário decimal
    int temp = hora;
    int fator = 1;                     // posição decimal: 1, 10, 100, ...
    while (temp != 0) {
        int bit = temp % 2;           // extrai o LSB
        bin_hora += (long long)bit * fator;
        temp /= 2;                    // shift right lógico
        fator *= 10;                  // próxima casa decimal
    }

    // Converte minuto para binário decimal (mesmo algoritmo)
    temp = minuto;
    fator = 1;
    while (temp != 0) {
        int bit = temp % 2;
        bin_minuto += (long long)bit * fator;
        temp /= 2;
        fator *= 10;
    }

    // %08lld: 8 dígitos com zeros à esquerda
    printf("%08lld\n%08lld\n", bin_hora, bin_minuto);

    return 0;
}