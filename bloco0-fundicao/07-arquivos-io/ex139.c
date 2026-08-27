// 139 — Contador de Linhas
// Conta o número de linhas de um arquivo texto, considerando se a
// última linha termina ou não com '\n'. Demonstra leitura caractere
// a caractere com fgetc e rastreamento do último caractere lido.
#include <stdio.h>

int main(void) {
    FILE *arquivo = fopen("arquivo.txt", "r");
    int caractere;
    int linhas = 0;
    int ultimo_era_nova_linha = 1;  // assume arquivo vazio como 0 linhas

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    // Lê cada caractere e conta as quebras de linha
    while ((caractere = fgetc(arquivo)) != EOF) {
        if (caractere == '\n') {
            linhas++;
        }
        ultimo_era_nova_linha = (caractere == '\n');
    }

    // Corrige a contagem para a última linha sem '\n'
    if (!ultimo_era_nova_linha && linhas == 0) {
        linhas = 1;  // arquivo com conteúdo mas sem '\n'
    } else if (!ultimo_era_nova_linha) {
        linhas++;    // última linha sem '\n'
    }

    fclose(arquivo);

    printf("%d\n", linhas);
    return 0;
}