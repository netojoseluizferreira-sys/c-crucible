// 06 — A Soma Misteriosa
// Lê dois caracteres '0'–'9' e exibe a soma de seus valores numéricos.
//
// ATENÇÃO: %c lê o caractere, não o número. Exemplo: '3' tem valor ASCII 51.
// A conversão de char para int não transforma '3' em 3; obtém-se o código ASCII.
// Para somar corretamente, é necessário subtrair '0' (48) de cada caractere.
#include <stdio.h>

int main() {
    char digito1, digito2;

    scanf("%c %c", &digito1, &digito2);

    // Converte caractere para valor numérico: '3' → 3
    int soma = (digito1 - '0') + (digito2 - '0');

    printf("%d\n", soma);

    return 0;
}