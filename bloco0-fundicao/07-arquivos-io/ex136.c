// 136 — Gravador de Texto Simples
// Lê uma string do usuário e grava em um arquivo texto.
// Demonstra fopen com modo "w", fprintf e fclose.
// Se o arquivo não puder ser aberto, exibe mensagem de erro.
#include <stdio.h>

int main(void) {
    char aux[50];

    // Abre o arquivo para escrita (modo "w" sobrescreve se já existir)
    FILE *arquivo = fopen("saida.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;  // encerra com erro
    }

    printf("Digite uma palavra: ");
    scanf("%49s", aux);  // limita a leitura a 49 caracteres (segurança)

    // Grava a string no arquivo
    fprintf(arquivo, "%s", aux);

    // Fecha o arquivo (importante para salvar os dados)
    fclose(arquivo);

    return 0;
}