// 024 — Os Três Suspeitos
// Verifica se a descrição (altura, peso) corresponde a um dos três suspeitos.
// Suspeito 1: (1, 2)
// Suspeito 2: (2, 3)
// Suspeito 3: (3, 1)
// Qualquer outra combinação é considerada inocente.
//
// Usa if-else aninhado para mapear cada suspeito à sua descrição exata.
#include <stdio.h>

int main(void) {
    int altura, peso;

    scanf("%d %d", &altura, &peso);

    if (altura == 1 && peso == 2)
        printf("Culpado\n");
    else if (altura == 2 && peso == 3)
        printf("Culpado\n");
    else if (altura == 3 && peso == 1)
        printf("Culpado\n");
    else
        printf("Inocente\n");

    return 0;
}