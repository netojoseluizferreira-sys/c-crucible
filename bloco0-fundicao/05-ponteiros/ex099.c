// 099 — A Arena dos Gladiadores (Ponteiros para Funções com Estratégia)
// Lê um inteiro (1-3) representando a estratégia de ataque e executa
// a função correspondente via ponteiro para função, imprimindo o dano.
//
// Demonstra o padrão Strategy simplificado: um ponteiro para função
// é usado para selecionar o comportamento em tempo de execução,
// sem depender de switch/if dentro da lógica de combate.
#include <stdio.h>

int kungfu(void);
int jiujitsu(void);
int karate(void);

int main(void) {
    // Array de ponteiros para função: cada índice é uma estratégia
    int (*ataques[])(void) = {kungfu, jiujitsu, karate};
    int n;

    scanf("%d", &n);

    // Validação da escolha
    if (n < 1 || n > 3) {
        return 0;  // fora do intervalo, encerra sem imprimir
    }

    // Executa o ataque via array de ponteiros para função
    printf("Dano: %d\n", ataques[n - 1]());

    return 0;
}

// Artes marciais — cada uma retorna o dano causado
int kungfu(void)   { return 75; }
int jiujitsu(void) { return 100; }
int karate(void)   { return 50; }