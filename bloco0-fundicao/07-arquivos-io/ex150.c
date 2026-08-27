// 150 — Frequência de Caracteres em Arquivo
// Conta quantas vezes cada caractere ASCII (0-127) aparece no arquivo.
#include <stdio.h>

int main(void) {
    char nome_arquivo[100];
    scanf("%s", nome_arquivo);

    // Abre o arquivo para leitura
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return 1;
    }

    // Array de 128 inteiros para contar frequências (ASCII 0-127)
    int frequencias[128] = {0};

    // Lê cada caractere e incrementa a contagem
    int caractere;
    while ((caractere = fgetc(arquivo)) != EOF) {
        if (caractere >= 0 && caractere < 128) {
            frequencias[caractere]++;
        }
    }

    fclose(arquivo);

    // Imprime apenas os caracteres que apareceram
    for (int i = 0; i < 128; i++) {
        if (frequencias[i] > 0) {
            printf("'%c': %d\n", i, frequencias[i]);
        }
    }

    return 0;
}