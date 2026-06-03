// 085 — O Cálice da Decisão (Ponteiros para Funções II)
// Lê dois números reais e um inteiro (1-4) representando a operação.
// Usa um array de ponteiros para função para executar a operação
// correspondente: 1=soma, 2=subtração, 3=multiplicação, 4=divisão.
// Trata divisão por zero e operação inválida.
//
// A função calculadora() recebe o ponteiro para a operação e a executa,
// demonstrando o conceito de callback com ponteiros para função.
#include <stdio.h>

double somar(double n1, double n2);
double subtrair(double n1, double n2);
double multiplicacao(double n1, double n2);
double divisao(double n1, double n2);
double calculadora(double n1, double n2, double (*operacao)(double, double));

int main(void) {
    double n1, n2;
    int op;

    scanf("%lf %lf %d", &n1, &n2, &op);

    // Array de ponteiros para função: cada índice acessa a operação correspondente
    double (*operacoes[])(double, double) = {somar, subtrair, multiplicacao, divisao};

    // Validação da operação
    if (op < 1 || op > 4) {
        printf("Operacao invalida\n");
        return 1;
    }

    // Tratamento de divisão por zero
    if (op == 4 && n2 == 0.0) {
        printf("Divisao por zero\n");
        return 1;
    }

    // Executa a operação via array de ponteiros para função
    printf("%.2lf\n", calculadora(n1, n2, operacoes[op - 1]));

    return 0;
}

// Funções de operação
double somar(double n1, double n2)        { return n1 + n2; }
double subtrair(double n1, double n2)     { return n1 - n2; }
double multiplicacao(double n1, double n2){ return n1 * n2; }
double divisao(double n1, double n2)      { return n1 / n2; }

// Função que recebe um ponteiro para função como argumento (callback)
double calculadora(double n1, double n2, double (*operacao)(double, double)) {
    return operacao(n1, n2);  // executa a função apontada
}