// 094 — O Arquivo das Almas Perdidas (char **argv com Filtros)
// Recebe argumentos da linha de comando e um caractere da entrada padrão.
// Imprime apenas os argumentos cujo primeiro caractere coincide com o
// caractere lido, ignorando o nome do programa (argv[0]).
// Usa apenas aritmética de ponteiros para navegar entre os argumentos
// e acessar o primeiro caractere de cada um.
#include <stdio.h>

int main(int argc, char **argv) {
    char filtro;

    // Lê o caractere de filtro da entrada padrão
    scanf("%c", &filtro);

    // Começa de i = 1 para ignorar argv[0] (nome do programa)
    for (int i = 1; i < argc; i++) {
        // **(argv + i) é o primeiro caractere do argumento i
        // Equivalente a argv[i][0]
        if (**(argv + i) == filtro) {
            printf("%s\n", *(argv + i));  // imprime o argumento via ponteiro
        }
    }

    return 0;
}