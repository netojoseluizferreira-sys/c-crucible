// 037 — O Mais Velho
// Função maior_idade() recebe duas idades e retorna a maior delas.
// Se forem iguais, retorna qualquer uma (são iguais).
// A leitura e a impressão ficam em main.
#include <stdio.h>

int maior_idade(int age1, int age2);

int main(void) {
    int idade1, idade2;

    scanf("%d %d", &idade1, &idade2);

    printf("%d\n", maior_idade(idade1, idade2));

    return 0;
}

int maior_idade(int age1, int age2) {
    if (age1 >= age2)
        return age1;
    else
        return age2;
}