#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *array;
    int tamanho;
    int capacidade;
    int remove_nums;
} Vector;

int funcao_criterio(int paridade);
void vector_remover_se(Vector **v, char paridade, int (*criterio)(int));

int main(void){
    size_t n;
    char par;
    Vector *vetor = (Vector *)malloc(sizeof(Vector));
    if (vetor == NULL) return 1;
    
    scanf("%zu", &n);
    scanf(" %c", &par);

    vetor->tamanho = 0;
    vetor->capacidade = (int)n;
    vetor->remove_nums = 0;
    
    vetor->array = (int *)malloc(n * sizeof(int));
    if (vetor->array == NULL) { free(vetor); return 1; }

    for (size_t i = 0; i < n; i++){
        scanf("%d", vetor->array+i);
        vetor->tamanho++;
    }

    vector_remover_se(&vetor, par, funcao_criterio);

    for (size_t i = 0; i < n; i++){
        printf("%d ", vetor->array[i]);
    }

    return 0;
}

void vector_remover_se(Vector **v, char paridade, int (*criterio)(int)){   
    int i = (*v)->tamanho - 1;
    if (v == NULL || *v == NULL) return;  

    while (i >= 0) {
        int deve_remover = 0;
        int valor = (*v)->array[i];

        if ((paridade == 'p' || paridade == 'P') && criterio(valor) == 1) {
            deve_remover = 1;
        } else if ((paridade == 'i' || paridade == 'I') && criterio(valor) == 0) {
            deve_remover = 1;
        }

        if (deve_remover) {
            for (int pos = i; pos < (*v)->tamanho - 1; pos++) {
                (*v)->array[pos] = (*v)->array[pos + 1];
            }
            (*v)->tamanho--;
            (*v)->remove_nums++;
        } else {
            i--;
    }

    
/*
        if ((*v)->tamanho >= (*v)->capacidade) {
        int nova_cap = (*v)->capacidade * 2;

        size_t tamanho_bytes = (size_t)nova_cap * sizeof(int);
        int *temp = (int *)realloc((*v)->array, tamanho_bytes);
        if (temp == NULL) return;

        (*v)->array = temp;
        (*v)->capacidade = nova_cap;
    }
*/
}
}

int funcao_criterio(int paridade){
    if (paridade % 2 == 0) return 1;
    else return 0;
}