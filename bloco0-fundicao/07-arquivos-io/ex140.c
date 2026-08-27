// 140 — Escrita e Leitura de Inteiros (Binário)
// Lê N inteiros, grava-os em um arquivo binário e depois lê de volta,
// imprimindo os valores. Demonstra fwrite e fread com modo binário.
#include <stdio.h>

int main(void) {
    int n;

    scanf("%d", &n);

    // Lê os n inteiros para o array
    int numeros[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &numeros[i]);
    }

    // Abre para escrita binária
    FILE *arquivo = fopen("dados.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    // Grava n inteiros no arquivo binário
    size_t elementos_escritos = fwrite(numeros, sizeof(int), (size_t)n, arquivo);
    if (elementos_escritos != (size_t)n) {
        printf("Erro ao escrever todos os dados no arquivo!\n");
        fclose(arquivo);
        return 1;
    }
    printf("Dados escritos com sucesso!\n");

    fclose(arquivo);

    // Abre para leitura binária
    arquivo = fopen("dados.bin", "rb");  // correção: era dados.txt
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura!\n");
        return 1;
    }

    // Lê n inteiros do arquivo binário
    int numeros_lidos[n];
    size_t elementos_lidos = fread(numeros_lidos, sizeof(int), (size_t)n, arquivo);

    if (elementos_lidos == (size_t)n) {
        printf("Dados lidos com sucesso: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", numeros_lidos[i]);
        }
        printf("\n");
    } else {
        printf("Erro na leitura ou fim do arquivo atingido precocemente. Elementos lidos: %zu\n", elementos_lidos);
    }

    fclose(arquivo);

    return 0;
}