// 11 — O Divisor de Contas
// Divide o valor total (em reais, float) igualmente entre um número de pessoas.
// Estratégia: converte o valor total para centavos (inteiro) para evitar
// imprecisões de ponto flutuante na divisão. Após a divisão inteira,
// converte de volta para reais com 2 casas decimais.
#include <stdio.h>

int main() {
    float dinheiro;
    int pessoas;

    scanf("%f %d", &dinheiro, &pessoas);

    // Converte reais para centavos: R$ 10.00 → 1000 centavos
    int centavos = (int)(dinheiro * 100.0f);

    // Divisão inteira dos centavos
    int valor_por_pessoa = centavos / pessoas;

    // Converte centavos de volta para reais com 2 casas decimais
    printf("%.2f\n", valor_por_pessoa / 100.0);

    return 0;
}