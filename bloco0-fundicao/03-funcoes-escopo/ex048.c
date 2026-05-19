// 048 — Função que Retorna Múltiplos Valores
// A função operacao() recebe dois inteiros e, através de ponteiros,
// retorna a soma, o produto e a média (como double).
// A função em si retorna void.
// A leitura e a impressão ficam em main.
#include <stdio.h>

int soma, produto;
double media;
void operacao(int a, int b);

int main(void) {
    int a, b;

    scanf("%d %d", &a, &b);

    operacao(a, b);

    printf("%d\n%d\n%.2lf\n", soma, produto, media);

    return 0;
}

void operacao(int a, int b) {
    int *pSoma = &soma;
    int *pProduto = &produto;
    double *pMedia = &media;

    *pSoma = a + b;
    *pProduto = a * b;
    *pMedia = (double)(a + b) / 2.0;
}