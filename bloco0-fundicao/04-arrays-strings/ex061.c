// 061 — strlen Recriada (Strings)
// Implementa a função meu_strlen() que recebe uma string (array de char)
// e retorna seu comprimento. Proibido usar qualquer função da <string.h>.
// A leitura e a impressão ficam em main.
#include <stdio.h>

int meu_strlen(char string[]);

int main(void) {
    char string[100];

    scanf("%s", string);

    printf("%d\n", meu_strlen(string));

    return 0;
}

// Calcula o comprimento da string contando caracteres até encontrar '\0'
int meu_strlen(char string[]) {
    int tam = 0;

    // Percorre a string até o terminador nulo
    for (int i = 0; i < 100; i++) {
        if (string[i] == '\0') {
            break;  // fim da string
        }
        tam++;
    }

    return tam;
}
