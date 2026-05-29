#include <stdio.h>

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
    int tamanho = 0;
    while (*(palavra + tamanho) != '\0') {
        tamanho++;
    }

    for (int i = 0; i < tamanho / 2; i++) {
        if (*(palavra + i) != *(palavra + tamanho - 1 - i)) {
            return 0;
        }
    }
    return 1;
}