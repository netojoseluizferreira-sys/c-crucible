// 063 — strcmp Recriada (Strings)
// Implementa a função meu_strcmp() que compara duas strings lexicograficamente.
// Retorna 0 se forem iguais, negativo se a primeira for menor,
// positivo se a primeira for maior. Proibido usar <string.h>.
// A leitura e a impressão ficam em main.
#include <stdio.h>

int meu_strcmp(char *str1, char *str2);

int main(void) {
    char string1[100], string2[100];

    scanf("%s %s", string1, string2);

    int cmp = meu_strcmp(string1, string2);

    if (cmp < 0) printf("Primeira menor\n");
    else if (cmp == 0) printf("Iguais\n");
    else printf("Primeira maior\n");

    return 0;
}

// Compara duas strings lexicograficamente (ordem do dicionário)
int meu_strcmp(char *str1, char *str2) {
    int i = 0;

    // Percorre ambas as strings enquanto os caracteres forem iguais
    while (str1[i] != '\0' && str2[i] != '\0' && str1[i] == str2[i]) {
        i++;
    }

    // Retorna a diferença entre os primeiros caracteres diferentes
    // Se uma string terminou, a diferença será negativa ou positiva
    return (unsigned char)str1[i] - (unsigned char)str2[i];
}
