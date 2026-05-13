// 025 — O Contador de Dias do Mês
// Dado um inteiro de 1 a 12, retorna o número de dias do mês
// (ano não bissexto). Se o valor estiver fora do intervalo,
// imprime "Inválido" e continua lendo até receber um valor válido.
//
// Usa switch com fall-through para agrupar meses de mesma quantidade.
#include <stdio.h>

int main(void) {
    int mes;

    // Loop infinito: só sai quando um mês válido for informado
    while (1) {
        scanf("%d", &mes);

        switch (mes) {
            // Meses com 31 dias: fall-through agrupa os cases
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                printf("31\n");
                return 0;

            // Meses com 30 dias
            case 4:
            case 6:
            case 9:
            case 11:
                printf("30\n");
                return 0;

            // Fevereiro (ano não bissexto)
            case 2:
                printf("28\n");
                return 0;

            // Qualquer outro valor é inválido; continua o loop
            default:
                printf("Inválido\n");
                break;
        }
    }
}