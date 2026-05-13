// 023 — O Contador de Intervalos
// Conta quantos números (entre 10 lidos) pertencem a cada intervalo.
// Intervalos: [0,25], [26,50], [51,75], [76,100].
// Números fora de 0–100 são ignorados.
//
// Usa if-else encadeado para classificar cada número no intervalo correto.
#include <stdio.h>

int main(void) {
    int numero;
    int faixa1 = 0, faixa2 = 0, faixa3 = 0, faixa4 = 0;

    for (int i = 0; i < 10; i++) {
        scanf("%d", &numero);

        if (numero >= 0 && numero <= 100) {
            if (numero <= 25)
                faixa1++;
            else if (numero <= 50)
                faixa2++;
            else if (numero <= 75)
                faixa3++;
            else
                faixa4++;
        }
        // Fora do intervalo: ignora
    }

    printf("%d\n%d\n%d\n%d\n", faixa1, faixa2, faixa3, faixa4);

    return 0;
}