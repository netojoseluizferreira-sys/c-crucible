// 149 — Log de Erros com Arquivo
// Lê strings continuamente e grava no arquivo log.txt no formato [Log] texto.
// Termina quando o usuário digitar SAIR.
// Demonstra modo append ("a") e loop com condição de parada.
#include <stdio.h>
#include <string.h>

int main(void) {
    char mensagem[200];

    // Abre o arquivo em modo append ("a")
    // Se não existir, cria. Se existir, anexa ao final.
    FILE *log = fopen("log.txt", "a");
    if (log == NULL) {
        printf("Erro ao abrir o arquivo de log!\n");
        return 1;
    }

    // Loop infinito controlado por condição de parada
    while (1) {
        // Lê uma linha da entrada padrão
        // %199s limita a leitura a 199 caracteres (evita overflow)
        scanf("%199s", mensagem);

        // Verifica se deve parar
        if (strcmp(mensagem, "SAIR") == 0) {
            break;
        }

        // Grava no log no formato [Log] mensagem
        fprintf(log, "[Log] %s\n", mensagem);

        // IMPORTANTE: flush para garantir que a mensagem vá para o disco
        // imediatamente, mesmo que o programa pare abruptamente
        fflush(log);
    }

    fclose(log);
    return 0;
}