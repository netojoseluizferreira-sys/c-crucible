// 022 — O Guardião do Castelo
// O personagem deve inserir a chave correta (A, B ou C) para abrir a porta.
// Qualquer outra entrada aciona uma armadilha e encerra o programa.
// O laço continua até que uma chave válida seja inserida ou a armadilha dispare.
#include <stdio.h>

int main() {
    char tentativa;

    // Continua lendo até acertar uma chave ou cair na armadilha
    while (1) {
        scanf(" %c", &tentativa);  // espaço antes de %c ignora whitespace

        if (tentativa == 'A' || tentativa == 'B' || tentativa == 'C') {
            printf("Porta abriu com chave %c\n", tentativa);
            break;  // sai do loop, porta aberta
        } else {
            printf("Armadilha!\n");
        }
    }

    return 0;
}