// 19 — O Exterminador de Decimais
// Trunca a parte fracionária de um número real usando cast explícito.
// O cast (int) descarta a parte decimal sem arredondamento.
// Para números negativos, o truncamento vai em direção a zero (-2.7 → -2).

#include <stdio.h>

int main(){
    double num;
    
    scanf("%lf", &num);

    // Cast para int remove a parte fracionária
    printf("%d", (int)num);
    return 0;
}