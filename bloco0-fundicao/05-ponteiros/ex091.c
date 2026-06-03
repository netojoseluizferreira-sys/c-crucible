// 091 — A Rede de Almas Encadeadas (Ponteiros Triplos com Array)
// Cria três variáveis inteiras com valores distintos. Cria ponteiros simples
// para essas variáveis e, em seguida, ponteiros duplos para esses ponteiros.
// Depois, armazena os ponteiros duplos em um array terminado por NULL.
//
// Este exercício demonstra indireção tripla:
// - arr[i] é um ponteiro duplo (int **)
// - *arr[i] é um ponteiro simples (int *)
// - **arr[i] é o valor inteiro original
// - ***(arr + i) acessa o mesmo valor usando aritmética de ponteiros
#include <stdio.h>

int main(void) {
    int a = 5, b = 10, c = 20;
    int *pa = &a, *pb = &b, *pc = &c;
    int **ppa = &pa, **ppb = &pb, **ppc = &pc;
    int **arr[4] = {ppa, ppb, ppc, NULL};

    // Percorre o array de ponteiros duplos até encontrar NULL
    for (size_t i = 0; *(arr + i) != NULL; i++) {
        printf("%d ", ***(arr + i));  // acesso por aritmética de ponteiros
    }

    return 0;
}