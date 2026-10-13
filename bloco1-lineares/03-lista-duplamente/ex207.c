// 207 — Ordenação com Merge Sort em Lista Dupla
// Implementa Merge Sort para lista duplamente encadeada.
// Divide a lista ao meio (ponteiros rápido/lento), ordena recursivamente
// e mescla as metades religando os nós existentes (sem alocar novos).
// A função mesclar NÃO aloca nós: apenas reorganiza os ponteiros prox/ant.
// Ao final do merge sort, cabeca e cauda da struct são atualizadas.
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

// Cursor: aponta para a lista e para o nó atual.
typedef struct Cursor{
    ListaDupla *lista;
    NoDuplo *atual;
} Cursor;

// Protótipos
NoDuplo *noDuplo_criar(int valor);
void inserir_inicio(ListaDupla *l, int valor);
void inserir_final(ListaDupla *l, int valor);
int  inserir_posicao(ListaDupla *l, int valor, int pos);
void imprimir_frente(ListaDupla *l);
void destruir_lista(ListaDupla *l);
int remover_inicio(ListaDupla *l);
int remover_final(ListaDupla *l);
int remover_posicao(ListaDupla *l, int posicao);
void cursor_inicio(Cursor **c, ListaDupla *l);
void cursor_fim(Cursor **c, ListaDupla *l);
void cursor_avancar(Cursor **c);
void cursor_retroceder(Cursor **c);
int cursor_valor(Cursor *c);
int cursor_remover(Cursor **c, int *v);
void inverter_lista(ListaDupla *l);
void concatenar_listas(ListaDupla *l, ListaDupla *l2);
ListaDupla mesclar(ListaDupla *a, ListaDupla *b);
NoDuplo *meio(NoDuplo *cabeca);
void partir(NoDuplo *fonte, ListaDupla *frente, ListaDupla *tras);
void mergeSort(ListaDupla *l);

