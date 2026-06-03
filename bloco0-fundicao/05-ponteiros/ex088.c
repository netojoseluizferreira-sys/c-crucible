// 088 — A Sala dos Espectros (Ponteiros para Structs)
// Lê um nome e uma idade para uma struct, acessando e imprimindo
// os campos exclusivamente através de um ponteiro para a struct.
//
// Demonstra duas formas equivalentes de acesso via ponteiro:
// - ptr->campo    (operador seta, mais idiomático)
// - (*ptr).campo  (desreferência explícita, mais didático)
#include <stdio.h>

int main(void) {
    // Define a struct que representa um espectro (alma)
    typedef struct {
        char nome[50];
        int  idade;
    } Demon;

    Demon d1;           // instância da struct
    Demon *ptr = &d1;   // ponteiro para a struct

    // Leitura via ponteiro (operador seta)
    scanf("%s %d", ptr->nome, &ptr->idade);

    // Impressão usando as duas formas de acesso via ponteiro
    printf("Nome: %s\nIdade: %d\n", ptr->nome, (*ptr).idade);

    return 0;
}