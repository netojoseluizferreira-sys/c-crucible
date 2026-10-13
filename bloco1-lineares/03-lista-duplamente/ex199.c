// 199 — Remoção nas Pontas
// Remove do início e do final da lista dupla, ajustando cabeca e cauda.
// Testa as quatro operações: inserir_inicio, inserir_final, remover_inicio,
// remover_final — transferindo nós entre duas listas.
#include <stdio.h>
#include <stdlib.h>

// Nó da lista dupla: valor + ponteiro para o próximo e para o anterior
typedef struct NoDuplo {
    int valor;
    struct NoDuplo *prox;
    struct NoDuplo *ant;
} NoDuplo;

// Lista dupla: guarda o primeiro e o último nó.
typedef struct ListaDupla {
    NoDuplo *cabeca;
    NoDuplo *cauda;
} ListaDupla;

// Protótipos
NoDuplo *noDuplo_criar(int valor);
void inserir_inicio(ListaDupla *l, int valor);
void inserir_final(ListaDupla *l, int valor);
void imprimir_frente(ListaDupla *l);
void destruir_lista(ListaDupla *l);
void remover_inicio(ListaDupla *l);
void remover_final(ListaDupla *l);

int main(void) {
    int num, v;

    scanf("%d", &num);

    // Cria duas listas vazias
    ListaDupla *l = (ListaDupla *)malloc(sizeof(ListaDupla));
    if (l == NULL) return 1;
    l->cabeca = NULL;
    l->cauda = NULL;

    ListaDupla *l2 = (ListaDupla *)malloc(sizeof(ListaDupla));
    if (l2 == NULL) return 1;
    l2->cabeca = NULL;
    l2->cauda = NULL;

    // Lê N valores e insere em l (no final)
    for (int i = 0; i < num; i++) {
        scanf("%d", &v);
        inserir_final(l, v);
    }

    // Estado inicial: l tem os valores, l2 vazia
    imprimir_frente(l);
    imprimir_frente(l2);

    // Transfere de l para l2: pega o primeiro de l, joga no final de l2.
    // Como remove sempre o início, l fica na ordem original.
    // l2 também fica na ordem original (inserindo no final).
    for (int i = 0; i < num; i++) {
        inserir_final(l2, l->cabeca->valor);  // pega o primeiro de l
        remover_inicio(l);                     // remove de l
    }

    // l deve estar vazia, l2 deve ter os valores
    imprimir_frente(l);
    imprimir_frente(l2);

    // Transfere de l2 para l: pega o primeiro de l2, insere no início de l.
    // Isso INVERTE a ordem em l.
    for (int i = 0; i < num; i++) {
        inserir_final(l, l2->cauda->valor);  // pega o último de l2
        remover_final(l2);                      // remove do final de l2
    }

    // l agora tem os valores invertidos, l2 vazia
    imprimir_frente(l);
    imprimir_frente(l2);

    // Libera tudo
    destruir_lista(l);
    free(l);

    destruir_lista(l2);
    free(l2);

    return 0;
}

// Aloca um nó com valor, prox e ant = NULL
NoDuplo *noDuplo_criar(int valor) {
    NoDuplo *novo = (NoDuplo *)malloc(sizeof(NoDuplo));
    if (novo == NULL) return NULL;

    novo->valor = valor;
    novo->prox = NULL;
    novo->ant = NULL;

    return novo;
}

// Insere no INÍCIO em O(1)
void inserir_inicio(ListaDupla *l, int valor) {
    NoDuplo *novo = noDuplo_criar(valor);
    if (novo == NULL) return;

    novo->ant = NULL;
    novo->prox = l->cabeca;

    if (l->cabeca == NULL) {
        // Lista vazia: novo é o único nó
        l->cabeca = novo;
        l->cauda = novo;
    } else {
        // A ordem importa: usa l->cabeca antes de sobrescrever
        l->cabeca->ant = novo;
        l->cabeca = novo;
    }
}

// Insere no FINAL em O(1)
void inserir_final(ListaDupla *l, int valor) {
    NoDuplo *novo = noDuplo_criar(valor);
    if (novo == NULL) return;

    novo->prox = NULL;
    novo->ant = l->cauda;

    if (l->cauda == NULL) {
        // Lista vazia: novo é o único nó
        l->cabeca = novo;
        l->cauda = novo;
    } else {
        // A ordem importa: usa l->cauda antes de sobrescrever
        l->cauda->prox = novo;
        l->cauda = novo;
    }
}

// Imprime a lista do INÍCIO ao FIM
void imprimir_frente(ListaDupla *l) {
    NoDuplo *atual = l->cabeca;
    if (atual == NULL) {
        printf("LISTA VAZIA\n");
        return;
    }
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->prox;
    }
    printf("NULL\n");
}

// Libera todos os nós da lista e reseta cabeca/cauda
void destruir_lista(ListaDupla *l) {
    NoDuplo *atual = l->cabeca;

    while (atual != NULL) {
        NoDuplo *proximo = atual->prox;  // guarda antes de liberar
        free(atual);
        atual = proximo;
    }

    l->cabeca = NULL;
    l->cauda = NULL;
}

// Remove o primeiro nó em O(1)
// Casos: lista vazia (nada a fazer), lista com 1 nó (fica vazia),
// lista com 2+ nós (cabeca vira o segundo)
void remover_inicio(ListaDupla *l) {
    if (l == NULL || l->cabeca == NULL) return;

    NoDuplo *remover = l->cabeca;

    if (remover == l->cauda) {
        // Único nó: lista fica vazia
        l->cabeca = NULL;
        l->cauda = NULL;
    } else {
        // Mais de um nó: o segundo vira cabeca
        l->cabeca = remover->prox;
        l->cabeca->ant = NULL;   // o novo primeiro não tem anterior
    }

    free(remover);
}

// Remove o último nó em O(1)
// Casos: lista vazia (nada a fazer), lista com 1 nó (fica vazia),
// lista com 2+ nós (cauda vira o penúltimo)
void remover_final(ListaDupla *l) {
    if (l == NULL || l->cauda == NULL) return;

    NoDuplo *remover = l->cauda;

    if (remover == l->cabeca) {
        // Único nó: lista fica vazia
        l->cabeca = NULL;
        l->cauda = NULL;
    } else {
        // Mais de um nó: o penúltimo vira cauda
        l->cauda = remover->ant;
        l->cauda->prox = NULL;   // o novo último não tem próximo
    }

    free(remover);
}