// 158 — Split e Vector de Strings
// Lê uma linha de texto, divide em palavras separadas por espaço,
// armazena cada uma em um Vector de strings e imprime em ordem e depois inversa.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **strings;
    int tamanho;
    int capacidade;
} Vector;

Vector *vector_criar(void);
void vetor_inserir(Vector **v, const char *str);
void vector_liberar(Vector **v);
void vector_imprimir(const Vector *v);

int main(void) {
    Vector *vetor = vector_criar();
    if (vetor == NULL) return 1;

    char frase[200];
    fgets(frase, sizeof(frase), stdin);

    // Remove o '\n' final do fgets
    size_t len = strlen(frase);
    if (frase[len - 1] == '\n') {
        frase[len - 1] = '\0';
    }

    // Percorre a frase e divide por espaços
    char *inicio = frase;
    for (char *p = frase; ; p++) {
        if (*p == ' ' || *p == '\0') {
            // Encontrou delimitador: isola a palavra
            char temp = *p;
            *p = '\0';
            if (*inicio != '\0') {
                vetor_inserir(&vetor, inicio);
            }
            *p = temp;
            inicio = p + 1;
            if (temp == '\0') break;
        }
    }

    // Imprime em ordem direta
    printf("Ordem direta:\n");
    vector_imprimir(vetor);

    // Imprime em ordem inversa
    printf("\nOrdem inversa:\n");
    for (int i = vetor->tamanho - 1; i >= 0; i--) {
        printf("%s\n", vetor->strings[i]);
    }

    vector_liberar(&vetor);
    return 0;
}

// Cria um Vector vazio
Vector *vector_criar(void) {
    Vector *vetor = (Vector *)malloc(sizeof(Vector));
    if (vetor == NULL) return NULL;

    vetor->tamanho = 0;
    vetor->capacidade = 2;

    vetor->strings = (char **)malloc((size_t)vetor->capacidade * sizeof(char *));
    if (vetor->strings == NULL) {
        free(vetor);
        return NULL;
    }
    return vetor;
}

// Insere uma cópia da string no vetor
void vetor_inserir(Vector **v, const char *str) {
    if (v == NULL || *v == NULL || str == NULL) return;

    // Realoca se necessário
    if ((*v)->tamanho >= (*v)->capacidade) {
        int nova_cap = (*v)->capacidade * 2;
        char **temp = (char **)realloc((*v)->strings, (size_t)nova_cap * sizeof(char *));
        if (temp == NULL) return;
        (*v)->strings = temp;
        (*v)->capacidade = nova_cap;
    }

    // Aloca nova string e copia o conteúdo (cópia profunda)
    size_t comprimento = strlen(str) + 1;
    (*v)->strings[(*v)->tamanho] = (char *)malloc(comprimento);
    if ((*v)->strings[(*v)->tamanho] == NULL) return;

    strcpy((*v)->strings[(*v)->tamanho], str);
    (*v)->tamanho++;
}

// Libera todas as strings, o array e a struct
void vector_liberar(Vector **v) {
    if (v == NULL || *v == NULL) return;

    for (int i = 0; i < (*v)->tamanho; i++) {
        free((*v)->strings[i]);
        (*v)->strings[i] = NULL;
    }
    free((*v)->strings);
    (*v)->strings = NULL;
    free(*v);
    *v = NULL;
}

// Imprime as strings uma por linha
void vector_imprimir(const Vector *v) {
    if (v == NULL) return;
    for (int i = 0; i < v->tamanho; i++) {
        printf("%s\n", v->strings[i]);
    }
}