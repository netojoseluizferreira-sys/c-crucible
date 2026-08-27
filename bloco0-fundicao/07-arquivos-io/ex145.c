// 146 — Inversor de Arquivo (Binário)
// Lê o arquivo inteiro, inverte a ordem dos bytes e reescreve.
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char nome_arquivo[100];
    scanf("%s", nome_arquivo);

    // Abre para leitura binária
    FILE *arquivo = fopen(nome_arquivo, "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return 1;
    }

    // Descobre o tamanho do arquivo
    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);

    // Aloca memória para o arquivo inteiro
    unsigned char *dados = malloc((size_t)tamanho);
    if (dados == NULL) {
        fclose(arquivo);
        return 1;
    }

    // Lê tudo
    fread(dados, 1, (size_t)tamanho, arquivo);
    fclose(arquivo);

    // Inverte os bytes usando dois ponteiros
    unsigned char *inicio = dados;
    unsigned char *fim = dados + tamanho - 1;

    while (inicio < fim) {
        unsigned char temp = *inicio;
        *inicio = *fim;
        *fim = temp;
        inicio++;
        fim--;
    }

    // Reescreve o arquivo invertido
    arquivo = fopen(nome_arquivo, "wb");
    if (arquivo == NULL) {
        free(dados);
        return 1;
    }

    fwrite(dados, 1, (size_t)tamanho, arquivo);
    fclose(arquivo);

    free(dados);
    printf("Arquivo invertido.\n");
    return 0;
}