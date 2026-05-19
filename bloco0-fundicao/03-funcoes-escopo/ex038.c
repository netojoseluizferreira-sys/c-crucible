// 038 — Aumento de Salário
// Função aumentar() recebe um salário (float) e uma porcentagem de aumento (int).
// Calcula o novo salário e o retorna. Não imprime nada.
// A leitura e a impressão ficam em main.
#include <stdio.h>

float aumentar(float dinheiro, int aumento);

int main(void) {
    float salario;
    int percentual;

    scanf("%f %d", &salario, &percentual);

    printf("%.2f\n", aumentar(salario, percentual));

    return 0;
}

float aumentar(float dinheiro, int aumento) {
    // Cálculo do novo salário: salário + (salário * porcentagem / 100)
    float fator = (float)aumento / 100.0f;
    float novo_salario = dinheiro + (dinheiro * fator);
    return novo_salario;
}