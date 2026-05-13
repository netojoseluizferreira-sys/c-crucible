// 17 — O Detector de Paridade
// Verifica se o número de bits 1 em um inteiro sem sinal é ímpar.
//
// Algoritmo: percorre cada bit do número usando shift right.
// Para cada bit, testa se o LSB está ligado (temp & 1).
// Acumula a contagem e no final verifica se o total é ímpar.
//
// Usa unsigned int para evitar comportamento indefinido
// no shift right (signed pode ter extensão de sinal).

#include <stdio.h>

int main(){
    unsigned int numero, paridade = 0; 

    scanf("%u", &numero);
    
    unsigned int temp = numero;
    while (temp > 0) {
        if (temp & 1) {
            paridade++;
        }
        temp = temp >> 1;
    }
    
    if (paridade % 2 != 0) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return 0;
}