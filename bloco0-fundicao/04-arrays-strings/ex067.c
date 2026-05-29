// 067 — Inversão de String (String + Aritmética de Ponteiros)
// Lê uma string e inverte-a in-place (modificando o próprio array)
// usando apenas aritmética de ponteiros (sem []).
// A leitura e a impressão ficam em main.
#include <stdio.h>

void inverter(char *str);

int main(void) {
    char string[50];

    scanf("%s", string);

    inverter(string);

    printf("%s\n", string);

    return 0;
}

// Inverte a string in-place usando dois ponteiros
void inverter(char *str) {
    // Ponteiro para o início da string
    char *inicio = str;

    // Ponteiro para o final da string (último caractere antes do '\0')
    char *fim = str;
    while (*(fim + 1) != '\0') {
        fim++;
    }

    // Troca caracteres das pontas até os ponteiros se encontrarem
    while (inicio < fim) {
        // Swap usando variável temporária
        char temp = *inicio;
        *inicio = *fim;
        *fim = temp;

        inicio++;
        fim--;
    }
}