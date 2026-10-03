// 186 — Merge Sort em Lista
// Ordena a lista encadeada com merge sort recursivo.
// Divide ao meio, ordena cada metade e mescla as duas.
#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *prox;
} No;

No *no_criar(int valor);
void inserir_final(No **cabeca, int valor);
void inserir_meio(No **cabeca, int valor, int posicao);
void inserir_inicio(No **cabeca, int valor);
void destruir_lista(No **cabeca);
int buscar(No *cabeca, int alvo);
void remover_inicio(No **cabeca);
void remover_final(No **cabeca);
void remover_valor(No **cabeca, int valor);
void remover_meio(No **cabeca, int posicao);
void imprimir(No *cabeca);
void inverter_lista(No **cabeca);
int contar_pares(No *cabeca);
No *copiar(No *cabeca);
void concatenar(No **cabeca1, No *cabeca2);
int tem_ciclo(No *cabeca);
No *mesclar(No *l1, No *l2);
No *meio(No *cabeca);
void partir(No *fonte, No **frente, No **tras);
void mergeSort(No **cabeca);

int main(void) {
    int n1, v;

    // Lê a lista do usuário
    No *cabeca = NULL;
    scanf("%d", &n1);
    for (int i = 0; i < n1; i++) {
        scanf("%d", &v);
        inserir_final(&cabeca, v);
    }

    printf("Antes: ");
    imprimir(cabeca);

    mergeSort(&cabeca);

    printf("Depois: ");
    imprimir(cabeca);

    destruir_lista(&cabeca);

    return 0;
}

// Aloca um novo nó com o valor fornecido e prox = NULL
No *no_criar(int valor) {
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL) return NULL;

    novo->valor = valor;
    novo->prox = NULL;

    return novo;
}

// Insere um novo nó no FINAL da lista
void inserir_final(No **cabeca, int valor) {
    No *novo = no_criar(valor);
    if (novo == NULL) return;

    if (*cabeca == NULL) {
        *cabeca = novo;
        return;
    }

    No *atual = *cabeca;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }

    atual->prox = novo;
}

// Libera todos os nós e seta *cabeca para NULL
void destruir_lista(No **cabeca) {
    if (cabeca == NULL || *cabeca == NULL) return;

    No *atual = *cabeca;
    while (atual != NULL) {
        No *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    *cabeca = NULL;
}

// Busca um valor e retorna o índice da primeira ocorrência (ou -1)
int buscar(No *cabeca, int alvo) {
    int indice = 0;
    No *atual = cabeca;

    while (atual != NULL) {
        if (atual->valor == alvo) return indice;
        atual = atual->prox;
        indice++;
    }

    return -1;
}

// Remove o primeiro nó
void remover_inicio(No **cabeca) {
    if (cabeca == NULL || *cabeca == NULL) return;

    No *atual = *cabeca;
    No *proximo = atual->prox;

    free(atual);
    *cabeca = proximo;
}

// Remove o último nó
void remover_final(No **cabeca) {
    if (cabeca == NULL || *cabeca == NULL) return;

    No *atual = *cabeca;

    if (atual->prox == NULL) {
        free(atual);
        *cabeca = NULL;
        return;
    }

    while (atual->prox->prox != NULL) {
        atual = atual->prox;
    }

    free(atual->prox);
    atual->prox = NULL;
}

// Remove a primeira ocorrência de um valor usando ponteiro duplo
void remover_valor(No **cabeca, int valor) {
    if (cabeca == NULL || *cabeca == NULL) return;

    No **atual = cabeca;

    while (*atual != NULL) {
        if ((*atual)->valor == valor) {
            No *remover = *atual;
            *atual = remover->prox;
            free(remover);
            return;
        }
        atual = &(*atual)->prox;
    }
}

// Insere um novo nó na posição indicada (0-indexada)
void inserir_meio(No **cabeca, int valor, int posicao) {
    No *novo = no_criar(valor);
    if (novo == NULL) return;

    if (*cabeca == NULL || posicao <= 0) {
        novo->prox = *cabeca;
        *cabeca = novo;
        return;
    }

    No *atual = *cabeca;
    int indice = 0;

    while (atual->prox != NULL && indice < posicao - 1) {
        atual = atual->prox;
        indice++;
    }

    novo->prox = atual->prox;
    atual->prox = novo;
}

// Insere um novo nó no INÍCIO da lista
void inserir_inicio(No **cabeca, int valor) {
    No *novo = no_criar(valor);
    if (novo == NULL) return;

    novo->prox = *cabeca;
    *cabeca = novo;
}

// Remove o nó na posição indicada (0-indexada)
void remover_meio(No **cabeca, int posicao) {
    if (cabeca == NULL || *cabeca == NULL) return;

    if (posicao <= 0) {
        remover_inicio(cabeca);
        return;
    }

    No *atual = *cabeca;
    int indice = 0;

    while (atual->prox != NULL && indice < posicao - 1) {
        atual = atual->prox;
        indice++;
    }

    if (atual->prox == NULL) return;

    No *remover = atual->prox;
    atual->prox = remover->prox;
    free(remover);
}

// Imprime a lista no formato [a,b,c] ou LISTA DESTRUIDA se vazia
void imprimir(No *cabeca) {
    No *atual = cabeca;
    if (atual == NULL) {
        printf("LISTA DESTRUIDA\n");
        return;
    }
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->prox;
    }
    printf("NULL\n");
}

