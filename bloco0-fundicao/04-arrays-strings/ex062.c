// 062 — strcpy Recriada (Strings)
// Implementa a função meu_strcpy() que copia o conteúdo da string
// de origem para a string de destino. Proibido usar <string.h>.
// A leitura e a impressão ficam em main.
#include <stdio.h>

void meu_strcpy(char origem[], char destino[]);

int main(void) {
    char origem[50], destino[50];

    scanf("%s", origem);

    meu_strcpy(origem, destino);

    printf("%s\n", destino);

    return 0;
}

// Copia a string de origem para destino, caractere por caractere,
// incluindo o '\0' final
void meu_strcpy(char origem[], char destino[]) {
    int i = 0;

    // Copia cada caractere até encontrar o terminador nulo
    while (origem[i] != '\0') {
        destino[i] = origem[i];
        i++;
    }
    destino[i] = '\0';
}