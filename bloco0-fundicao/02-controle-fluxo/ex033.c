// 033 — O Saltador Condicional
// Lê até 10 inteiros. Se encontrar um 0, salta imediatamente para o final
// do programa usando goto, encerrando a leitura.
// Caso contrário, imprime cada número lido e ao final exibe "Encerrando".
#include <stdio.h>

int main(void) {
    int num;

    for (int i = 0; i < 10; i++) {
        scanf("%d", &num);

        // Se encontrar 0, abandona o loop imediatamente
        if (num == 0) {
            goto final;
        }

        printf("%d\n", num);
    }

final:
    printf("Encerrando\n");

    return 0;
}