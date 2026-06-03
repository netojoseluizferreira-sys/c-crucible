// 079 — A Mesa dos Condenados (void*)
// Lê um caractere C e um inteiro N. Preenche um bloco de memória
// de tamanho N com o valor de C usando um ponteiro void* e cast.
// Imprime o bloco como uma string.
#include <stdio.h>

int main(void) {
    char letra;
    int rep;

    scanf("%c %d", &letra, &rep);

    char arr[rep + 1];  // +1 para o '\0'
    void *c_generico = &letra;  // ponteiro genérico

    // Cast de void* para char* e preenchimento
    char *c = (char *)c_generico;
    for (int i = 0; i < rep; i++) {
        *(arr + i) = *c;
    }
    *(arr + rep) = '\0';  // fecha a string

    printf("%s\n", arr);

    return 0;
}