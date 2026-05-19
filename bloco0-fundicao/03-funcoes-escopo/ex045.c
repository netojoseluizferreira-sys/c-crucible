#include <stdio.h>

int soma_digitos(int num);

int main(){
    int num;

    scanf("%d", &num);

    printf("%d", soma_digitos(num));

    return 0;
}

int soma_digitos(int num){
    if (num < 10) return num;
    return (num % 10) + soma_digitos(num / 10);
}

/*teste de mesa
soma(9234)
4 + soma(923)
7 + soma(92)
9 + soma(9)
18
aprovado
*/