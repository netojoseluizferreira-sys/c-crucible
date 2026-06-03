// 080 — O Enxame de Almas (char** argv)
// Recebe argumentos da linha de comando e imprime cada um deles,
// um por linha, ignorando o nome do programa (argv[0]).
// Usa apenas aritmética de ponteiros para percorrer argv (sem []).
#include <stdio.h>

int main(int argc, char **argv) {

    // Começa de i = 1 para ignorar argv[0] (nome do programa)
    for (int i = 1; i < argc; i++) {
        printf("%s\n", *(argv + i));  // acesso via ponteiro, sem []
    }

    return 0;
}