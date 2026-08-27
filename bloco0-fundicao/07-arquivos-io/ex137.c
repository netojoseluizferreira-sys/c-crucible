// 137 — Leitor de Arquivo Texto
// Abre um arquivo para leitura, lê uma string e imprime na tela.
// Demonstra fopen com modo "r", fscanf e fclose.
#include <stdio.h>

int main(void) {
    char aux[50];

    // Abre o arquivo para leitura (modo "r")
    FILE *arquivo = fopen("entrada.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return 1;
    }

    // Lê uma string do arquivo
    fscanf(arquivo, "%s", aux);

    // Fecha o arquivo
    fclose(arquivo);

    // Imprime o que foi lido
    printf("%s\n", aux);

    return 0;
}