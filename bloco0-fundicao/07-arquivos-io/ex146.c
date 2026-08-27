// 146 — Inversor de Arquivo (Binário)
// Lê um arquivo binário inteiro para memória, inverte a ordem dos bytes
// e reescreve o arquivo com os bytes invertidos.
// Demonstra leitura completa com fseek/ftell, alocação dinâmica e escrita binária.
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char nome_arquivo[100];

    // Lê o nome do arquivo
    scanf("%s", nome_arquivo);

    // Abre para leitura binária
    FILE *arquivo = fopen(nome_arquivo, "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return 1;
    }

    // Move para o final do arquivo para descobrir o tamanho
    fseek(arquivo, 0, SEEK_END);

    // Obtém o tamanho total em bytes
    long tamanho = ftell(arquivo);
    if (tamanho <= 0) {
        printf("Arquivo vazio ou erro ao obter tamanho.\n");
        fclose(arquivo);
        return 1;
    }

    // Volta para o início do arquivo
    fseek(arquivo, 0, SEEK_SET);

    // Aloca memória para armazenar todos os bytes do arquivo
    unsigned char *dados = (unsigned char *)malloc((size_t)tamanho);
    if (dados == NULL) {
        printf("Erro ao alocar memoria.\n");
        fclose(arquivo);
        return 1;
    }

    // Lê o arquivo inteiro de uma vez
    size_t bytes_lidos = fread(dados, 1, (size_t)tamanho, arquivo);
    if (bytes_lidos != (size_t)tamanho) {
        printf("Erro ao ler o arquivo.\n");
        free(dados);
        fclose(arquivo);
        return 1;
    }

    fclose(arquivo);

    // Inverte a ordem dos bytes no array
    // Usa dois ponteiros: um no início e outro no final
    unsigned char *inicio = dados;
    unsigned char *fim = dados + tamanho - 1;

    while (inicio < fim) {
        // Troca os bytes usando XOR swap (sem variável temporária)
        *inicio ^= *fim;
        *fim ^= *inicio;
        *inicio ^= *fim;

        inicio++;
        fim--;
    }

    // Abre para escrita binária ("wb" sobrescreve)
    arquivo = fopen(nome_arquivo, "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para escrita.\n");
        free(dados);
        return 1;
    }

    // Grava os bytes invertidos
    size_t bytes_escritos = fwrite(dados, 1, (size_t)tamanho, arquivo);
    if (bytes_escritos != (size_t)tamanho) {
        printf("Erro ao escrever no arquivo.\n");
        free(dados);
        fclose(arquivo);
        return 1;
    }

    // Libera a memória
    free(dados);
    dados = NULL;

    fclose(arquivo);

    printf("Arquivo invertido.\n");
    return 0;
}