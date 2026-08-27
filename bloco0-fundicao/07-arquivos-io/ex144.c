// 144 — Leitura de Arquivo CSV Simples
// Cria um arquivo CSV com dados de alunos e depois lê o arquivo,
// separando os campos manualmente (sem strtok) e imprimindo cada campo.
// Demonstra parsing de texto, manipulação de strings e leitura linha a linha.
#include <stdio.h>

int main(void) {
    // Abre o arquivo para leitura
    FILE *arquivo = fopen("dados.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo CSV!\n");
        return 1;
    }

    char linha[256];
    int numero_linha = 1;

    // Lê cada linha do arquivo até o final
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("=== Registro %d ===\n", numero_linha);

        int posicao = 0;
        int campo = 1;

        // Percorre a linha caractere por caractere
        while (linha[posicao] != '\0' && linha[posicao] != '\n') {
            // Se encontrar vírgula, é o fim de um campo
            if (linha[posicao] == ',') {
                // Imprime quebra de linha para separar campos
                printf("\n");
                campo++;
                posicao++;
                continue;
            }

            // Imprime o caractere atual do campo
            // Dependendo do campo, imprime o prefixo correto
            if (posicao == 0 || linha[posicao - 1] == ',') {
                // É o início de um campo, imprime o prefixo
                if (campo == 1) {
                    printf("Nome: ");
                } else if (campo == 2) {
                    printf("Idade: ");
                } else if (campo == 3) {
                    printf("Nota: ");
                }
            }

            // Imprime o caractere do campo
            printf("%c", linha[posicao]);
            posicao++;
        }

        printf("\n");
        numero_linha++;
    }

    fclose(arquivo);
    return 0;
}