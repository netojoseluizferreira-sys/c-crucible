// 147 — Extrator de Trecho de Arquivo
// Extrai caracteres das posições A a B (1-indexadas) de um arquivo texto.
#include <stdio.h>

int main(void) {
    char nome_arquivo[100];
    int a, b;

    // Lê nome do arquivo e as posições A e B
    scanf("%s %d %d", nome_arquivo, &a, &b);

    // Abre o arquivo para leitura
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return 1;
    }

    // Posiciona o ponteiro na posição A (1-indexada → offset A-1)
    fseek(arquivo, (long)(a - 1), SEEK_SET);

    // Lê e imprime caracteres de A até B
    for (int i = a; i <= b; i++) {
        int caractere = fgetc(arquivo);
        if (caractere == EOF) {
            break;  // fim do arquivo antes de B
        }
        printf("%c", caractere);
    }
    printf("\n");

    fclose(arquivo);
    return 0;
}