// 055 — Torre de Hanói (Recursivo com impressão)
// Resolve o problema da Torre de Hanói para n discos.
// Move todos os discos da haste 'A' para a haste 'C' usando 'B' como auxiliar.
// Regras: apenas um disco por vez; disco maior nunca sobre menor.
// A recursão resolve em 3 passos:
//   1. Move n-1 discos da origem para a auxiliar.
//   2. Move o disco n da origem para o destino.
//   3. Move n-1 discos da auxiliar para o destino.
#include <stdio.h>

void hanoi(int n, char origem, char destino, char auxiliar);

int main(void) {
    int tamanho;

    scanf("%d", &tamanho);

    hanoi(tamanho, 'A', 'C', 'B');

    return 0;
}

void hanoi(int n, char origem, char destino, char auxiliar) {
    // Caso base: apenas um disco → move direto
    if (n == 1) {
        printf("Mover disco de %c para %c\n", origem, destino);
        return;
    }

    // Passo 1: move n-1 discos da origem para a auxiliar (destino vira apoio)
    hanoi(n - 1, origem, auxiliar, destino);

    // Passo 2: move o disco maior da origem para o destino
    printf("Mover disco de %c para %c\n", origem, destino);

    // Passo 3: move n-1 discos da auxiliar para o destino (origem vira apoio)
    hanoi(n - 1, auxiliar, destino, origem);
}