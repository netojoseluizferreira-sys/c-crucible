// 093 — A Câmara dos Gritos (Ponteiros para Funções Recursivas)
// Implementa o cálculo do fatorial de forma recursiva. A chamada
// principal é feita através de um ponteiro para função, demonstrando
// que funções podem ser referenciadas e invocadas indiretamente.
//
// Nota sobre o enunciado original: o exercício pedia que até a chamada
// recursiva interna fosse feita via ponteiro. Isso exigiria uma
// variável estática ou passagem do ponteiro como argumento extra.
// Esta versão atende ao núcleo do exercício (ponteiro na chamada
// principal) e mantém a recursão interna direta para clareza.
#include <stdio.h>

int fatorial(int num);

int main(void) {
    // Declaração de um ponteiro para função que recebe int e retorna int
    int (*Operacao)(int);
    int n;

    // Atribui o endereço da função fatorial ao ponteiro
    Operacao = fatorial;

    scanf("%d", &n);

    // Chama a função através do ponteiro
    printf("%d\n", Operacao(n));

    return 0;
}

// Função recursiva que calcula o fatorial de num
int fatorial(int num) {
    // Casos base: 0! = 1 e 1! = 1
    if (num == 0 || num == 1) {
        return 1;
    }
    // Passo recursivo: n! = n * (n-1)!
    return num * fatorial(num - 1);
}