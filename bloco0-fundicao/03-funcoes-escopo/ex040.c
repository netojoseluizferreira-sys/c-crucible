// 040 — Troca de Valores (Swap)
// Função void swap_ponteiros() recebe dois ponteiros para inteiro
// e permuta os valores das variáveis originais usando XOR bitwise.
// Se os ponteiros apontarem para o mesmo endereço, nada faz.
// A leitura e a impressão ficam em main.
#include <stdio.h>

void swap_ponteiros(int *a, int *b);

int main(void) {
    int x, y;

    scanf("%d %d", &x, &y);

    swap_ponteiros(&x, &y);  // passa os endereços diretamente

    printf("%d %d\n", x, y);

    return 0;
}

void swap_ponteiros(int *a, int *b) {
    // Verifica se os ponteiros não apontam para o mesmo endereço
    if (a != b) {
        *a = *a ^ *b;
        *b = *a ^ *b;
        *a = *a ^ *b;
    }
}