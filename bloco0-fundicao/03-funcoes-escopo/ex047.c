// 047 — Escopo Local vs Global
// Demonstra o sombreamento de variáveis: uma variável local com o mesmo
// nome de uma global esconde a global dentro do seu escopo.
// A função exibir_global() retorna o valor da variável global.
// Em main, a variável local x sombreia a global.
#include <stdio.h>

int global = 100;                 // variável global com nome diferente
int exibir_global(void);

int main(void) {
    int x;                        // variável local (não sombreia mais "global")

    scanf("%d", &x);              // lê o valor para a variável LOCAL

    printf("%d\n", x);            // imprime a local
    printf("%d\n", exibir_global());  // imprime a global

    return 0;
}

int exibir_global(void) {
    return global;                // retorna a variável global
}