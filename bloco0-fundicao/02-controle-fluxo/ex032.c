// 032 — O Classificador de Dígitos
// Classifica o último dígito (unidade) de números positivos em três categorias.
// Usa switch com fall-through para agrupar os 10 dígitos em "Baixo", "Medio" e "Alto".
// O programa termina quando um número negativo é digitado.
#include <stdio.h>

int main(void) {
    int numero;

    while (1) {
        scanf("%d", &numero);

        // Condição de parada: número negativo encerra o programa
        if (numero < 0) {
            return 0;
        }

        // Extrai o último dígito (unidade) usando módulo 10
        int resto = numero % 10;

        // Switch com fall-through: dígitos agrupados por categoria
        switch (resto) {
            case 0:
            case 1:
            case 2:
            case 3:
                printf("%d -> Baixo\n", numero);
                break;
            case 4:
            case 5:
            case 6:
                printf("%d -> Medio\n", numero);
                break;
            case 7:
            case 8:
            case 9:
                printf("%d -> Alto\n", numero);
                break;
            default:
                break;  // nunca acontece (0-9 cobertos), mas mantém o switch seguro
        }
    }

    return 0;
}