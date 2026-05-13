// 12 — O Inversor de Sinal (Bitwise)
// Inverte o sinal de um inteiro sem usar o operador unário -.
//
// Estratégia: utiliza propriedades do complemento de dois.
// - Se numero >= 0: (numero ^ 0) - 0 = numero.
// - Se numero < 0:  (numero ^ -1) - (-1) = ~numero + 1 = -numero.
//
// Atenção: assume inteiros de 32 bits e complemento de dois.
//          É portável para a maioria das arquiteturas modernas,
//          mas não é garantido pelo padrão C para todas as plataformas.

#include <stdio.h>

int main(){
    int numero;
    
    scanf("%d", &numero);

    // Inversão de sinal via complemento de dois
    numero = (numero ^ (numero >> 31)) - (numero >> 31);

    printf("%d", numero);

    return 0;
}