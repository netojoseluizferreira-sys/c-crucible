// 198 — Travessia nas Duas Direções
// Monta uma lista dupla de inteiros e imprime em ambas as direções.
// Depois modifica o primeiro nó e imprime novamente para provar que
// os vínculos prox/ant estão consistentes.
#include <stdio.h>
#include <stdlib.h>

// Nó da lista dupla: valor + ponteiro para o próximo e para o anterior
typedef struct NoDuplo {
    int valor;
    struct NoDuplo *prox;
    struct NoDuplo *ant;
} NoDuplo;

// Lista dupla: guarda o primeiro e o último nó.
// Ter os dois ponteiros permite inserção O(1) nas duas pontas,
// sem precisar percorrer a lista.
//
// Sobre o tipo do parâmetro nas funções:
//   As funções recebem ListaDupla * (ponteiro para struct).
//   Modificar l->cabeca e l->cauda dentro da função persiste no caller
//   porque l aponta para a struct real, não para uma cópia.
//   Só seria necessário ListaDupla ** se a função fosse trocar a struct
//   inteira ou modificar o próprio ponteiro l (não é o caso aqui).
typedef struct ListaDupla {
    NoDuplo *cabeca;
    NoDuplo *cauda;
} ListaDupla;

// Protótipos
NoDuplo *noDuplo_criar(int valor);
void inserir_inicio(ListaDupla *l, int valor);
void inserir_final(ListaDupla *l, int valor);
void imprimir_frente(ListaDupla *l);
void imprimir_tras(ListaDupla *l);
void destruir_lista(ListaDupla *l);

int main(void) {
    int num, v;

    // Lê quantos valores serão inseridos
    scanf("%d", &num);

    // Aloca a struct da lista e inicializa vazia.
    // Cabeca = NULL e cauda = NULL indicam lista sem nós.
    ListaDupla *l = (ListaDupla *)malloc(sizeof(ListaDupla));
    if (l == NULL) return 1;
    l->cabeca = NULL;
    l->cauda = NULL;

    // Lê N valores e insere no FINAL, um a um
    for (int i = 0; i < num; i++) {
        scanf("%d", &v);
        inserir_final(l, v);
    }

    // Imprime nas duas direções para mostrar os vínculos funcionando
    imprimir_frente(l);
    imprimir_tras(l);

    // Modifica o valor do PRIMEIRO nó (acrescenta 8).
    // Depois imprime de novo nas duas direções para mostrar que a
    // mudança aparece em ambas — prova que os nós são os MESMOS,
    // acessados por caminhos diferentes (ida ou volta).
    (l->cabeca)->valor += 8;

    imprimir_frente(l);
    imprimir_tras(l);

    // Libera todos os nós e depois a struct da lista
    destruir_lista(l);
    free(l);

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
// Lista vazia: novo é cabeca e cauda
// Lista não vazia: novo vira cabeca, antigo primeiro aponta para trás
void inserir_inicio(ListaDupla *l, int valor) {
    NoDuplo *novo = noDuplo_criar(valor);
    if (novo == NULL) return;

    // Novo é o primeiro: ninguém antes dele
    novo->ant = NULL;

    // Novo aponta para o antigo primeiro (pode ser NULL se lista vazia)
    novo->prox = l->cabeca;

    if (l->cabeca == NULL) {
        // Lista vazia: o novo é o único nó → é cabeca e cauda ao mesmo tempo
        l->cabeca = novo;
        l->cauda = novo;
    } else {
        // Lista não vazia:
        //   1) o antigo primeiro aponta para trás, para o novo
        //   2) cabeca passa a ser o novo
        // A ordem importa: o passo 1 usa l->cabeca antes de sobrescrevê-lo.
        l->cabeca->ant = novo;
        l->cabeca = novo;
    }
}

// Insere no FINAL em O(1)
// Lista vazia: novo é cabeca e cauda
// Lista não vazia: novo vira cauda, antigo último aponta para frente
void inserir_final(ListaDupla *l, int valor) {
    NoDuplo *novo = noDuplo_criar(valor);
    if (novo == NULL) return;

    // Novo é o último: ninguém depois dele
    novo->prox = NULL;

    // Novo aponta para trás, para o antigo último (NULL se lista vazia)
    novo->ant = l->cauda;

    if (l->cauda == NULL) {
        // Lista vazia: o novo é o único nó → é cabeca e cauda ao mesmo tempo
        l->cabeca = novo;
        l->cauda = novo;
    } else {
        // Lista não vazia:
        //   1) o antigo último aponta para frente, para o novo
        //   2) cauda passa a ser o novo
        // A ordem importa: o passo 1 usa l->cauda antes de sobrescrevê-lo.
        l->cauda->prox = novo;
        l->cauda = novo;
    }
}

// Imprime a lista do INÍCIO ao FIM, seguindo o ponteiro 'prox'.
// Se a saída for coerente com a de imprimir_tras, os vínculos de ida
// estão consistentes.
void imprimir_frente(ListaDupla *l) {
    NoDuplo *atual = l->cabeca;   // começa pela cabeca
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->prox;       // anda para frente
    }
    printf("NULL\n");
}

// Imprime a lista do FIM ao INÍCIO, seguindo o ponteiro 'ant'.
// Complementa o imprimir_frente: se as duas saídas forem coerentes,
// os vínculos (prox e ant) estão consistentes.
void imprimir_tras(ListaDupla *l) {
    NoDuplo *atual = l->cauda;    // começa pela cauda
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->ant;        // anda para trás
    }
    printf("NULL\n");
}

// Libera todos os nós da lista.
// Guarda o proximo antes do free para não perder a referência.
// Ao final, reseta cabeca e cauda para NULL, evitando dangling pointers
// caso a struct seja usada depois.
void destruir_lista(ListaDupla *l) {
    NoDuplo *atual = l->cabeca;

    while (atual != NULL) {
        NoDuplo *proximo = atual->prox;  // guarda antes de liberar
        free(atual);
        atual = proximo;
    }

    // Zera os ponteiros da struct: lista fica em estado "vazia" válido
    l->cabeca = NULL;
    l->cauda = NULL;
}