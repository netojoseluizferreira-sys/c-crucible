// 089 — O Arsenal de Funções (Tabela de Ponteiros para Funções)
// Lê dois inteiros e um índice (0-4). Usa um array de ponteiros
// para função para executar a operação correspondente:
// 0=soma, 1=subtração, 2=multiplicação, 3=divisão, 4=potência.
//
// O typedef Operacao simplifica a declaração do array de ponteiros.
// A chamada tabela_operacoes[op](a, b) seleciona e executa a função
// correspondente ao índice, sem necessidade de switch/if.
#include <stdio.h>

int somar(int a, int b);
int subtrair(int a, int b);
int multiplicar(int a, int b);
int dividir(int a, int b);
int elevar(int a, int b);

int main(void) {
    // Typedef para ponteiro de função: Operacao é um tipo que representa
    // "ponteiro para função que recebe dois int e retorna int"
    typedef int (*Operacao)(int, int);

    int a, b, op;

    // Array de ponteiros para função: tabela_operacoes[i] é uma função
    Operacao tabela_operacoes[] = {somar, subtrair, multiplicar, dividir, elevar};

    scanf("%d %d %d", &a, &b, &op);

    // Chama a função pelo índice: tabela_operacoes[op] retorna o ponteiro,
    // e (a, b) são os argumentos passados a ela
    printf("%d\n", tabela_operacoes[op](a, b));

    return 0;
}

// Funções de operação
int somar(int a, int b)        { return a + b; }
int subtrair(int a, int b)     { return a - b; }
int multiplicar(int a, int b)  { return a * b; }
int dividir(int a, int b)      { return a / b; }

// Potência recursiva (a^b), com casos base
int elevar(int a, int b) {
    if (b == 0) return 1;        // qualquer número elevado a 0 é 1
    if (a == 1) return 1;        // 1 elevado a qualquer coisa é 1
    return a * elevar(a, b - 1); // passo recursivo
}