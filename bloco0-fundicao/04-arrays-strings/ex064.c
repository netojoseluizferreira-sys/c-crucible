// 064 — strcat Recriada (Strings)
// Implementa a função meu_strcat() que concatena a segunda string
// ao final da primeira. A primeira string deve ter espaço suficiente.
// Proibido usar <string.h>. A leitura e a impressão ficam em main.
#include <stdio.h>

void meu_strcat(char *str1, char *str2);
int meu_strlen(char *string);

int main(void) {
    char string1[100], string2[50];

    scanf("%s %s", string1, string2);

    meu_strcat(string1, string2);

    printf("%s\n", string1);

    return 0;
}

// Concatena str2 ao final de str1
void meu_strcat(char *str1, char *str2) {
    int tam1 = meu_strlen(str1);
    int tam2 = meu_strlen(str2);

    // Copia str2 para o final de str1
    for (int i = 0; i < tam2; i++) {
        str1[tam1 + i] = str2[i];
    }

    // Fecha a string concatenada com '\0'
    str1[tam1 + tam2] = '\0';
}

// Calcula o comprimento da string
int meu_strlen(char *string) {
    int tam = 0;

    for (int i = 0; i < 100; i++) {
        if (string[i] == '\0') {
            break;
        }
        tam++;
    }

    return tam;
}