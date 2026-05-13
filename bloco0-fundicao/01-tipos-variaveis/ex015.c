// 15 - O Trocador de Sinal (Bitwise)
// Inverte o sinal de um inteiro usando apenas operadores bitwise,
// sem recorrer ao operador unário de negação (-).
//
// Como funciona (assumindo complemento de dois e inteiros de 32 bits):
// 1. (numero >> 31) replica o bit de sinal por todo o inteiro.
//    - Se numero >= 0: vira 0x00000000 (0).
//    - Se numero < 0:  vira 0xFFFFFFFF (-1).
// 2. (numero ^ mascara): se mascara == 0, numero permanece igual.
//    Se mascara == -1, cada bit é invertido (complemento de um).
// 3. - (mascara): se mascara == 0, subtrai 0 (sem efeito).
//    Se mascara == -1, subtrair -1 equivale a somar 1.
//    Isso completa a operação de complemento de dois: ~numero + 1.
//
// Portabilidade: o padrão C99 não garante shift aritmético à direita
// para inteiros com sinal, mas a vasta maioria dos compiladores
// modernos (GCC, Clang, MSVC) implementa dessa forma.

#include <stdio.h>

int main(){
    int numero;

    scanf("%d", &numero);
    numero = (numero ^ (numero >> 31)) - (numero >> 31);

    printf("%d", numero);

    return 0;
}