// 034 — A Sequência de Collatz
// Gera a sequência de Collatz até chegar a 1.
// Se N for par, divide por 2. Se ímpar, multiplica por 3 e soma 1.
// O loop termina quando o valor chega a 1.
#include <stdio.h>

int main(void) {
    int num;

    scanf("%d", &num);

    // Exibe o valor inicial antes de começar o loop
    printf("%d", num);

    // Se já for 1, o do-while não executa o corpo
    if (num != 1) {
        do {
            if (num % 2 == 0) {
                num /= 2;
            } else {
                num = num * 3 + 1;
            }
            printf(" %d", num);
        } while (num != 1);
    }

    printf("\n");
    return 0;
}