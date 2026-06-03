// 109 — O Tribunal dos Vetores (Filtros, Transformações e Ordenação)
// Lê um vetor de inteiros e separa seus valores em três possibilidades:
// vetor original, vetor apenas com pares e vetor apenas com ímpares.
// O valor 0 é ignorado nos filtros de pares e ímpares.
//
// Depois, lê três comandos:
// - filtro: 'p' para pares, 'i' para ímpares ou outro valor para manter o vetor original
// - transform: 'd' para dobrar os valores antes de imprimir
// - ordem: 'c' para crescente, 'd' para decrescente
#include <stdio.h>
#include <stdlib.h>

int dobro(int a);
int compard(const void *a, const void *b);
int comparc(const void *a, const void *b);

int main(void){
    int tamanho;
    char filtro, transform, ordem;

    scanf("%d", &tamanho);

    int lista[tamanho];

    // Leitura do vetor original usando aritmética de ponteiros
    for (int i = 0; i < tamanho; i++) {
        scanf("%d", lista + i);
    }

    int par = 0;
    int impar = 0;

    // Conta quantos valores pares e ímpares existem, ignorando o zero
    for (int i = 0; i < tamanho; i++) {
        if (*(lista + i) == 0) continue;

        if (*(lista + i) % 2 == 0) par++;
        else impar++;
    }

    int pares[par];
    int impares[impar];

    int j = 0;
    int k = 0;

    // Separa os valores do vetor original nos vetores de pares e ímpares
    for (int i = 0; i < tamanho; i++) {
        if (*(lista + i) == 0) continue;

        if (*(lista + i) % 2 == 0) {
            *(pares + j) = *(lista + i);
            j++;
        } else {
            *(impares + k) = *(lista + i);
            k++;
        }
    }

    scanf(" %c %c %c", &filtro, &transform, &ordem);

    int *alvo = lista;
    int qtd = tamanho;

    // Define qual vetor será processado de acordo com o filtro escolhido
    if (filtro == 'p') {
        alvo = pares;
        qtd = par;
    } else if (filtro == 'i') {
        alvo = impares;
        qtd = impar;
    }

    // Ordena o vetor escolhido em ordem crescente ou decrescente
    if (ordem == 'c') {
        qsort(alvo, (size_t)qtd, sizeof *alvo, comparc);
    } else if (ordem == 'd') {
        qsort(alvo, (size_t)qtd, sizeof *alvo, compard);
    }

    // Aplica a transformação, se necessário, e imprime o vetor final
    for (int i = 0; i < qtd; i++) {
        if (transform == 'd') {
            *(alvo + i) = dobro(*(alvo + i));
        }

        printf("%d ", *(alvo + i));
    }

    return 0;
}

// Retorna o dobro de um valor inteiro
int dobro(int a){ return a * 2; }

// Comparador para qsort em ordem crescente
int comparc(const void *a, const void *b){
    const int x = *(const int *)a;
    const int y = *(const int *)b;

    if (x < y) {
        return -1;
    }

    if (x > y) {
        return 1;
    }

    return 0;
}

// Comparador para qsort em ordem decrescente
int compard(const void *a, const void *b){
    const int x = *(const int *)a;
    const int y = *(const int *)b;

    if (x > y) {
        return -1;
    }

    if (x < y) {
        return 1;
    }

    return 0;
}