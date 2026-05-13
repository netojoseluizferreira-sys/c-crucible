// 031 — O Políglota Interativo
// Menu interativo com switch: oferece Soma, Subtracao, Multiplicacao e Sair.
// O menu reaparece até que o usuário digite 4 (Sair).
// Usa switch para mapeamento limpo das opções.
#include <stdio.h>

int main(void) {
    int num1, num2, operacao;

    // Loop infinito: só sai com case 4 (return 0)
    while (1) {
        printf("1) Soma\n2) Subtracao\n3) Multiplicacao\n4) Sair\nOpcao: ");
        scanf("%d", &operacao);

        switch (operacao) {
            case 4:
                return 0;           // encerra o programa
            case 1:
                scanf("%d %d", &num1, &num2);
                printf("%d\n", num1 + num2);
                break;
            case 2:
                scanf("%d %d", &num1, &num2);
                printf("%d\n", num1 - num2);
                break;
            case 3:
                scanf("%d %d", &num1, &num2);
                printf("%d\n", num1 * num2);
                break;
            default:
                printf("Operacao invalida\n");
                break;
        }
    }
}