// 092 — O Poço da Reflexão (Ponteiros Triplos com Troca)
// Cria duas variáveis inteiras e dois ponteiros simples apontando para elas.
// Em seguida, cria ponteiros duplos para esses ponteiros simples e armazena
// esses ponteiros duplos em um array terminado por NULL.
//
// Este exercício demonstra indireção tripla:
// - arr[i] é um ponteiro duplo (int **)
// - *arr[i] é um ponteiro simples (int *)
// - **arr[i] é o valor inteiro original
// - trocar_alvos recebe int *** para alterar quais ponteiros duplos estão
//   armazenados nas posições do array
#include <stdio.h>

void trocar_alvos(int ***x, int ***y);
void exibir_array(int ***arr);

int main(void) {
    int a = 10, b = 20;
    int *pa = &a, *pb = &b;
    int **ppa = &pa, **ppb = &pb;
    int **arr[3] = {ppa, ppb, NULL};

    exibir_array(arr);  // exibe os valores antes da troca
    trocar_alvos(arr, arr + 1);  // troca os ponteiros duplos dentro do array
    exibir_array(arr);  // exibe os valores depois da troca

    return 0;
}

// Troca os ponteiros duplos armazenados nas posições recebidas
void trocar_alvos(int ***x, int ***y) {
    int **aux;

    aux = *x;
    *x = *y;
    *y = aux;
}

// Percorre o array de ponteiros duplos até encontrar NULL
void exibir_array(int ***arr) {
    for (size_t i = 0; *(arr + i) != NULL; i++) {
        printf("%d ", ***(arr + i));  // acesso por aritmética de ponteiros
    }

    printf("\n");
}