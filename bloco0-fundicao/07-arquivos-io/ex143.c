// 143 — Bufferização Personalizada
// Gera 1000 linhas em um arquivo com buffer customizado de 64 bytes.
// Depois lê as primeiras 10 linhas para verificar a integridade.
#include <stdio.h>

int main(void) {
    // Buffer de 64 bytes para a escrita
    char meu_buffer[64];

    // Abre para escrita e leitura ("w+")
    FILE *arquivo = fopen("testelegal.txt", "w+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    // Configura bufferização total com buffer de 64 bytes
    // Deve ser chamado ANTES de qualquer operação de I/O
    setvbuf(arquivo, meu_buffer, _IOFBF, (size_t)64);

    // Gera 1000 linhas no arquivo
    for (int i = 0; i < 1000; i++) {
        fprintf(arquivo, "Linha %d\n", i + 1);
    }

    // CRÍTICO: descarrega o buffer restante no disco
    // Sem isso, os últimos bytes ainda estão no buffer
    fflush(arquivo);

    // Reposiciona o ponteiro para o início do arquivo
    // Sem isso, fgets começaria a ler do final e retornaria NULL
    fseek(arquivo, 0, SEEK_SET);

    // Lê e imprime as primeiras 10 linhas
    char linha[128];
    for (int i = 0; i < 10; i++) {
        if (fgets(linha, sizeof(linha), arquivo) == NULL) {
            break;  // fim do arquivo antes das 10 linhas
        }
        printf("%s", linha);  // fgets já inclui o \n
    }

    fclose(arquivo);

    return 0;
}