// 124 — O Vórtice de Realocação (realloc com Loop)
// Lê inteiros continuamente até que -1 seja digitado. Começa com NULL
// e, a cada novo valor (exceto -1), usa realloc para expandir o array
// em uma posição e armazenar o valor. Imprime todos os valores lidos
// e libera a memória.
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // Começa com NULL (sem memória alocada)
    int *p = NULL;
    int control, i = 0;
    
    while (1) {
        scanf("%d", &control);

        if (control == -1) {
            break;
        }

        // Expande o array em uma posição usando realloc
        // Uso seguro: atribui a temp antes de sobrescrever p
        int *temp = (int *)realloc(p, ((size_t)i + 1) * sizeof(int));
        if (temp == NULL) {
            // Se realloc falhar, p (se não NULL) ainda é válido e precisa ser liberado
            free(p);
            return 1;
        }
        p = temp;

        // Armazena o valor lido na nova posição
        *(p + i) = control;
        i++;
    }

    // Impressão de todos os valores usando aritmética de ponteiros
    for (int j = 0; j < i; j++) {
        printf("%d ", *(p + j));
    }
    printf("\n");

    // Libera a memória (se p != NULL; se i == 0, p é NULL e free(NULL) é seguro)
    free(p);
    p = NULL;

    return 0;
}