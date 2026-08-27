// 148 — Concatenador de Arquivos
// Copia o conteúdo de fonte1 para destino e depois anexa fonte2 ao final.
// Demonstra modos "w" (sobrescrever) e "a" (append) do fopen.
#include <stdio.h>

int main(void) {
    char nome_fonte1[100], nome_fonte2[100], nome_destino[100];
    int caractere;

    // Lê os nomes dos arquivos
    scanf("%s %s %s", nome_fonte1, nome_fonte2, nome_destino);
    
    // Abre a primeira fonte para leitura
    FILE *fonte1 = fopen(nome_fonte1, "r");
    if (fonte1 == NULL) {
        printf("Erro ao abrir arquivo de origem.\n");
        return 1;
    }

    // Abre o destino para escrita ("w" sobrescreve se já existir)
    FILE *destino = fopen(nome_destino, "w");
    if (destino == NULL) {
        printf("Erro ao abrir arquivo de destino.\n");
        fclose(fonte1);
        return 1;
    }

    // Copia caractere por caractere da fonte1 para o destino
    while ((caractere = fgetc(fonte1)) != EOF) {
        fputc(caractere, destino);
    }

    fclose(fonte1);
    fclose(destino);
    
    // Abre a segunda fonte para leitura
    FILE *fonte2 = fopen(nome_fonte2, "r");
    if (fonte2 == NULL) {
        printf("Erro ao abrir arquivo de origem.\n");
        return 1;
    }

    // Abre o destino em modo append ("a" adiciona ao final)
    destino = fopen(nome_destino, "a");
    if (destino == NULL) {
        printf("Erro ao abrir arquivo de destino.\n");
        fclose(fonte2);
        return 1;
    }

    // Copia caractere por caractere da fonte2 para o final do destino
    while ((caractere = fgetc(fonte2)) != EOF) {
        fputc(caractere, destino);
    }

    fclose(fonte2);
    fclose(destino);

    printf("Concatenacao concluida.\n");
    return 0;
}