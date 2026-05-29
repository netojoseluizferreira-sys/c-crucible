// 065 — Busca em Array com Ponteiro (Array + Aritmética de Ponteiros)
// Lê N inteiros e um valor X. Verifica se X está presente no array
// usando apenas aritmética de ponteiros (sem []). Imprime o índice
// da primeira ocorrência ou -1 se não encontrado.
#include <stdio.h>

int encontrar(int *arr, int qnt, int encontro);

int main(void) {
    int qnt, encontro;

    // Lê a quantidade de elementos
    scanf("%d", &qnt);
    int numeros[qnt];
    int *p = numeros;

    // Lê os N elementos usando aritmética de ponteiros
    for (int i = 0; i < qnt; i++) {
        scanf("%d", p + i);
    }

    // Lê o valor a ser buscado
    scanf("%d", &encontro);

    // Exibe o índice da primeira ocorrência ou -1
    printf("%d\n", encontrar(p, qnt, encontro));

    return 0;
}

// Busca o valor 'encontro' no array usando apenas aritmética de ponteiros
int encontrar(int *arr, int qnt, int encontro) {
    for (int i = 0; i < qnt; i++) {
        if (*(arr + i) == encontro) {  // acesso via ponteiro, sem []
            return i;                  // retorna o índice
        }
    }
    return -1;  // não encontrado
}