// 102 — A Teia de Aranha (Ponteiros Triplos)
// Demonstra três níveis de indireção. Declara uma variável inteira,
// constrói uma cadeia de ponteiros com três níveis, modifica o valor
// original através do ponteiro triplo e imprime o valor final.
//
// Cadeia: ppp → pp → p → n
// ***ppp acessa o valor de n através de três indireções.
#include <stdio.h>

int main(void) {
    int n = 7;           // variável original
    int *p = &n;         // nível 1: ponteiro para n
    int **pp = &p;       // nível 2: ponteiro para ponteiro
    int ***ppp = &pp;    // nível 3: ponteiro para ponteiro para ponteiro

    // Modifica n através do ponteiro triplo
    ***ppp += 770;       // n = 7 + 770 = 777

    // Todos os níveis de acesso apontam para o mesmo valor final
    printf("%d\n", n);

    return 0;
}