int main(void) {
    int num, v;

    // Lê a quantidade de valores que vão compor a lista
    scanf("%d", &num);

    // Cria a lista vazia
    ListaDupla *l = (ListaDupla *)malloc(sizeof(ListaDupla));
    if (l == NULL) return 1;
    l->cabeca = NULL;
    l->cauda = NULL;

    // Lê N valores e insere no final, um a um
    for (int i = 0; i < num; i++) {
        scanf("%d", &v);
        inserir_final(l, v);
    }

    // Estado original (desordenado)
    imprimir_frente(l);

    // Ordena in-place com merge sort
    mergeSort(l);

    // Estado final (ordenado)
    imprimir_frente(l);

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

// Insere em posição específica da lista dupla (1 = ok, 0 = inválida).
int inserir_posicao(ListaDupla *l, int valor, int pos) {
    if (pos < 0) return 0;

    if (l->cabeca == NULL || pos == 0) {
        inserir_inicio(l, valor);
        return 1;
    }

    NoDuplo *atual = l->cabeca;
    int i = 0;

    while (i < pos - 1 && atual->prox != NULL) {
        atual = atual->prox;
        i++;
    }

    if (atual->prox == NULL) {
        inserir_final(l, valor);
        return 1;
    }

    NoDuplo *novo = noDuplo_criar(valor);
    if (novo == NULL) return 0;

    NoDuplo *proximo = atual->prox;

    // Ajusta os 4 ponteiros do meio
    novo->ant = atual;
    novo->prox = proximo;
    atual->prox = novo;
    proximo->ant = novo;

    return 1;
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

// Libera todos os nós e reseta cabeca/cauda
void destruir_lista(ListaDupla *l) {
    NoDuplo *atual = l->cabeca;

    while (atual != NULL) {
        NoDuplo *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    l->cabeca = NULL;
    l->cauda = NULL;
}

// Remove o primeiro nó em O(1); retorna valor ou -1 se vazia.
int remover_inicio(ListaDupla *l) {
    if (l == NULL || l->cabeca == NULL) return -1;

    NoDuplo *remover = l->cabeca;

    if (remover == l->cauda) {
        // Único nó: lista fica vazia
        l->cabeca = NULL;
        l->cauda = NULL;
    } else {
        // Mais de um nó: o segundo vira cabeca
        l->cabeca = remover->prox;
        l->cabeca->ant = NULL;
    }

    int valor = remover->valor;
    free(remover);
    return valor;
}

// Remove o último nó em O(1); retorna valor ou -1 se vazia.
int remover_final(ListaDupla *l) {
    if (l == NULL || l->cauda == NULL) return -1;

    NoDuplo *remover = l->cauda;

    if (remover == l->cabeca) {
        // Único nó: lista fica vazia
        l->cabeca = NULL;
        l->cauda = NULL;
    } else {
        // Mais de um nó: o penúltimo vira cauda
        l->cauda = remover->ant;
        l->cauda->prox = NULL;
    }

    int valor = remover->valor;
    free(remover);
    return valor;
}

// Remove o nó na posição e retorna o valor removido, ou -1 se inválida.
int remover_posicao(ListaDupla *l, int posicao) {
    NoDuplo *cabeca = l->cabeca;
    if (cabeca == NULL) return -1;

    if (posicao <= 0) {
        return remover_inicio(l);
    }

    NoDuplo *atual = cabeca;
    int indice = 0;

    while (atual->prox != NULL && indice < posicao - 1) {
        atual = atual->prox;
        indice++;
    }

    if (atual->prox == NULL) return -1;

    NoDuplo *remover = atual->prox;
    int valor = remover->valor;

    atual->prox = remover->prox;
    if (remover->prox != NULL) {
        remover->prox->ant = atual;
    }

    free(remover);
    return valor;
}

// Posiciona o cursor no primeiro nó da lista.
void cursor_inicio(Cursor **c, ListaDupla *l){
    if (c == NULL || *c == NULL) return;
    if (l == NULL || l->cabeca == NULL) return;
    (*c)->lista = l;
    (*c)->atual = l->cabeca;
}

// Posiciona o cursor no último nó da lista.
void cursor_fim(Cursor **c, ListaDupla *l){
    if (c == NULL || *c == NULL) return;
    if (l == NULL || l->cauda == NULL) return;
    (*c)->lista = l;
    (*c)->atual = l->cauda;
}

// Avança o cursor um nó. Se já estiver no fim, não muda.
void cursor_avancar(Cursor **c){
    if (c == NULL || *c == NULL) return;
    if ((*c)->atual == NULL) return;
    if ((*c)->atual->prox != NULL){
        (*c)->atual = (*c)->atual->prox;
    }
}

// Retrocede o cursor um nó. Se já estiver no início, não muda.
void cursor_retroceder(Cursor **c){
    if (c == NULL || *c == NULL) return;
    if ((*c)->atual == NULL) return;
    if ((*c)->atual->ant != NULL){
        (*c)->atual = (*c)->atual->ant;
    }
}

// Retorna o valor do nó atual, ou -1 se o cursor for inválido.
int cursor_valor(Cursor *c){
    if (c == NULL || c->atual == NULL) return -1;
    return c->atual->valor;
}

// Remove o nó apontado pelo cursor, ajustando cabeca/cauda se necessário.
int cursor_remover(Cursor **c, int *v){
    if (c == NULL || *c == NULL) return 0;
    if ((*c)->lista == NULL || (*c)->lista->cabeca == NULL) return 0;
    if ((*c)->atual == NULL) return 0;

    NoDuplo *alvo = (*c)->atual;
    ListaDupla *l = (*c)->lista;

    if (v != NULL) *v = alvo->valor;

    if (alvo->ant != NULL) {
        (*c)->atual = alvo->ant;
    } else if (alvo->prox != NULL) {
        (*c)->atual = alvo->prox;
    } else {
        (*c)->atual = NULL;
    }

    if (alvo->ant != NULL) {
        alvo->ant->prox = alvo->prox;
    } else {
        l->cabeca = alvo->prox;
    }

    if (alvo->prox != NULL) {
        alvo->prox->ant = alvo->ant;
    } else {
        l->cauda = alvo->ant;
    }

    free(alvo);
    return 1;
}

// Inverte a lista dupla in-place.
void inverter_lista(ListaDupla *l){
    if (l == NULL || l->cabeca == NULL) return;

    NoDuplo *atual = l->cabeca;

    while (atual != NULL) {
        NoDuplo *aux = atual->ant;
        atual->ant = atual->prox;
        atual->prox = aux;
        atual = atual->ant;
    }

    NoDuplo *aux = l->cauda;
    l->cauda = l->cabeca;
    l->cabeca = aux;
}

// Concatena l2 ao final de l em O(1), sem percorrer nenhuma das listas.
void concatenar_listas(ListaDupla *l, ListaDupla *l2){
    if (l == NULL || l2 == NULL) return;
    if (l2->cabeca == NULL) return;

    if (l->cabeca == NULL) {
        l->cabeca = l2->cabeca;
        l->cauda = l2->cauda;
    } else {
        l->cauda->prox = l2->cabeca;
        l2->cabeca->ant = l->cauda;
        l->cauda = l2->cauda;
    }

    l2->cabeca = NULL;
    l2->cauda = NULL;
}

// Acha o nó anterior ao meio da lista (último da primeira metade).
// Usa dois ponteiros: slow anda 1, fast anda 2.
// Quando fast chega ao fim, slow está no meio.
NoDuplo *meio(NoDuplo *cabeca) {
    NoDuplo *slow = cabeca;
    NoDuplo *fast = cabeca->prox;

    while (fast != NULL && fast->prox != NULL) {
        slow = slow->prox;
        fast = fast->prox->prox;
    }

    return slow;
}

// Divide a lista em duas metades.
// frente = primeira metade (cabeça até o meio)
// tras   = segunda metade (do próximo do meio até o fim)
// O prox do último nó da primeira metade é cortado (NULL),
// e o ant do primeiro nó da segunda metade também (NULL).
// Casos:
//   - lista vazia ou com 1 nó: tras = NULL
void partir(NoDuplo *fonte, ListaDupla *frente, ListaDupla *tras) {
    if (fonte == NULL || fonte->prox == NULL) {
        frente->cabeca = fonte;
        frente->cauda = fonte;
        tras->cabeca = NULL;
        tras->cauda = NULL;
        return;
    }

    NoDuplo *no_meio = meio(fonte);

    // Configura as duas metades
    frente->cabeca = fonte;
    tras->cabeca   = no_meio->prox;

    // Corta a conexão no meio: o meio passa a ser o último da primeira metade
    no_meio->prox = NULL;
    if (tras->cabeca != NULL) {
        tras->cabeca->ant = NULL;
    }

    // Ajusta ant da frente (caso fonte não seja a cabeça original)
    frente->cabeca->ant = NULL;

    // Acha a cauda de cada metade
    NoDuplo *p = frente->cabeca;
    while (p->prox != NULL) p = p->prox;
    frente->cauda = p;

    if (tras->cabeca != NULL) {
        p = tras->cabeca;
        while (p->prox != NULL) p = p->prox;
        tras->cauda = p;
    } else {
        tras->cauda = NULL;
    }
}

// Mescla duas listas duplas ORDENADAS em uma terceira, RELIGANDO os nós
// existentes (não aloca novos). Retorna uma ListaDupla com cabeca e cauda
// corretos. Ao final, as listas de origem ficam vazias (cabeca/cauda = NULL).
//
// Estratégia:
//   - Anda com pa e pb pelas duas listas.
//   - A cada passo, escolhe o menor nó e o "desliga" da lista de origem,
//     religando-o ao final do resultado.
//   - Ao final, anexa o resto da lista que sobrou (também religando).
ListaDupla mesclar(ListaDupla *a, ListaDupla *b) {
    ListaDupla res;
    res.cabeca = NULL;
    res.cauda = NULL;

    NoDuplo *pa = a->cabeca;
    NoDuplo *pb = b->cabeca;

    // Enquanto as duas listas tiverem nós, escolhe o menor
    while (pa != NULL && pb != NULL) {
        NoDuplo *escolhido;
        if (pa->valor <= pb->valor) {
            escolhido = pa;
            pa = pa->prox;
        } else {
            escolhido = pb;
            pb = pb->prox;
        }

        // Desliga o escolhido da lista antiga e anexa ao resultado
        escolhido->ant = res.cauda;
        escolhido->prox = NULL;
        if (res.cauda != NULL) res.cauda->prox = escolhido;
        else                   res.cabeca = escolhido;
        res.cauda = escolhido;
    }

    // Resto: qual lista não acabou?
    NoDuplo *resto = (pa != NULL) ? pa : pb;

    // Anexa o resto ao final do resultado, religando nó a nó
    while (resto != NULL) {
        NoDuplo *prox = resto->prox;
        resto->ant = res.cauda;
        resto->prox = NULL;
        if (res.cauda != NULL) res.cauda->prox = resto;
        else                   res.cabeca = resto;
        res.cauda = resto;
        resto = prox;
    }

    // Zera as listas de origem: os nós agora pertencem a res
    a->cabeca = NULL; a->cauda = NULL;
    b->cabeca = NULL; b->cauda = NULL;

    return res;
}

// Merge Sort recursivo em lista dupla.
// Casos base: lista vazia ou com 1 nó já estão ordenadas.
// Caso geral: parte ao meio, ordena cada metade recursivamente,
// e mescla as duas.
void mergeSort(ListaDupla *l) {
    if (l == NULL || l->cabeca == NULL || l->cabeca->prox == NULL) return;

    ListaDupla a;
    ListaDupla b;

    partir(l->cabeca, &a, &b);

    mergeSort(&a);
    mergeSort(&b);

    // mesclar devolve uma nova ListaDupla com cabeca e cauda corretos.
    // Atribui de volta à struct original.
    *l = mesclar(&a, &b);
}