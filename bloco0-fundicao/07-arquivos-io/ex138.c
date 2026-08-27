// 138 — Copiador de Arquivos (Texto)
// Copia o conteúdo de um arquivo de origem para um arquivo de destino.
// Demonstra abertura de dois arquivos simultaneamente e transferência
// de dados com fscanf e fprintf.
#include <stdio.h>

int main(void) {
    char aux[50];

    // Abre o arquivo de origem para leitura
    FILE *origem = fopen("origem.txt", "r");
    if (origem == NULL) {
        printf("Erro ao abrir arquivo de origem.\n");
        return 1;
    }

    // Lê o conteúdo da origem
    fscanf(origem, "%s", aux);
    fclose(origem);

    // Abre o arquivo de destino para escrita
    FILE *destino = fopen("destino.txt", "w");
    if (destino == NULL) {
        printf("Erro ao abrir arquivo de destino.\n");
        return 1;
    }

    // Grava o conteúdo lido no destino
    fprintf(destino, "%s", aux);
    fclose(destino);

    printf("Copia concluida.\n");

    return 0;
}