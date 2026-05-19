// 049 — Operações em Array com Função
// A função analisar_array() recebe um array de inteiros e seu tamanho,
// e através de ponteiros retorna o maior e o menor valor encontrados.
// A função retorna void. A leitura e a impressão ficam em main.
// O array tem no máximo 10 elementos.
#include <stdio.h>

void analisar_array(int *arr, int tamanho, int *maior, int *menor);

int main(void) {
    int tamanho;
    int lista[10], maior, menor;

    // Entrada amigável
    printf("Digite a quantidade de numeros (1 a 10): ");
    scanf("%d", &tamanho);

    printf("Digite os %d numeros:\n", tamanho);
    for (int i = 0; i < tamanho; i++) {
        printf("  %do numero: ", i + 1);
        scanf("%d", &lista[i]);
    }

    // Chama a função passando o array e os ponteiros para os resultados
    analisar_array(lista, tamanho, &maior, &menor);

    // Saída amigável
    printf("\nResultado:\n");
    printf("  Maior valor: %d\n", maior);
    printf("  Menor valor: %d\n", menor);

    return 0;
}

// Percorre o array uma única vez, atualizando o maior e o menor
void analisar_array(int *arr, int tamanho, int *maior, int *menor) {
    // Inicializa ambos com o primeiro elemento
    *maior = arr[0];
    *menor = arr[0];

    // Percorre do segundo ao último, comparando cada elemento
    for (int i = 1; i < tamanho; i++) {
        if (arr[i] > *maior)
            *maior = arr[i];
        if (arr[i] < *menor)
            *menor = arr[i];
    }
}