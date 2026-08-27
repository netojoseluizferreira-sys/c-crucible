// 141 — Tamanho de Arquivo com fseek
// Determina o tamanho total de um arquivo em bytes usando fseek + ftell.
// Demonstra posicionamento no final do arquivo e leitura da posição atual.
#include <stdio.h>

int main(void) {
    // Abre o arquivo em modo leitura binária ("rb")
    // Binário é importante para que fseek funcione corretamente em qualquer sistema
    FILE *arquivo = fopen("arquivo.txt", "rb");
    
    // Verifica se o arquivo foi aberto corretamente
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return 1;
    }

    // Move o ponteiro para o final do arquivo
    // SEEK_END = posiciona a partir do final
    // 0 = deslocamento zero a partir do final (ou seja, exatamente no final)
    fseek(arquivo, 0, SEEK_END);

    // ftell retorna a posição atual em bytes (contados do início)
    // Como estamos no final, essa posição é exatamente o tamanho do arquivo
    long tamanho = ftell(arquivo);

    // Imprime o tamanho do arquivo
    printf("%ld\n", tamanho);

    // Fecha o arquivo
    fclose(arquivo);

    return 0;
}