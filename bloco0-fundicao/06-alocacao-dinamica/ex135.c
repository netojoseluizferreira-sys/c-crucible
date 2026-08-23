// 135 — O Trono do Ourives (Gerenciador de Memória Simplificado)
// O exercício mais completo de alocação dinâmica do Bloco 0.
// Implementa um CRUD de arrays dinâmicos com 10 slots,
// cada um podendo armazenar um array de inteiros.
//
// Comandos disponíveis:
//   S: Selecionar slot (0-9)
//   C: Criar array no slot atual (com calloc)
//   L: Listar elementos do slot atual
//   A: Adicionar valor ao final (expande com realloc)
//   D: Destruir array do slot atual (free + NULL)
//   Q: Sair liberando toda a memória
//
// Operações em um slot:
//   Criar  -> calloc (posições zeradas)
//   Adicionar -> realloc (+1 posição)
//   Listar -> percorre e imprime
//   Destruir -> free (libera o array do slot)
//
// Mecanismos importantes:
//   - Ponteiro duplo (int **slots) para gerenciar 10 arrays
//   - calloc para inicializar com zeros
//   - realloc com ponteiro temporário (seguro)
//   - free com anulação (evita double free)
//   - Limpeza de buffer após scanf de int (Windows)
//   - Menu interativo com entrada amigável
#include <stdio.h>
#include <stdlib.h>

// Protótipos das funções de manipulação
void array_inteiro(size_t tamanho, int slot, int **slots);
void listar_array(int slot, int tamanho, int **slots);
void expandir_array(int novo_elemento, int slot, int tamanho, int **slots);
void destruir_array(int slot, int **slots);

int main(void) {
    // Aloca o array de 10 ponteiros (cada um apontará para um array de int)
    int **slots = (int **)malloc(10 * sizeof(int *));
    if (slots == NULL) return 1;  // falha na alocação dos slots

    int slot = 0;             // slot selecionado atualmente
    int tamanhos[10] = {0};   // armazena o tamanho do array em cada slot
    int tamanho, novo_valor;  // variáveis auxiliares
    char caso;                // comando do usuário

    // Inicializa todos os slots como NULL (nenhum array alocado)
    for (size_t i = 0; i < 10; i++) {
        slots[i] = NULL;
    }

    // Loop principal do menu
    while (1) {
        printf("\n--SLOT ATUAL: %d--\n", slot);
        printf("S: Selecionar Slot\nC: Criar Array\nL: Ler Array\nA: Adicionar novo valor\nD: Destruir array\nQ: Sair\n");
        printf("Sua opcao: ");
        scanf(" %c", &caso);  // espaço antes de %c ignora whitespace

        switch (caso) {
            case 'S':  // Seleção do slot
                while (1) {
                    scanf("%d", &slot);
                    if (slot >= 0 && slot < 10) break;
                    else printf("Valor fora do intervalo, tente novamente\n");
                }
                break;

            case 'C':  // Criar array no slot atual
                printf("Digite o tamanho do array: ");
                scanf("%d", &tamanho);
                while (getchar() != '\n');  // limpa o buffer do teclado (Windows)
                tamanhos[slot] = tamanho;   // registra o tamanho

                if (slots[slot] == NULL) {
                    array_inteiro((size_t)tamanho, slot, slots);
                    printf("Array criado.\n");
                } else {
                    printf("Slot ja ocupado, tente outro slot\n");
                }
                break;

            case 'L':  // Listar elementos do slot atual
                printf("Slot %d: ", slot);
                if (slots[slot] != NULL) {
                    listar_array(slot, tamanhos[slot], slots);
                } else {
                    printf("Slot vazio\n");
                }
                break;

            case 'A':  // Adicionar valor ao final do array
                printf("Digite novo valor para o slot %d: ", slot);
                scanf("%d", &novo_valor);
                expandir_array(novo_valor, slot, tamanhos[slot], slots);
                printf("Valor %d adicionado ao final do slot %d\n", novo_valor, slot);
                tamanhos[slot]++;  // atualiza o tamanho registrado
                break;

            case 'D':  // Destruir array do slot atual
                printf("Destruindo slot %d\n", slot);
                destruir_array(slot, slots);
                printf("slot %d liberado\n", slot);
                tamanhos[slot] = 0;  // zera o tamanho registrado
                break;

            case 'Q':  // Sair liberando tudo
                printf("Liberando memoria para sair.\n");
                for (size_t i = 0; i < 10; i++) {
                    if (slots[i] != NULL) {
                        free(slots[i]);   // libera cada array alocado
                        slots[i] = NULL;  // anula o ponteiro
                    }
                }
                free(slots);       // libera o array de ponteiros
                slots = NULL;      // anula o ponteiro principal
                printf("Memoria liberada.\n");
                return 0;

            default:
                break;  // comando inválido: ignora
        }
    }
}

// Cria um array de tamanho 'tamanho' no slot 'slot', usando calloc
// calloc inicializa todas as posições com zero
void array_inteiro(size_t tamanho, int slot, int **slots) {
    *(slots + slot) = (int *)calloc(tamanho, sizeof(int));
}

// Lista os elementos do array no slot 'slot'
void listar_array(int slot, int tamanho, int **slots) {
    for (size_t i = 0; i < (size_t)tamanho; i++) {
        printf("%d ", slots[slot][i]);
    }
    printf("\n");
}

// Expande o array do slot 'slot' em uma posição e adiciona 'novo_elemento'
// Usa realloc com ponteiro temporário para segurança
void expandir_array(int novo_elemento, int slot, int tamanho, int **slots) {
    // Realoca para (tamanho + 1) elementos
    int *temp = (int *)realloc(slots[slot], ((size_t)tamanho + 1) * sizeof(int));
    if (temp == NULL) return;  // se falhar, mantém o array original

    slots[slot] = temp;  // atualiza o ponteiro para o novo bloco

    // Inicializa a nova posição e armazena o valor
    slots[slot][tamanho] = 0;  // zera a nova posição (evita lixo de memória)
    slots[slot][tamanho] = novo_elemento;
}

// Libera o array do slot 'slot' e anula o ponteiro
void destruir_array(int slot, int **slots) {
    free(slots[slot]);   // libera a memória do array
    slots[slot] = NULL;  // anula para evitar double free
}