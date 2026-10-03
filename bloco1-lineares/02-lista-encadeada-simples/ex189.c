// 189 — Dividir ao Meio
// Divide a lista em duas metades: esquerda (primeira) e direita (segunda).
// A lista original fica vazia (cabeça = NULL).
// Reaproveita a função partir, que usa o algoritmo do ponteiro lento/rápido.
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
No *inverter_recursivo(No *cabeca);
int contar_pares(No *cabeca);
No *copiar(No *cabeca);
void concatenar(No **cabeca1, No *cabeca2);
int tem_ciclo(No *cabeca);
No *mesclar(No *l1, No *l2);
No *meio(No *cabeca);
void partir(No *fonte, No **frente, No **tras);
void mergeSort(No **cabeca);
int nesimo_do_fim(No *cabeca, int k);

int main(void) {
    int n1, v;
    No *esq = NULL;
    No *dir = NULL;

    // Lê a lista
    No *cabeca = NULL;
    scanf("%d", &n1);
    for (int i = 0; i < n1; i++) {
        scanf("%d", &v);
        inserir_final(&cabeca, v);
    }

    printf("Antes:   ");
    imprimir(cabeca);

    // Divide ao meio — partir corta a lista em duas
    partir(cabeca, &esq, &dir);

    // A lista original ficou fragmentada: só esq e dir têm nós agora
    // Setar cabeca = NULL para não ter ponteiro solto
    cabeca = NULL;

    printf("Esquerda: ");
    imprimir(esq);

    printf("Direita:  ");
    imprimir(dir);

    // Libera as duas metades
    destruir_lista(&esq);
    destruir_lista(&dir);

    return 0;
}

// Aloca um novo nó
No *no_criar(int valor) {
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL) return NULL;

    novo->valor = valor;
    novo->prox = NULL;

    return novo;
}

// Insere no final
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

// Libera toda a lista
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

// Busca um valor
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

// Remove a primeira ocorrência de um valor
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

// Insere em posição
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

// Insere no início
void inserir_inicio(No **cabeca, int valor) {
    No *novo = no_criar(valor);
    if (novo == NULL) return;

    novo->prox = *cabeca;
    *cabeca = novo;
}

// Remove em posição
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

// Imprime a lista
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

// Inverte iterativamente
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

// Inverte recursivamente
No *inverter_recursivo(No *cabeca) {
    if (cabeca == NULL || cabeca->prox == NULL) {
        return cabeca;
    }

    No *novaCabeca = inverter_recursivo(cabeca->prox);

    cabeca->prox->prox = cabeca;
    cabeca->prox = NULL;

    return novaCabeca;
}

// Conta pares
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

// Cópia profunda
No *copiar(No *cabeca) {
    No *copia = NULL;

    No *atual = cabeca;
    while (atual != NULL) {
        inserir_final(&copia, atual->valor);
        atual = atual->prox;
    }

    return copia;
}

// Concatena valores
void concatenar(No **cabeca1, No *cabeca2) {
    No *atual = cabeca2;

    while (atual != NULL) {
        inserir_final(cabeca1, atual->valor);
        atual = atual->prox;
    }
}

// Floyd
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

// Merge de listas ordenadas
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

// Encontra o nó do meio
No *meio(No *cabeca) {
    No *slow = cabeca;
    No *fast = cabeca->prox;

    while (fast != NULL && fast->prox != NULL && fast->prox->prox != NULL) {
        slow = slow->prox;
        fast = fast->prox->prox;
    }

    return slow;
}

// Divide a lista em duas metades
// frente = primeira metade (cabeça até o meio)
// tras   = segunda metade (do próximo do meio até o fim)
// O prox do último nó da primeira metade é cortado (NULL)
void partir(No *fonte, No **frente, No **tras) {
    // Lista vazia ou com 1 nó: segunda metade é NULL
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

    // Corta a conexão — o meio passa a ser o último da primeira metade
    no_meio->prox = NULL;
}

// Merge Sort
void mergeSort(No **cabeca) {
    No *atual = *cabeca;
    No *a;
    No *b;

    if (!atual || !(atual->prox)) {
        return;
    }

    partir(*cabeca, &a, &b);

    mergeSort(&a);
    mergeSort(&b);

    *cabeca = mesclar(a, b);
}

// Encontra o k-ésimo nó a partir do fim
int nesimo_do_fim(No *cabeca, int k) {
    if (k <= 0) return -1;

    No *slow = cabeca;
    No *fast = cabeca;

    for (int i = 0; i < k - 1; i++) {
        if (fast == NULL) return -1;
        fast = fast->prox;
    }

    if (fast == NULL) return -1;

    while (fast->prox != NULL) {
        slow = slow->prox;
        fast = fast->prox;
    }

    return slow->valor;
}