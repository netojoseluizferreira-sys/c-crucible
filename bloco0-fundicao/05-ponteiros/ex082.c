// 082 — O Labirinto de Espelhos (Ponteiros para Ponteiros II)
// Lê dois inteiros e troca seus valores usando apenas ponteiros duplos
// (sem acessar as variáveis originais diretamente).
#include <stdio.h>

int main(void) {
    int a, b;

    scanf("%d %d", &a, &b);

    // Ponteiros simples apontando para as variáveis
    int *pa = &a;
    int *pb = &b;

    // Ponteiros duplos apontando para os ponteiros
    int **ppa = &pa;
    int **ppb = &pb;

    // Troca usando apenas **ppa e **ppb
    **ppa = **ppa + **ppb;
    **ppb = **ppa - **ppb;
    **ppa = **ppa - **ppb;

    printf("%d %d\n", **ppa, **ppb);

    return 0;
}