#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int valor;
    struct No *prox;
} No;

No *no_criar(int valor);

int main(void){
    int num;
    scanf("%d", &num);

    No *start;
    start  = no_criar(num);

    printf("%d\n", start->valor);
    if (start->prox == NULL)
        printf("prox: (nil)");
    return 0;
}

No *no_criar(int valor) {
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL) return NULL;

    novo->valor = valor;
    novo->prox = NULL; 

    return novo;
}