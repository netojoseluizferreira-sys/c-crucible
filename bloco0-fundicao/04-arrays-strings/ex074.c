// 074 — strstr Recriada (Strings)
// Implementa a função meu_strstr() que localiza a primeira ocorrência
// de uma substring dentro de uma string maior. Retorna o índice inicial
// ou -1 se não encontrada. Proibido usar <string.h>.
// A leitura e a impressão ficam em main.
#include <stdio.h>

int meu_strstr(char *str, char *str2);

int main(void) {
    char string[50], string2[50];

    scanf("%s", string);
    scanf("%s", string2);

    printf("%d\n", meu_strstr(string, string2));

    return 0;
}

// Retorna o índice da primeira ocorrência de str2 em str, ou -1
int meu_strstr(char *str, char *str2) {
    // Calcula o comprimento da substring (str2)
    int tam = 0;
    while (str2[tam] != '\0') {
        tam++;
    }

    // Se a substring for vazia, retorna 0 (por convenção)
    if (tam == 0) {
        return 0;
    }

    // Percorre a string principal
    for (int i = 0; str[i] != '\0'; i++) {
        // Se o primeiro caractere bate, verifica o restante
        if (str[i] == str2[0]) {
            int match = 1;  // assume que vai casar

            for (int k = 0; k < tam; k++) {
                // Verifica se chegou ao fim da string principal antes do fim da substring
                if (str[i + k] == '\0') {
                    match = 0;
                    break;
                }
                if (str[i + k] != str2[k]) {
                    match = 0;
                    break;
                }
            }

            if (match) {
                return i;  // encontrou, retorna o índice inicial
            }
        }
    }

    return -1;  // não encontrou
}