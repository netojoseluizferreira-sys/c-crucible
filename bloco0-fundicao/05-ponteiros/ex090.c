// 090 — O Fosso da Morte Súbita (void* Genérico)
// Cria uma função que aceita um ponteiro genérico (void*) e um caractere
// indicando o tipo real do dado. A função imprime o valor corretamente,
// fazendo a conversão apropriada via cast.
//
// A função tipagem() demonstra o uso de void* como tipo coringa:
// o mesmo ponteiro pode apontar para int, char ou float, e o cast
// correto recupera o valor original.
#include <stdio.h>
#include <stdlib.h>  // atoi, atof

void tipagem(void *ptr, char tipo);

int main(void) {
    char tipo;
    int dado_int;
    char dado_char;
    float dado_float;
    void *ptr = NULL;

    // Leitura do tipo e do valor
    scanf("%c", &tipo);

    if (tipo == 'i') {
        scanf("%d", &dado_int);
        ptr = &dado_int;
    } else if (tipo == 'c') {
        scanf(" %c", &dado_char);  // espaço antes de %c ignora whitespace
        ptr = &dado_char;
    } else if (tipo == 'f') {
        scanf("%f", &dado_float);
        ptr = &dado_float;
    }

    tipagem(ptr, tipo);

    return 0;
}

// Recebe um void* e um tipo, faz o cast apropriado e imprime o valor
void tipagem(void *ptr, char tipo) {
    if (ptr == NULL) {
        printf("Tipo invalido.\n");
        return;
    }

    if (tipo == 'i') {
        printf("Inteiro: %d\n", *((int *)ptr));     // cast para int*
    } else if (tipo == 'c') {
        printf("Caractere: %c\n", *((char *)ptr));  // cast para char*
    } else if (tipo == 'f') {
        printf("Real: %.2f\n", *((float *)ptr));    // cast para float*
    }
}