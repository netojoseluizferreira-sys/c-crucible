// 072 — strchr Recriada (Strings)
// Implementa a função meu_strchr() que localiza a primeira ocorrência
// de um caractere numa string e retorna um ponteiro para ele,
// ou NULL se não encontrado. Proibido usar <string.h>.
// A leitura e a impressão ficam em main.
#include <stdio.h>

char *meu_strchr(char *str, int c);

int main(void) {
    char string[50], c;

    // Lê a string (sem espaços) e o caractere a ser buscado
    scanf("%s", string);
    scanf(" %c", &c);  // espaço antes de %c ignora o \n do buffer

    char *resultado = meu_strchr(string, (int)c);

    if (resultado != NULL) {
        printf("%s\n", resultado);  // imprime a substring a partir do caractere
    } else {
        printf("Nao encontrado\n");
    }

    return 0;
}

// Retorna ponteiro para a primeira ocorrência de c em str, ou NULL
char *meu_strchr(char *str, int c) {
    int i = 0;

    // Percorre a string até encontrar o caractere ou o fim
    while (str[i] != '\0') {
        if (str[i] == (char)c) {
            return &str[i];  // retorna o endereço da ocorrência
        }
        i++;
    }

    return NULL;  // não encontrado
}