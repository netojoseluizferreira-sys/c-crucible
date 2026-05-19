// 054 — Número Primo (Função Booleana)
// Função eh_primo() retorna 1 se o número for primo, 0 caso contrário.
// Utiliza otimização: testa divisores até a raiz quadrada do número.
// A leitura e a impressão ficam em main.
#include <stdio.h>
#include <math.h>

int eh_primo(int numero);

int main(void) {
    int numero;

    scanf("%d", &numero);

    if (eh_primo(numero))
        printf("Primo\n");
    else
        printf("Composto\n");

    return 0;
}

int eh_primo(int numero) {
    // Números menores ou iguais a 1 não são primos
    if (numero <= 1)
        return 0;

    // 2 é o único primo par
    if (numero == 2)
        return 1;

    // Números pares maiores que 2 não são primos
    if (numero % 2 == 0)
        return 0;

    // Testa apenas divisores ímpares até a raiz quadrada
    int limite = (int)sqrt(numero);
    for (int i = 3; i <= limite; i += 2) {
        if (numero % i == 0)
            return 0;  // encontrou divisor → não é primo
    }

    return 1;  // nenhum divisor encontrado → é primo
}