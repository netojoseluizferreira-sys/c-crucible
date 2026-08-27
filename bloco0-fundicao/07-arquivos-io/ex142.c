// 142 — Atualização Seletiva com fseek
// Cria um arquivo binário com 5 inteiros zerados usando calloc,
// atualiza um registro específico com fseek e fwrite usando ponteiros,
// e depois lê todos os valores com fread.
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int indice, valor;
    int dados_lidos[5];

    // Abre para leitura e escrita binária ("wb+")
    FILE *arquivo = fopen("registros.bin", "wb+");
    if (arquivo == NULL) {
        return 1;
    }

    // Aloca 5 inteiros zerados com calloc
    int *dados = (int *)calloc(5, sizeof(int));
    if (dados == NULL) {
        fclose(arquivo);
        return 1;
    }

    // Grava os 5 zeros no arquivo
    fwrite(dados, sizeof(int), 5, arquivo);

    // Lê o índice e o novo valor
    scanf("%d %d", &indice, &valor);

    // Atualiza o valor no array dinâmico usando aritmética de ponteiros
    *(dados + indice) = valor;

    // Posiciona o ponteiro no registro correto
    // Correção: converte indice para size_t antes da multiplicação
    // Isso evita a conversão implícita de int para size_t
    fseek(arquivo, (size_t)indice * sizeof(int), SEEK_SET);

    // Grava o valor atualizado na posição correta
    fwrite(dados + indice, sizeof(int), 1, arquivo);

    // Volta para o início do arquivo
    fseek(arquivo, 0, SEEK_SET);

    // Lê os 5 inteiros do arquivo
    size_t lidos = fread(dados_lidos, sizeof(int), 5, arquivo);

    // Imprime os valores lidos
    if (lidos == 5) {
        for (int i = 0; i < 5; i++) {
            printf("%d ", *(dados_lidos + i));
        }
        printf("\n");
    }

    // Libera a memória alocada
    free(dados);
    dados = NULL;

    fclose(arquivo);
    return 0;
}