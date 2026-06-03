// 098 — A Pilha das Almas Perdidas (Ponteiros para Funções em Estruturas)
// Lê um nome e um inteiro (1 ou 2). Executa o feitiço correspondente
// usando ponteiros para função passados como argumento.
//
// As funções feitico1() e feitico2() retornam constantes de string,
// e a função escolha() recebe dois ponteiros para função, demonstrando
// que funções podem ser passadas como argumentos e executadas sob demanda.
#include <stdio.h>

const char *feitico1(void);
const char *feitico2(void);
void escolha(char *nome, int num, const char *(*fun1)(void), const char *(*fun2)(void));

int main(void) {
    int num;
    char nome[50];

    scanf("%s %d", nome, &num);

    // Passa as funções como argumentos para escolha()
    escolha(nome, num, feitico1, feitico2);

    return 0;
}

// Feitiços que retornam strings constantes
const char *feitico1(void) { return "AAAAH!"; }
const char *feitico2(void) { return "shhh..."; }

// Recebe dois ponteiros para função e executa o escolhido pelo índice
void escolha(char *nome, int num, const char *(*fun1)(void), const char *(*fun2)(void)) {
    switch (num) {
        case 1:
            printf("%s: %s\n", nome, fun1());  // executa o feitiço 1 via ponteiro
            break;
        case 2:
            printf("%s: %s\n", nome, fun2());  // executa o feitiço 2 via ponteiro
            break;
        default:
            printf("Feitico invalido\n");
            break;
    }
}