// 103 — A Passagem Secreta (restrict)
// Lê N inteiros para um array e copia-os para outro usando uma função
// que promete que as regiões de memória não se sobrepõem.
//
// A palavra-chave restrict é uma promessa ao compilador de que os
// ponteiros apontam para regiões de memória independentes, permitindo
// otimizações mais agressivas. Se a promessa for quebrada (sobreposição),
// o comportamento é indefinido.
//
// Neste exercício, os arrays são declarados separadamente na main,
// portanto a promessa é segura e válida.
#include <stdio.h>

void copy(int *restrict arr, int *restrict veri, int n);

int main(void) {
    int n;

    scanf("%d", &n);

    int lista1[n], lista2[n];

    // Leitura dos elementos usando aritmética de ponteiros
    for (int i = 0; i < n; i++) {
        scanf("%d", lista1 + i);
    }

    // Cópia com promessa restrict (regiões independentes)
    copy(lista1, lista2, n);

    // Impressão do array copiado usando aritmética de ponteiros
    for (int i = 0; i < n; i++) {
        printf("%d ", *(lista2 + i));
    }
    printf("\n");

    return 0;
}

// Copia n inteiros de arr para veri.
// restrict promete que arr e veri não se sobrepõem.
void copy(int *restrict arr, int *restrict veri, int n) {
    for (int i = 0; i < n; i++) {
        *(veri + i) = *(arr + i);
    }
}