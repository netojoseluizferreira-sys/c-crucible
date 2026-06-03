#include <stdio.h>

int main(void){
    int n;
    scanf("%d", &n);

    int *p = &n;
    int **pp = &p;

    printf("%d\n%d\n%d\n", n, *p, **pp);

    return 0;
}