// Inverte a lista iterativamente com três ponteiros
void inverter_lista(No **cabeca) {
    if (cabeca == NULL || *cabeca == NULL || (*cabeca)->prox == NULL) {
        return;
    }

    No *anterior = NULL;
    No *atual = *cabeca;
    No *proximo = NULL;

    while (atual != NULL) {
        proximo = atual->prox;
        atual->prox = anterior;
        anterior = atual;
        atual = proximo;
    }

    *cabeca = anterior;
}

// Conta quantos valores pares existem na lista
int contar_pares(No *cabeca) {
    int pares = 0;
    No *atual = cabeca;

    while (atual != NULL) {
        if (atual->valor % 2 == 0) {
            pares++;
        }
        atual = atual->prox;
    }

    return pares;
}

// Cria uma nova lista com os mesmos valores (cópia profunda)
No *copiar(No *cabeca) {
    No *copia = NULL;

    No *atual = cabeca;
    while (atual != NULL) {
        inserir_final(&copia, atual->valor);
        atual = atual->prox;
    }

    return copia;
}

// Anexa os valores da segunda lista ao final da primeira
void concatenar(No **cabeca1, No *cabeca2) {
    No *atual = cabeca2;

    while (atual != NULL) {
        inserir_final(cabeca1, atual->valor);
        atual = atual->prox;
    }
}

// Detecta ciclo usando o algoritmo de Floyd (tartaruga e lebre)
int tem_ciclo(No *cabeca) {
    No *slow = cabeca;
    No *fast = cabeca;

    while (fast != NULL && fast->prox != NULL) {
        slow = slow->prox;
        fast = fast->prox->prox;
        if (slow == fast) return 1;
    }

    return 0;
}

// Mescla duas listas ordenadas em uma terceira, preservando a ordem
No *mesclar(No *l1, No *l2) {
    No *copia = NULL;
    No *atual1 = l1;
    No *atual2 = l2;

    while (atual1 != NULL && atual2 != NULL) {
        if (atual1->valor < atual2->valor) {
            inserir_final(&copia, atual1->valor);
            atual1 = atual1->prox;
        } else {
            inserir_final(&copia, atual2->valor);
            atual2 = atual2->prox;
        }
    }

    while (atual1 != NULL) {
        inserir_final(&copia, atual1->valor);
        atual1 = atual1->prox;
    }

    while (atual2 != NULL) {
        inserir_final(&copia, atual2->valor);
        atual2 = atual2->prox;
    }

    return copia;
}

// Encontra o nó do meio e o RETORNA (não o valor)
// Usado pelo partir para dividir a lista
No *meio(No *cabeca) {
    No *slow = cabeca;
    No *fast = cabeca;

    while (fast != NULL && fast->prox != NULL && fast->prox->prox != NULL) {
        slow = slow->prox;
        fast = fast->prox->prox;
    }

    return slow;
}

// Divide a lista em duas metades: frente (primeira) e tras (segunda)
// Usa o meio para achar o ponto de corte
void partir(No *fonte, No **frente, No **tras) {
    // Caso base: lista vazia ou com 1 elemento
    if (fonte == NULL || fonte->prox == NULL) {
        *frente = fonte;
        *tras = NULL;
        return;
    }

    // Acha o nó do meio
    No *no_meio = meio(fonte);

    // Configura as duas metades
    *frente = fonte;
    *tras = no_meio->prox;

    // Corta a conexão entre as duas listas
    no_meio->prox = NULL;
}

// Merge Sort recursivo em lista encadeada
// Divide a lista ao meio, ordena cada metade e mescla
void mergeSort(No **cabeca) {
    No *atual = *cabeca;
    No *a;
    No *b;

    // Caso base: lista vazia ou com 1 elemento (já ordenada)
    if (!atual || !(atual->prox)) {
        return;
    }

    // Divide a lista em duas metades
    partir(*cabeca, &a, &b);

    // Ordena recursivamente cada metade
    mergeSort(&a);
    mergeSort(&b);

    // Intercala as duas metades ordenadas
    *cabeca = mesclar(a, b);
}