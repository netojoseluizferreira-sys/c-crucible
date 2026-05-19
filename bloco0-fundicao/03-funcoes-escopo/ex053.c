// 053 — Palíndromo de String (Função Iterativa)
// Verifica se uma string é um palíndromo (lida igual de frente para trás).
// Ignora diferenças entre maiúsculas e minúsculas.
// Retorna 1 se for palíndromo, 0 caso contrário.
// A leitura e a impressão ficam em main.
#include <stdio.h>
#include <ctype.h>   // para a função tolower()

int eh_palindromo(char *palavra);

int main(void) {
    char palavra[50];

    scanf("%s", palavra);

    if (eh_palindromo(palavra))
        printf("Sim\n");
    else
        printf("Nao\n");

    return 0;
}

int eh_palindromo(char *palavra) {
    // Calcula o comprimento da string
    int tamanho = 0;
    while (palavra[tamanho] != '\0') {
        tamanho++;
    }

    // Compara caracteres das pontas em direção ao centro
    for (int i = 0; i < tamanho / 2; i++) {
        // Converte ambos para minúscula antes de comparar
        if (tolower(palavra[i]) != tolower(palavra[tamanho - 1 - i])) {
            return 0;  // não é palíndromo
        }
    }
    return 1;  // é palíndromo
}