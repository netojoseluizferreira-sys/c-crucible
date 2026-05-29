// 066 — Contagem de Caracteres (String + Aritmética de Ponteiros)
// Lê uma string e um caractere. Conta quantas vezes o caractere
// aparece na string usando apenas aritmética de ponteiros (sem []).
// A leitura e a impressão ficam em main.
#include <stdio.h>

int meu_count(char *str, char letra);

int main(void) {
    char palavra[50], letra;

    scanf("%s", palavra);
    scanf(" %c", &letra);  // espaço antes do %c ignora o \n do buffer

    printf("%d\n", meu_count(palavra, letra));

    return 0;
}

// Conta ocorrências de 'letra' em 'str' usando apenas aritmética de ponteiros
int meu_count(char *str, char letra) {
    int cont = 0;
    int i = 0;

    // Percorre a string até encontrar '\0'
    while (*(str + i) != '\0') {
        if (*(str + i) == letra) {
            cont++;  // conta a ocorrência
        }
        i++;  // avança para o próximo caractere sempre
    }

    return cont;
}