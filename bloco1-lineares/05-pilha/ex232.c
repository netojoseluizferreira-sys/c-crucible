// 232 — Pilha com Array Dinâmico
// Pilha com array alocado dinamicamente que dobra de capacidade quando
// enche. Capacidade inicial 2, cresce com realloc.
// O main empilha, imprime, desempilha, imprime, empilha de novo e
// imprime. Ao final, libera a pilha.
#include <stdio.h>
#include <stdlib.h>

// Pilha com array dinâmico: dados + topo + capacidade
typedef struct {
    int *array;
    int topo;
    int capacidade;
} Pilha;

// Protótipos
Pilha *pilha_criar(void);
void empilhar(Pilha **v, int num);
int desempilhar(Pilha **v, int *elemento);
int peek(Pilha *v, int *valor);
int esta_vazia(Pilha *v);
void str(const Pilha *v);
void pilha_liberar(Pilha **v);

int main(void) {
    Pilha *p = pilha_criar();
    if (p == NULL) return 1;

    // Empilha 0..4 (5 elementos, dobra a capacidade 2 -> 4 -> 8)
    for (int i = 0; i < 5; i++) {
        empilhar(&p, i);
        str(p);
    }

    // Desempilha 6 vezes: a 6ª falha porque a pilha está vazia
    for (int i = 0; i < 6; i++) {
        int elemento;
        if (desempilhar(&p, &elemento)) {
            printf("%d\n", elemento);
            str(p);
        } else {
            // desempilhar já imprimiu "Pilha vazia"
        }
    }

    // Empilha 0, 10, 20, 30, 40
    for (int i = 0; i < 5; i++) {
        empilhar(&p, i * 10);
        str(p);
    }

    pilha_liberar(&p);
    return 0;
}

// Cria uma pilha vazia com capacidade inicial 2
Pilha *pilha_criar(void) {
    Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));
    if (pilha == NULL) return NULL;

    pilha->topo = 0;
    pilha->capacidade = 2;

    pilha->array = (int *)calloc((size_t)pilha->capacidade, sizeof(int));
    if (pilha->array == NULL) {
        free(pilha);
        return NULL;
    }
    return pilha;
}

// Insere no topo, realocando se necessário (dobra a capacidade).
//
// Estratégia segura com realloc:
//   - Calcula a nova capacidade.
//   - Usa um ponteiro temporário 'temp' para o realloc.
//   - Se realloc falhar (retorna NULL), NÃO sobrescreve o array original
//     (evita perder a referência e vazar memória).
//   - Só atualiza array e capacidade se o realloc deu certo.
void empilhar(Pilha **v, int num) {
    if (v == NULL || *v == NULL) return;

    if ((*v)->topo >= (*v)->capacidade) {
        int nova_cap = (*v)->capacidade * 2;
        int *temp = (int *)realloc((*v)->array, (size_t)nova_cap * sizeof(int));
        if (temp == NULL) return;   // mantém o array original intacto

        (*v)->array = temp;
        (*v)->capacidade = nova_cap;
    }

    (*v)->array[(*v)->topo] = num;
    (*v)->topo++;
}

// Desempilha: recua o topo e devolve o valor via ponteiro.
// Retorna 1 em sucesso, 0 se a pilha estiver vazia.
int desempilhar(Pilha **v, int *elemento) {
    if (v == NULL || *v == NULL) return 0;

    if ((*v)->topo != 0) {
        (*v)->topo--;
        *elemento = (*v)->array[(*v)->topo];
        return 1;
    } else {
        printf("Pilha vazia\n");
        return 0;
    }
}

// Espia o topo sem remover. Retorna 1 em sucesso, 0 se vazia.
int peek(Pilha *v, int *valor) {
    if (v == NULL || v->topo == 0) return 0;

    *valor = v->array[v->topo - 1];
    return 1;
}

// Retorna 1 se a pilha estiver vazia, 0 caso contrário
int esta_vazia(Pilha *v) {
    return v->topo == 0;
}

// Imprime a pilha do TOPO até a BASE no formato [a,b,c]
void str(const Pilha *v) {
    if (v == NULL) return;

    if (v->topo == 0) {
        printf("[ PILHA VAZIA ]\n");
        return;
    }

    printf("[");
    for (int i = v->topo - 1; i >= 0; i--) {
        printf("%d", v->array[i]);
        if (i > 0) printf(",");
    }
    printf("]\n");
}

// Libera o array e a estrutura
void pilha_liberar(Pilha **v) {
    if (v == NULL || *v == NULL) return;
    free((*v)->array);
    (*v)->array = NULL;
    free(*v);
    *v = NULL;
}